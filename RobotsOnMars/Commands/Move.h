#pragma once

#include "Commands/ManualModeCommand.h"
#include "Robot/Robot.h"

class Move : public ManualModeCommand
{
public:
    Move(Direction direction);
    virtual ~Move() = default;

private:
    virtual void ExecuteImpl(GameInterface &gameInterface) override;

    virtual void UndoImpl(GameInterface &gameInterface) override;

    virtual CommandType GetCommandType() const override;

    Direction m_direction{Direction::Up};
};