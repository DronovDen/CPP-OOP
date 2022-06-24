#pragma once
#include "ManualCommands.h"

class Robot;

class Grab : public ManualCommands
{
public:
    Grab() = default;
    bool Execute(Robot *robot) override;
};