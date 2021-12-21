#pragma once

#include "Commands/ManualCommands.h"

class Scan : public ManualCommands
{
public:
    Scan() = default;
    virtual ~Scan() = default;
    virtual bool Execute(Robot *robot) override;
    //virtual CommandType GetCommandType(){return CommandType::SCAN;};
};
