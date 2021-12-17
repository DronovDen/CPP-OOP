#include "AutoMode.h"

AutoMode::AutoMode(Simulation &simulation, Mode modeType)
    : ModeBasement(simulation, modeType)
{
    directions[Direction::UP] = [](const Point &p)
    { return Up(p); };
    directions[Direction::DOWN] = [](const Point &p)
    { return Down(p); };
    directions[Direction::RIGHT] = [](const Point &p)
    { return Right(p); };
    directions[Direction::LEFT] = [](const Point &p)
    { return Left(p); };
}

AutoMode::Point::Point(size_t X, size_t Y) : X{X}, Y{Y}
{
}

AutoMode::Point AutoMode::Up(const Point &p)
{
    return Point(p.X, p.Y - 1);
}

AutoMode::Point AutoMode::Down(const Point &p)
{
    return Point(p.X, p.Y + 1);
}

AutoMode::Point AutoMode::Right(const Point &p)
{
    return Point(p.X + 1, p.Y);
}

AutoMode::Point AutoMode::Left(const Point &p)
{
    return Point(p.X - 1, p.Y);
}

bool AutoMode::ExploreArea(std::vector<Point> &points, CellType targetCell, const std::vector<CellType> &restrictedCells) const
{
    const auto &cur = points.back(); //last cell in current path
    //start exploring area from it

    const auto &gameArea = simulation.Player->GetExploredGameArea();
    //4 - number of directions
    for (size_t i = 0; i < 4; ++i)
    {
        auto point = directions[Direction(i)](cur);

        //checking if point is on gameArea or is in path already
        if (!gameArea.IsCellOnMap(point.X, point.Y) || std::find(std::cbegin(points), std::cend(points), point) != std::cend(points))
            continue;
        auto &cell = gameArea.GetCell(point.X, point.Y);
        if (cell.GetRobot() != nullptr)
            continue;
        if (cell.GetType() == targetCell)
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

std::deque<Direction> AutoMode::Convert(const std::vector<Point> &points) const
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

Direction AutoMode::FindDirection(const Point &from, const Point &to) const
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (directions[Direction(i)](from) == to)
            return Direction(i);
    }
    return (Direction)4;
}

std::deque<Direction> AutoMode::FindPath(const Robot &robot, CellType targetCell, const std::vector<CellType> &restrictedCells) const
{
    std::vector<Point> points; //vector of path points
    std::deque<Direction> directions; //deque of instructions for robot to be executed
    auto &[x, y] = robot.GetPosition();
    points.push_back(Point{x, y}); //<-- Robot position
    if (ExploreArea(points, targetCell, restrictedCells))
    {
        directions = Convert(points);
    }
    return directions;
}