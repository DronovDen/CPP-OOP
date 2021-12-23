#include "ManualMode.h"

//class ManualCommands;

bool ManualMode::ExecuteManual(Robot *robot)
{
    bool result = true;
    result = dynamic_cast<ManualCommands *>(command)->Execute(robot);
}
