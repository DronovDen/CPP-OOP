#include "Robot.h"
#include "Server.h"
#include "Sapper.h"
#include "Collector.h"

Robot::Robot() : world(new World()), server(nullptr), position({0, 0}), exploredGameArea(nullptr) {}

Robot::~Robot()
{
    delete exploredGameArea;
}

bool Robot::IsAvailableToMove(const Coordinates &coordinates, Robot *robot) const
{
    CellType cellType;
    if (dynamic_cast<Collector *>(robot))
    {
        cellType = world->GetCellInRobotWorld(coordinates);
    }
    else if (dynamic_cast<Sapper *>(robot))
    {
        cellType = server->GetActualGameArea()->GetCell(coordinates).GetType();
    }

    if ((cellType == CellType::EMPTY || cellType == CellType::DIAMOND || (dynamic_cast<Sapper *>(robot) && cellType == CellType::BOMB)) &&
        exploredGameArea->IsCellOnMap(coordinates) && cellType != CellType::UNKNOWN)
    {
        return true;
    }

    return false;
}

Coordinates Robot::GetSpawnCoordinates()
{
    Coordinates spawn = {0, 0};
    spawn.x = rand() % world->GetGlobalGameArea()->GetWidth();
    spawn.y = rand() % world->GetGlobalGameArea()->GetHeight();
    while (!IsAvailableToMove(spawn, this))
    {
        spawn.x = rand() % world->GetGlobalGameArea()->GetWidth();
        spawn.y = rand() % world->GetGlobalGameArea()->GetHeight();
    }
    return spawn;
}

Coordinates Robot::CalculateNewCoordinates(const Direction &direction)
{
    Coordinates coord = this->position;

    if (direction == Direction::UP)
    {
        coord.y = (position.y - 1);
    }
    else if (direction == Direction::DOWN)
    {
        coord.y = (position.y + 1);
    }
    else if (direction == Direction::LEFT)
    {
        coord.x = (position.x - 1);
    }
    else if (direction == Direction::RIGHT)
    {
        coord.x = (position.x + 1);
    }
    return coord;
}

void Robot::ClearCell(CellType targetCell)
{
    Cell cell = exploredGameArea->GetCell(position);

    if (cell.GetType() == targetCell)
    {
        cell.SetType(CellType::EMPTY);
    }
}

void Robot::updateMap()
{
    this->server->applyOthersRobotsChanges();
}
