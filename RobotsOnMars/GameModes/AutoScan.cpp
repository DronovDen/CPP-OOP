#include "AutoScan.h"
#include "Application/Simulation.h"
#include "Robot/Robot.h"
#include "World/GameArea.h"
#include "Player/Player.h"

AutoScan::AutoScan(Simulation &simulation, std::size_t stepsNum)
    : AutoMode{simulation, Mode::SCAN}, stepsNum{stepsNum}
{
}

void AutoScan::RenderPath()
{
    for (size_t i = 0; i < stepsNum; ++i)
    {
        if (Step())
        {
            Render();
        }
        else
        {
            break;
        }
    }
    stepsNum = 0;
}

bool AutoScan::Step() const
{
    auto &collector = simulation.Player->GetCollector();
    
    auto path = FindPath(collector, CellType::UNKNOWN, restrictedCells);
    if (path.empty())
        return false;

    //path.pop_back(); //<--target cell (UNKNOWN)

    //foreach cycle
    for (auto &direction : path)
    {
        collector.Move(direction);
        Render();
    }

    collector.Scan();
    return true;
}
