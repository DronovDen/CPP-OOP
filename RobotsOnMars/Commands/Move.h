#pragma once
#include "../Commands/ManualCommands.h"
#include "../Robot/Direction.h"
//#include "../Robot/Server.h"

class Move : public ManualCommands
{
public:
    Move(Direction direction);
    //virtual ~Move() = default;
    //bool Execute(){return true;};
    bool Execute(Robot *robot) override;
    //virtual CommandType GetCommandType() { return CommandType::MOVE; };

private:
    Direction direction{Direction::UP};
};