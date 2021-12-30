#include "Move.h"
#include "../Robot/Collector.h"
#include <exception>

Move::Move(Direction direction)
    : direction(direction)
{
}

bool Move::Execute(Robot *robot)
{
    try
    {
        robot->Move(direction);
    }
    catch (std::exception &ex)
    {
        throw;
    }
    //dynamic_cast<Collector *>(robot)->Move(direction);
    return true;
}
