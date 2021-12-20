#pragma once
#include "Commands/ICommand.h"
#include "Robot/Robot.h"
#include "Application/Manager.h"

enum class Mode
{
    MANUAL,
    SCAN,
    GRAB,
};

class ModeBasement
{
public:
    ModeBasement(){};
    ~ModeBasement() = default;

    //virtual Mode GetMode() const { return mode; };

    virtual void SetCommand(ICommand *command);
    virtual void SetManager(Manager *manager);
    virtual bool Execute(Robot *robot);

    Manager *manager;

    //virtual void RenderPath() = 0;
    //void Render() const;

    //Simulation &simulation;

    ICommand *command;
};