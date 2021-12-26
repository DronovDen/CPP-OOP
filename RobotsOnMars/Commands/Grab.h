#pragma once
#include "ManualCommands.h"

class Robot;

class Grab : public ManualCommands
{
public:
    Grab() = default;
    //virtual ~Grab() = default;
    //virtual CommandType GetCommandType() { return CommandType::GRAB; };
    //bool Execute() { return true; };
    bool Execute(Robot *robot) override;
};