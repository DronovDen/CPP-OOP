#pragma once
#include "ModeBasement.h"
//#include "Commands/ICommand.h"
//#include "Application/Simulation.h"
#include "../Commands/ICommand.h"
//#include "Robot/Robot.h"

class ICommand;

class ManualMode : public ModeBasement
{
public:
    ManualMode() = default;
    ~ManualMode() = default;
    //virtual ~ManualMode() = default;
    void SetCommand(ICommand* command);
    bool ExecuteManual(Robot *robot);
    //void SetCommand(ICommand *command) override;
    //virtual void OnFrame() override;
private:
    ICommand *command;
};
