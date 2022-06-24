#include "Scan.h"

#include "../Robot/Collector.h"

bool Scan::Execute(Robot *robot)
{
    dynamic_cast<Collector *>(robot)->Scan();
    return true;
}
