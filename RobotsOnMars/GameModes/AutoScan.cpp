#include "AutoScan.h"
#include "../Robot/Robot.h"
#include "../Robot/Collector.h"
#include "../World/GameArea.h"

/* bool AutoScan::Execute(Robot *robot)
{
    //dynamic_cast<Collector *>(robot)->Scan();
    //robot->updateMap();
    while (this->stepsNum != 0)
    {
        auto path = FindPath(robot, CellType::UNKNOWN, restrictedCells);
        if (path.empty())
            return false;
    }
} */

bool AutoScan::Execute(Robot *robot)
{
    for (size_t i = 0; i < stepsNum; ++i)
    {
        if (Step(robot))
        {
            robot->updateMap();
        }
        else
        {
            break;
        }
    }
    stepsNum = 0;
    return true;
}

bool AutoScan::Step(Robot *robot)
{
    auto collector = dynamic_cast<Collector *>(robot);
    auto path = FindPath(collector, CellType::UNKNOWN, restrictedCells);
    if (path.empty())
        return false;

    path.pop_back(); //<--target cell (UNKNOWN)

    //foreach cycle
    for (auto &direction : path)
    {
        collector->Move(direction);

    }
    collector->Scan();
    return true;
}
