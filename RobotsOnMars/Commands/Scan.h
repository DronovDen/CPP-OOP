#pragma once

#include "../Commands/ManualCommands.h"

class Robot;

class Scan : public ManualCommands
{
public:
    Scan() = default;
    bool Execute(Robot *robot) override;
};
