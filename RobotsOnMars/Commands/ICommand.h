#pragma once
#include "Application/Simulation.h"

//struct GameInterface;

enum class CommandType : unsigned char
{
    MOVE,
    GRAB,
    SCAN,
    SET_MODE,
    SAPPER_ON,
    SAPPER_OFF
};

class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual void Execute(Simulation &simulation) = 0;

    virtual CommandType GetCommandType() const = 0;
};
