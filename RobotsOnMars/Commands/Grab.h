#pragma once
#include "Commands/ManualCommands.h"

class Grab : public ManualModeCommand
{
public:
    Grab();
    virtual ~Grab() = default;
    virtual CommandType GetCommandType() { return CommandType::GRAB; };
    virtual void Execute(Robot *robot) override;
};