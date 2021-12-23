#pragma once

#include "ICommand.h"
//#include "GameModes/ModeBasement.h"

//#include "../Application/Manager.h"
//#include "Robot/Robot.h"
#include <string>

class Manager;

class ChangeMode : public ICommand
{
public:
    ChangeMode(std::string modeName, Manager *manager, int stepsNum);
    ChangeMode(std::string modeName, Manager *manager);
    virtual ~ChangeMode() = default;
    virtual bool Execute() override;

private:
    std::string modeName;
    Manager *manager;
    int stepsNum = 0;
};