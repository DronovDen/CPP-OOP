#pragma once
#include "ICommand.h"

class Robot;

class ManualCommands : public ICommand
{
public:
    ManualCommands() = default;
    virtual bool Execute(Robot *robot) = 0;
};