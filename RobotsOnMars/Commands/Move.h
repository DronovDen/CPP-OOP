#pragma once

#include "Commands/ManualCommands.h"

class Move : public ManualCommands
{
public:
    Move(Direction direction);
    virtual ~Move() = default;
    virtual void Execute(Robot *robot) override;
    virtual CommandType GetCommandType() { return CommandType::MOVE; };

private:
    Direction direction{Direction::UP};
};