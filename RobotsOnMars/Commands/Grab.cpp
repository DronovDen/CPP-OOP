#include "Grab.h"
#include "../Robot/Collector.h"

bool Grab::Execute(Robot *robot)
{
    dynamic_cast<Collector *>(robot)->Collect();
    //simulation.Player->GetCollector().Grab();
    return true;
}