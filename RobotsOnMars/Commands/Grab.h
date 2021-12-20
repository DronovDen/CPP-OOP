#pragma once
#include "Commands/ManualCommands.h"

class Grab : public ManualCommands
{
public:
    Grab() = default;
    virtual ~Grab() = default;
    virtual CommandType GetCommandType() { return CommandType::GRAB; };
    virtual bool Execute(Robot *robot) override;
};