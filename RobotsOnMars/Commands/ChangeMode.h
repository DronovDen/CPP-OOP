#pragma once

#include "ICommand.h"
//#include "GameModes/ModeBasement.h"
#include "../GameModes/AutoScan.h"
#include "../Application/Manager.h"
//#include "Robot/Robot.h"
#include <string.h>

//class Manger;

class ChangeMode : public ICommand
{
public:
    ChangeMode(std::string modeName, Manager *manager, size_t stepsNum);
    ChangeMode(std::string modeName, Manager *manager);
    virtual ~ChangeMode() = default;
    virtual bool Execute() override;

private:
    std::string modeName;
    Manager *manager;
    size_t stepsNum = 0;
};