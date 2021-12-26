#include "ManualMode.h"
#include "../Commands/Grab.h"
#include "../Commands/Scan.h"
#include "../Commands/Move.h"

class ICommand;

//class ManualCommands;

void ManualMode::SetCommand(ICommand *command)
{
    if (dynamic_cast<Grab *>(command))
    {
        this->command = dynamic_cast<Grab *>(command);
    }
    if (dynamic_cast<Scan *>(command))
    {
        this->command = dynamic_cast<Scan *>(command);
    }
    if (dynamic_cast<Move *>(command))
    {
        this->command = dynamic_cast<Move *>(command);
    }
}

bool ManualMode::ExecuteManual(Robot *robot)
{
    //bool result = true;
    bool result = dynamic_cast<ICommand *>(command)->Execute(robot);
    return result;
}
