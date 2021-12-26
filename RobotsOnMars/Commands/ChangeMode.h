#pragma once

#include "ICommand.h"
//#include "GameModes/ModeBasement.h"

//#include "../Application/Manager.h"
//#include "Robot/Robot.h"
#include <string>

class Manager;
class Robot;

class ChangeMode : public ICommand
{
public:
    ChangeMode(std::string modeName, Manager *manager, size_t stepsNum);
    ChangeMode(std::string modeName, Manager *manager);
    virtual ~ChangeMode() = default;
    bool Execute(Robot *robot) override;

private:
    std::string modeName;
    Manager *manager;
    size_t stepsNum = 0;
};