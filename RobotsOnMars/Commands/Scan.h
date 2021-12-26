#pragma once

#include "../Commands/ManualCommands.h"

class Robot;

class Scan : public ManualCommands
{
public:
    Scan() = default;
    //virtual ~Scan() = default;
    //bool Execute() { return true; };
    bool Execute(Robot *robot) override;
    //virtual CommandType GetCommandType(){return CommandType::SCAN;};
};
