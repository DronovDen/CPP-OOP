#include "AutoGrab.h"
#include "../Robot/Sapper.h"
#include "../Robot/Server.h"

bool AutoGrab::Execute(Robot *robot)
{
    //as long as diamonds present on gameArea
    //continue collecting process
    //and it is possible that all the bombs have been defused
    while (Step(robot))
    {
        robot->updateMap();
    }
    return true;
}

bool AutoGrab::Step(Robot *robot)
{
    if (dynamic_cast<Collector *>(robot))
    {
        if (!Collect(robot))
            return false;
    }
    else if (dynamic_cast<Sapper *>(robot))
    {
        if (!Defuse(robot))
            return false;
    }
    return true;
}

bool AutoGrab::Collect(Robot *robot)
{
    while (robot->GetServer()->GetDiamondsAvaliable() != 0)
    {
        std::vector<CellType> restrictedCollectorCells = {CellType::BOMB, CellType::ROCK, CellType::UNKNOWN};
        auto path = FindPath(robot, CellType::DIAMOND, restrictedCollectorCells);
        if (path.empty())
            return false;
        ImplementPath(robot, path);
        auto collector = dynamic_cast<Collector *>(robot);
        collector->Collect();
    }
}

bool AutoGrab::Defuse(Robot *robot)
{
    if (robot == nullptr)
        return false;
    while (robot->GetServer()->GetBombsAvaliable() != 0)
    {
        std::vector<CellType> restrictedSapperCells = {CellType::ROCK, CellType::UNKNOWN};
        auto path = FindPath(robot, CellType::BOMB, restrictedSapperCells);
        if (path.empty())
            return false;
        ImplementPath(robot, path);
        auto sapper = dynamic_cast<Sapper *>(robot);
        sapper->Defuse();
    }
}

void AutoGrab::ImplementPath(Robot *robot, const std::deque<Direction> &path)
{
    for (auto &direction : path)
    {
        robot->Move(direction);
        robot->updateMap();
    }
}
