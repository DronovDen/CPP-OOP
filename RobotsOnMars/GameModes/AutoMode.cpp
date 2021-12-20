#include "AutoMode.h"

AutoMode::AutoMode()
{
    directions[Direction::UP] = [](const Coordinates &p)
    { return Up(p); };
    directions[Direction::DOWN] = [](const Coordinates &p)
    { return Down(p); };
    directions[Direction::RIGHT] = [](const Coordinates &p)
    { return Right(p); };
    directions[Direction::LEFT] = [](const Coordinates &p)
    { return Left(p); };
}

Coordinates AutoMode::Up(const Coordinates &p)
{
    return Coordinates(p.x, p.y - 1);
}

Coordinates AutoMode::Down(const Coordinates &p)
{
    return Coordinates(p.x, p.y + 1);
}

Coordinates AutoMode::Right(const Coordinates &p)
{
    return Coordinates(p.x + 1, p.y);
}

Coordinates AutoMode::Left(const Coordinates &p)
{
    return Coordinates(p.x - 1, p.y);
}

bool AutoMode::ExploreArea(std::vector<Coordinates> &points, CellType targetCell, std::vector<CellType> &restrictedCells)
{
    const auto &cur = points.back(); //last cell in current path
    //start exploring area from it
    GameArea &gameArea = manager->GetCurrentMap();
    //const auto &gameArea = simulation.Player->GetExploredGameArea();
    //4 - number of directions
    for (size_t i = 0; i < 4; ++i)
    {
        auto point = directions[Direction(i)](cur);

        //checking if point is on gameArea or is in path already
        if (!gameArea.IsCellOnMap(point.x, point.y) || std::find(std::cbegin(points), std::cend(points), point) != std::cend(points))
            continue;
        auto &cell = gameArea.GetCell(point.x, point.y);
        if (cell.GetRobot() != nullptr)
            continue;
        if (cell.GetType() == targetCell)//if cell isn't researched already - good!
        {
            points.push_back(point);
            return true; //path was found
        }
        //checking if cell isn't restricted for robot
        if (std::find(std::cbegin(restrictedCells), std::cend(restrictedCells), cell.GetType()) == std::cend(restrictedCells))
        {
            points.push_back(point);
            if (ExploreArea(points, targetCell, restrictedCells))
                return true;
        }
    }
    return false;
}

std::deque<Direction> AutoMode::Convert(const std::vector<Coordinates> &points)
{
    std::deque<Direction> result;
    auto *point = &points.back();
    while (point->previous != nullptr)
    {
        result.push_front(FindDirection(*point->previous, *point));
        point = point->previous;
    }
    return result;
}

Direction AutoMode::FindDirection(const Coordinates &from, const Coordinates &to)
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (directions[Direction(i)](from) == to)
            return Direction(i);
    }
    return (Direction)4;
}

std::deque<Direction> AutoMode::FindPath(Robot *robot, CellType targetCell, std::vector<CellType> &restrictedCells)
{
    std::vector<Coordinates> points; //vector of path points
    std::deque<Direction> directions; //deque of instructions for robot to be executed
    Coordinates coord = robot->GetPosition();
    points.push_back(coord); //<-- Robot position
    if (ExploreArea(points, targetCell, restrictedCells))
    {
        directions = Convert(points);
    }
    return directions;
}