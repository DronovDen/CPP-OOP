#pragma once
#include "../Commands/ManualCommands.h"
#include "../Robot/Direction.h"
#include <exception>

class Move : public ManualCommands
{
public:
    Move(Direction direction);
    bool Execute(Robot *robot) override;

private:
    Direction direction{Direction::UP};
};