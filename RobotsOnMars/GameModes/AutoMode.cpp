#include "AutoMode.h"
#include "../Application/Manager.h"
#include <algorithm>

#include "../World/GameArea.h"

class Manager;

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

bool AutoMode::ExploreArea(std::vector<Coordinates> &posize_ts, CellType targetCell, std::vector<CellType> &restrictedCells)
{
    const auto &cur = posize_ts.back(); //last cell in current path
    //start exploring area from it
    GameArea gameArea = manager->GetCurrentMap();
    //GameArea gameArea = manager->GetCurrentMap();

    //const auto &gameArea = simulation.Player->GetExploredGameArea();
    //4 - number of directions
    for (size_t i = 0; i < 4; ++i)
    {
        auto posize_t = directions[Direction(i)](cur);

        //checking if posize_t is on gameArea or is in path already
        if (!gameArea.IsCellOnMap(posize_t) || std::find(std::cbegin(posize_ts), std::cend(posize_ts), posize_t) != std::cend(posize_ts))
            continue;
        auto cell = gameArea.GetCell(posize_t.x, posize_t.y);
        if (cell.GetType() == CellType::SAPPER || cell.GetType() == CellType::COLLECTOR)
            continue;
        if (cell.GetType() == targetCell) //if cell isn't researched already - good!
        {
            posize_ts.push_back(posize_t);
            return true; //path was found
        }
        //checking if cell isn't restricted for robot
        if (std::find(std::cbegin(restrictedCells), std::cend(restrictedCells), cell.GetType()) == std::cend(restrictedCells))
        {
            posize_ts.push_back(posize_t);
            if (ExploreArea(posize_ts, targetCell, restrictedCells))
                return true;
        }
    }
    return false;
}

std::deque<Direction> AutoMode::Convert(const std::vector<Coordinates> &posize_ts)
{
    std::deque<Direction> result;
    auto *posize_t = &posize_ts.back();
    while (posize_t->previous != nullptr)
    {
        result.push_front(FindDirection(*posize_t->previous, *posize_t));
        posize_t = posize_t->previous;
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
    std::vector<Coordinates> posize_ts; //vector of path posize_ts
    std::deque<Direction> directions;   //deque of instructions for robot to be executed
    Coordinates coord = robot->GetCoordinates();
    posize_ts.push_back(coord); //<-- Robot position
    if (ExploreArea(posize_ts, targetCell, restrictedCells))
    {
        directions = Convert(posize_ts);
    }
    return directions;
}