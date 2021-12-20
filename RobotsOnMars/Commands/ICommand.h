#pragma once
//#include "Application/Simulation.h"
//#include "Application/Manager.h"
//struct GameInterface;

enum class CommandType
{
    MOVE,
    GRAB,
    SCAN,
    SET_MODE,
    SAPPER
};

class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual bool Execute() = 0;

    virtual CommandType GetCommandType() const = 0;
};
