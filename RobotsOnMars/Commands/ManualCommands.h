#pragma once

#include "ICommand.h"

//#include "../Robot/Robot.h"

class Robot;

class ManualCommands : public ICommand
{
public:
    ManualCommands() = default;
    //virtual ~ManualCommands() = default;

    virtual bool Execute(Robot *robot) = 0;
    //bool Execute() { return true; };
    //virtual void CommandImplementation(Robot *robot) = 0;
    //void AssertModeValid(Simulation &simulation) const;
};