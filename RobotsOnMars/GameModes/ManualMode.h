#pragma once
#include "ModeBasement.h"
#include "../Commands/ICommand.h"

class ICommand;

class ManualMode : public ModeBasement
{
public:
    ManualMode() = default;
    ~ManualMode() = default;
    void SetCommand(ICommand *command);
    bool ExecuteManual(Robot *robot);

private:
    ICommand *command;
};
