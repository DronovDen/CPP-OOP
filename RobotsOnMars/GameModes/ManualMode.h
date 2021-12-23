#pragma once
#include "ModeBasement.h"
//#include "Commands/ICommand.h"
//#include "Application/Simulation.h"
#include "../Commands/ManualCommands.h"
//#include "Robot/Robot.h"

class ManualMode : public ModeBasement
{
public:
    ManualMode();
    virtual ~ManualMode() = default;
    bool ExecuteManual(Robot *robot);
    void SetCommand(ICommand *command) override;
    //virtual void OnFrame() override;
};
