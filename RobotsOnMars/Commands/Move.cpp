#include "Move.h"
#include "../Robot/Collector.h"

Move::Move(Direction direction)
    : direction(direction)
{
}

bool Move::Execute(Robot *robot)
{
    dynamic_cast<Collector *>(robot)->Move(direction);

    //simulation.Player->GetCollector().Move(direction);
    return true;
}
