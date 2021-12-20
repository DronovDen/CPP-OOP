#include "Sapper.h"
//#include "GameArea/World.h"

Sapper::Sapper(GameArea *globalGameArea, Server *server)
{
    world->SetGlobalMap(globalGameArea);
    SetServer(server);
    exploredGameArea = new GameArea(globalGameArea->getMapSizeX(), globalGameArea->getMapSizeY());
    position = GetSpawnCoordinates();
    exploredGameArea->SetCell(this->position, CellType::SAPPER);
    //exploredGameArea.GetCell(this->position)->SetType(CellType::SAPPER);
    server->notifyRobotCreated(this, this->position);
    SetExploredArea(server->GetActualMap());

    updateMap();
}

Sapper::~Sapper()
{
    server->notifyRobotDeleted(this, this->position);
}

void Sapper::Move(const Direction &direction)
{
    Coordinates newCoord = CalculateNewCoordinates(direction);
    if (newCoord.x < 0 || newCoord.y < 0)
    {
        throw invalid_argument("Invalid coordinates");
    }
    CellType newPos = exploredGameArea->GetCell(newCoord).GetType();
    if (IsAvailableToMove(newCoord, this) && exploredGameArea->GetCell(newCoord).GetType() != CellType::UNKNOWN)
    {
        OldPositionProcessing();
        NewPositionProcessing(newPos);
        exploredGameArea->SetCell(newCoord, CellType::SAPPER);
        server->notifyRobotMoved(this, position, newCoord);
        position = newCoord;
    }
    else
    {
        throw("Can't move");
    }
}

void Sapper::OldPositionProcessing()
{
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
}

void Sapper::NewPositionProcessing(CellType newPos)
{
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
        this->server->notifyBombDefused(this, this->position);
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
