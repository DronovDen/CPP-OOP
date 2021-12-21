#pragma once
//#include "Application/Simulation.h"
//#include "Application/Manager.h"
//struct GameInterface;
#include "Application/Manager.h"
/* enum class CommandType
{
    MOVE,
    GRAB,
    SCAN,
    SET_MODE,
    SAPPER
}; */

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual bool Execute();

    //virtual CommandType GetCommandType() const = 0;
};
