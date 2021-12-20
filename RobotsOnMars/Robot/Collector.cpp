#include "Collector.h"
//#include "World/IWorld.h"
//#include "GameArea/Cell.h"
//#include "GameArea/GameArea.h"

Collector::Collector(GameArea *globalGameArea, Server *server)
{
    world->SetGlobalMap(globalGameArea);
    this->SetServer(server);

    exploredGameArea = new GameArea(globalGameArea->GetWidth(), globalGameArea->GetHeight());

    position = GetSpawnCoordinates();
    exploredGameArea->SetCell(position, CellType::COLLECTOR);
    server->notifyRobotCreated(this, position);
}

void Collector::Collect()
{
    if (this->world->GetDiamondHolder())
    {
        exploredGameArea->SetDiamondsAmount(exploredGameArea->GetDiamondsAmount() + 1);
        this->world->SetDiamondHolder(false);
        this->server->notifyDiamondCollected(this, this->position);
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
    Coordinates point{x, y};
    if (!exploredGameArea->IsCellOnMap(point) ||
        exploredGameArea->GetCell(point).GetType() != CellType::UNKNOWN)
    {
        return;
    }
    CellType globalCell = this->world->GetCellInRobotWorld(point);
    exploredGameArea->SetCell(point, globalCell);
    server->notifyCellScanned(this, std::make_pair(point, globalCell));
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
