#pragma once
#include <iostream>

class Robot;

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual bool Execute(Robot *robot) = 0;
};
