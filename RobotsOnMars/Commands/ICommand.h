#pragma once
//#include "Application/Simulation.h"
//#include "Application/Manager.h"
//struct GameInterface;
#include <iostream>
//#include "../Application/Manager.h"

class Robot;

class ICommand
{
public:
    virtual ~ICommand() = default;

    //virtual bool Execute(Robot* robot) { std::cout << "Executing..."; return true; };
    virtual bool Execute(Robot *robot) = 0;

    //virtual CommandType GetCommandType() const = 0;
};
