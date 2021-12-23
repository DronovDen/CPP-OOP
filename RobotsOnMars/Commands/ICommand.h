#pragma once
//#include "Application/Simulation.h"
//#include "Application/Manager.h"
//struct GameInterface;
#include "../Application/Manager.h"

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual bool Execute();

    //virtual CommandType GetCommandType() const = 0;
};
