#include "Collector.h"
#include "Server.h"
//#include "World/IWorld.h"
//#include "GameArea/Cell.h"
//#include "GameArea/GameArea.h"

Collector::Collector(GameArea *globalGameArea, Server *server)
{
    world->SetGlobalGameArea(globalGameArea);
    this->SetServer(server);

    exploredGameArea = new GameArea(globalGameArea->GetWidth(), globalGameArea->GetHeight());

    position = GetSpawnCoordinates();
    exploredGameArea->SetCell(position, CellType::COLLECTOR);
    server->NotifyRobotCreated(this, position);
}

Collector::~Collector()
{
    server->NotifyRobotDeleted(this, this->position);
}

void Collector::Move(const Direction &direction)
{
    Coordinates newCoord = CalculateNewCoordinates(direction);
    if (newCoord.x < 0 || newCoord.y < 0)
    {
        throw runtime_error("Invalid coordinates ");
    }
    CellType newPos = exploredGameArea->GetCell(newCoord).GetType();
    if (IsAvailableToMove(newCoord, this) && exploredGameArea->GetCell(newCoord).GetType() != CellType::UNKNOWN)
    {
        MoveImplementation(newPos);
        exploredGameArea->SetCell(newCoord, CellType::COLLECTOR);
        server->NotifyRobotMoved(this, position, newCoord);
        position = newCoord;
        updateMap(); //we are updating map because collector can be blown up by mine
    }
}

void Collector::MoveImplementation(CellType newPos)
{
    //Old position processing
    if (world->GetDiamondHolder())
    {
        exploredGameArea->SetCell(position, CellType::DIAMOND);
        world->SetDiamondHolder(false);
    }
    else
    {
        exploredGameArea->SetCell(this->position, CellType::EMPTY);
    }

    //New position processing
    if (newPos == CellType::DIAMOND)
    {
        world->SetDiamondHolder(true);
    }
}

void Collector::Collect()
{
    if (this->world->GetDiamondHolder())
    {
        exploredGameArea->SetDiamondsAmount(exploredGameArea->GetDiamondsAmount() + 1);
        this->world->SetDiamondHolder(false);
        this->server->NotifyDiamondCollected(this, this->position);
    }
}

void Collector::Scan()
{
    ScanCell(position.x - 1, position.y);
    ScanCell(position.x + 1, position.y);

    ScanCell(position.x, position.y + 1);
    ScanCell(position.x, position.y - 1);
}

void Collector::ScanCell(size_t x, size_t y) const
{
    Coordinates posize_t{x, y};
    if (!exploredGameArea->IsCellOnMap(posize_t) ||
        exploredGameArea->GetCell(posize_t).GetType() != CellType::UNKNOWN)
    {
        return;
    }
    CellType globalCell = this->world->GetCellInRobotWorld(posize_t);
    exploredGameArea->SetCell(posize_t, globalCell);
    server->NotifyCellScanned(const_cast<Collector *>(this), std::make_pair(posize_t, globalCell));
}

/* bool Collector::CanBeSetOnCell(const Cell &cell) const
{
    return (cell.GetType() != CellType::ROCK && cell.GetType() != CellType::BOMB && cell.GetRobot() == nullptr);
} */

//for collector it's BAD to go on bomb
/* bool Collector::AvailableForConcrete(size_t x, size_t y) const
{
    return (exploredGameArea.GetCell(x, y).GetType() != CellType::BOMB);
} */

/* void Collector::ScanCell(size_t x, size_t y) const
{
    if (x >= world.GetWidth() || y >= world.GetHeight())
        return;
    exploredGameArea.GetCell(x, y).SetType(world.GetCell(x, y).GetType());
} */
