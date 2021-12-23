#include "Scan.h"
//#include "Command/CommandType.h"
//#include "App/GameInterface.h"
#include "../Robot/Collector.h"
//#include "Player/Player.h"

bool Scan::Execute(Robot *robot)
{
    dynamic_cast<Collector *>(robot)->Scan();
    //gameInterface.Player->GetCollector().Scan();
}
