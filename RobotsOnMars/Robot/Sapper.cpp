#include "Sapper.h"
//#include "GameArea/World.h"

Sapper::Sapper(GameArea *globalGameArea, Server *server)
{
    world->SetGlobalGameArea(globalGameArea);
    SetServer(server);
    exploredGameArea = new GameArea(globalGameArea->getMapSizeX(), globalGameArea->getMapSizeY());
    position = GetSpawnCoordinates();
    exploredGameArea->SetCell(this->position, CellType::SAPPER);
    //exploredGameArea.GetCell(this->position)->SetType(CellType::SAPPER);
    server->NotifyRobotCreated(this, this->position);
    SetExploredArea(server->GetActualGameArea());

    updateMap();
}

Sapper::~Sapper()
{
    server->NotifyRobotDeleted(this, this->position);
}

void Sapper::Move(const Direction &direction)
{
    Coordinates newCoord = CalculateNewCoordinates(direction);
    if (newCoord.x < 0 || newCoord.y < 0)
    {
        throw runtime_error("Invalid coordinates");
    }
    CellType newPos = exploredGameArea->GetCell(newCoord).GetType();
    if (IsAvailableToMove(newCoord, this) && exploredGameArea->GetCell(newCoord).GetType() != CellType::UNKNOWN)
    {
        MoveImplementation(newPos);
        exploredGameArea->SetCell(newCoord, CellType::SAPPER);
        server->NotifyRobotMoved(this, position, newCoord);
        position = newCoord;
    }
    else
    {
        throw("Can't move");
    }
}

void Sapper::MoveImplementation(CellType newPos)
{
    //Old position processing
    if (world->GetDiamondHolder())
    {
        exploredGameArea->SetCell(position, CellType::DIAMOND);
        world->SetDiamondHolder(false);
    }
    else if (world->GetBombHolder())
    {
        exploredGameArea->SetCell(position, CellType::BOMB);
        world->SetBombHolder(false);
    }
    else
    {
        exploredGameArea->SetCell(position, CellType::EMPTY);
    }

    //New position processing
    if (newPos == CellType::DIAMOND)
    {
        world->SetDiamondHolder(true);
    }
    else if (newPos == CellType::BOMB)
    {
        world->SetBombHolder(true);
    }
}

void Sapper::Defuse()
{
    if (this->world->GetBombHolder())
    {
        exploredGameArea->SetBombsAmount(exploredGameArea->GetBombsAmount() + 1);
        this->world->SetBombHolder(false);
        this->server->NotifyBombDefused(this, this->position);
    }
}

/* void Sapper::SetPosition()
{
    while (true)
    {
        size_t x = rand() % exploredGameArea.GetWidth();
        size_t y = rand() % exploredGameArea.GetHeight();
        Cell &cell = exploredGameArea.GetCell(x, y);
        if (CanBeSetOnCell(cell))
        {
            Move(x, y);
            break;
        }
    }
} */

void Sapper::Defuse()
{
    ClearCell(CellType::BOMB);
}

/* bool Sapper::CanBeSetOnCell(const Cell &cell) const
{
    return (cell.GetType() != CellType::UNKNOWN && cell.GetType() != CellType::ROCK && cell.GetRobot() == nullptr);
} */
