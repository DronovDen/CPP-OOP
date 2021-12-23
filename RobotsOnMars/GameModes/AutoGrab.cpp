#include "AutoGrab.h"
#include "../Robot/Sapper.h"

//class Collector;

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
        Collect(robot);
    }
    else if (dynamic_cast<Sapper *>(robot))
    {
        Defuse(robot);
    }
    return true;
}

void AutoGrab::Collect(Robot *robot)
{
    //auto &collector = simulation.Player->GetCollector();
    std::vector<CellType> restrictedCollectorCells = {CellType::BOMB, CellType::ROCK, CellType::UNKNOWN};
    auto path = FindPath(robot, CellType::DIAMOND, restrictedCollectorCells);
    if (path.empty())
        return;
    ImplementPath(robot, path);
    auto collector = dynamic_cast<Collector *>(robot);
    collector->Collect();
}

void AutoGrab::Defuse(Robot *robot)
{
    //const auto sapper = simulation.Player->GetSapper();
    if (robot == nullptr)
        return;
    std::vector<CellType> restrictedSapperCells = {CellType::ROCK, CellType::UNKNOWN};
    auto path = FindPath(robot, CellType::BOMB, restrictedSapperCells);
    if (path.empty())
        return;
    ImplementPath(robot, path);
    auto sapper = dynamic_cast<Sapper *>(robot);
    sapper->Defuse();
}

void AutoGrab::ImplementPath(Robot *robot, const std::deque<Direction> &path)
{
    for (auto &direction : path)
    {
        robot->Move(direction);
        robot->updateMap();
    }
}
