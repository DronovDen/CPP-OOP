#include "Robot.h"
//#include "World/GameArea/Cell.h"
//#include "World/GameArea/GameArea.h"
//#include "World/IWorld.h"

Robot::Robot(RobotType type, World &world, GameArea &gameArea)
    : type(type), world(world), exploredGameArea(gameArea)
{
}

Robot::~Robot()
{
    exploredGameArea.GetCell(coord_x, coord_y).SetRobot(nullptr);
}

void Robot::SetPosition()
{
    while (true)
    {
        size_t x = rand() % world.GetWidth();
        size_t y = rand() % world.GetHeight();
        Cell &cell = world.GetCell(x, y);
        if (CanBeSetOnCell(cell))
        {
            Move(x, y);
            //discovering the first position
            //(updating map(exploredGameArea))
            exploredGameArea.GetCell(x, y).SetType(cell.GetType());
            break;
        }
    }
}

std::pair<std::size_t, std::size_t> Robot::GetPosition() const
{
    return {coord_x, coord_y};
}

void Robot::Move(Direction direction)
{
    const auto &[x, y] = CalculateTargetPos(direction);
    Move(x, y);
}

void Robot::Move(size_t x, size_t y)
{
    if (AvailableToMove(x, y))
    {
        exploredGameArea.GetCell(x, y).SetRobot(nullptr);
        exploredGameArea.GetCell(x, y).SetRobot(this);

        coord_x = x;
        coord_y = y;
    }
}

void Robot::ClearCell(CellType targetCell)
{
    Cell &cell = exploredGameArea.GetCell(coord_x, coord_y);

    if (cell.GetType() == targetCell)
    {
        cell.SetType(CellType::EMPTY);
        ++score;
    }
}

size_t Robot::GetScore() const
{
    return score;
}

RobotType Robot::GetType() const
{
    return type;
}

bool Robot::AvailableToMove(size_t x, size_t y) const
{
    if (!world.GetGameArea().IsCellOnMap(x, y))
        return false;
    const Cell &cell = world.GetCell(x, y);
    return (cell.GetType() != CellType::ROCK && cell.GetRobot() == nullptr && AvailableForConcrete(x, y));
}

//for basic robot and sapper it's normal to go on bomb
bool Robot::AvailableForConcrete(size_t x, size_t y) const
{
    return true;
}

std::pair<size_t, size_t> Robot::CalculateTargetPos(Direction dir) const
{
    size_t size_x = coord_x;
    size_t size_y = coord_y;
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
}
