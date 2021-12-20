#include "Move.h"
#include "Player/Player.h"
#include "Robot/Collector.h"

void Move::Execute(Robot *robot)
{
    dynamic_cast<Collector *>(robot)->Collect();
    //simulation.Player->GetCollector().Grab();
}