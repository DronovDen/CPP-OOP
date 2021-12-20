#pragma once
#include "ModeBasement.h"
#include "Commands/ICommand.h"
#include "Application/Simulation.h"
#include "Commands/ManualCommands.h"

class ManualMode : public ModeBasement
{
public:
    ManualMode(Simulation &simulation);
    virtual ~ManualMode() = default;
    void ExecuteManual(Robot *robot);
    void SetCommand(ICommand *command) override;
    //virtual void OnFrame() override;
};
