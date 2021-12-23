#pragma once

#include "ICommand.h"
#include "../Robot/Robot.h"
//#include "GameModes/ModeBasement.h"

class ManualCommands : public ICommand
{
public:
    ManualCommands() = default;
    virtual ~ManualCommands() = default;

    virtual bool Execute(Robot *robot) = 0;
    //virtual void CommandImplementation(Robot *robot) = 0;

private:
    //void AssertModeValid(Simulation &simulation) const;
};