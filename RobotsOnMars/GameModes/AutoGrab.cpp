#include "AutoGrab.h"

AutoGrab::AutoGrab(Simulation &simulation)
    : AutoMode(simulation, Mode::GRAB)
{
}

void AutoGrab::RenderPath()
{
    //as long as diamonds present on gameArea
    //continue collecting process
    //and it is possible that all the bombs have been defused
    while (Step())
    {
        Render();
    }
}

void AutoGrab::ImplementPath(Robot &robot, const std::deque<Direction> &path)
{
    for (auto &direction : path)
    {
        robot.Move(direction);
        Render();
    }
}

bool AutoGrab::Step()
{
    Defuse();
    return Collect();
}

bool AutoGrab::Collect()
{
    auto &collector = simulation.Player->GetCollector();
    const std::vector<CellType> restrictedCollectorCells = {CellType::BOMB, CellType::ROCK, CellType::UNKNOWN};
    auto path = FindPath(collector, CellType::DIAMOND, restrictedCollectorCells);
    if (path.empty())
        return false;

    ImplementPath(collector, path);
    collector.Collect();
    return true;
}

void AutoGrab::Defuse()
{
    const auto sapper = simulation.Player->GetSapper();
    if (sapper == nullptr)
        return;
    const std::vector<CellType> restrictedSapperCells = {CellType::ROCK, CellType::UNKNOWN};
    auto path = FindPath(*sapper, CellType::BOMB, restrictedSapperCells);
    if (path.empty())
        return;
    ImplementPath(*sapper, path);
    sapper->Defuse();
}
