#include "Robot.h"
//#include "World/GameArea/Cell.h"
//#include "World/GameArea/GameArea.h"
//#include "World/IWorld.h"

Robot::Robot() : world(new World()), server(nullptr), position({0, 0}), exploredGameArea(nullptr) {}

Robot::~Robot()
{
    delete exploredGameArea;
}

bool Robot::IsAvailableToMove(const Coordinates &coordinates, Robot *robot) const
{
    CellType cellType = world->GetCellInRobotWorld(coordinates);

    if ((cellType == CellType::EMPTY || cellType == CellType::DIAMOND || (dynamic_cast<Sapper *>(robot) && cellType == CellType::BOMB)) &&
        !exploredGameArea->IsCellOnMap(coordinates))
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

Direction Robot::GetDirection(const Coordinates &difference)
{
    if (difference.x == 0)
    {
        if (difference.y == 1)
            return Direction::DOWN;
        if (difference.y == -1)
            return Direction::UP;
    }
    if (difference.y == 0)
    {
        if (difference.x == 1)
            return Direction::RIGHT;
        if (difference.x == -1)
            return Direction::LEFT;
    }
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
        coord.y = (position.x - 1);
    }
    else if (direction == Direction::LEFT)
    {
        coord.y = (position.x + 1);
    }
    return coord;
}

/* void Robot::SetPosition()
{
    while (true)
    {
        position.x = rand() % world->GetGlobalMap()->GetWidth();
        position.y = rand() % world->GetGlobalMap()->GetHeight();
        Cell &cell = world->GetCell(position);
        if (CanBeSetOnCell(cell))
        {
            Move(position);
            //discovering the first position
            //(updating map(exploredGameArea))
            exploredGameArea->GetCell(position).SetType(cell.GetType());
            break;
        }
    }
} */

/* void Robot::Move(Direction direction)
{
    const auto &[x, y] = CalculateTargetPos(direction);
    Move(x, y);
} */

/* void Robot::Move(Coordinates position)
{
    if (AvailableToMove(position))
    {
        exploredGameArea->GetCell(Coordinates(x, y)).SetRobot(nullptr);
        exploredGameArea->GetCell(Coordinates(x, y)).SetRobot(this);

        position = Coordinates(x, y);
    }
} */

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

/* bool Robot::AvailableToMove(Coordinates coordinates) const
{
    if (!world.GetGlobalMap().IsCellOnMap(coordinates.x, coordinates.y))
        return false;
    const Cell &cell = world.GetCell(x, y);
    return (cell.GetType() != CellType::ROCK && cell.GetRobot() == nullptr && AvailableForConcrete(x, y));
} */

//for basic robot and sapper it's normal to go on bomb
/* bool Robot::AvailableForConcrete(size_t x, size_t y) const
{
    return true;
} */

/* std::pair<size_t, size_t> Robot::CalculateTargetPos(Direction dir) const
{
    size_t size_x = position.x;
    size_t size_y = position.y;
    if (dir == Direction::LEFT)
    {
        if (size_x > 0)
            size_x -= 1;
        else
            size_x = 0;
    }
    //x = x > 0 ? x - 1 : 0;

    else if (dir == Direction::RIGHT)
        ++size_x;
    else if (dir == Direction::DOWN)
    {
        if (size_y > 0)
            size_y -= 1;
        else
            size_y = 0;
    }
    //y = y > 0 ? y - 1 : 0;

    else if (dir == Direction::UP)
        ++size_y;
    return {size_x, size_y};
} */
