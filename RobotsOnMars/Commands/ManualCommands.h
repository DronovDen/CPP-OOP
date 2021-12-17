#pragma once

#include "ICommand.h"

class ManualCommands : public ICommand
{
public:
    ManualCommands() = default;
    virtual ~ManualCommands() = default;

    virtual void Execute(Simulation &simulation) override;
    virtual void CommandImplementation(Simulation &simulation) = 0;
    //virtual void Undo(Simulation &simulation) override final;

//protected:
    //virtual void ExecuteImpl(Simulation &simulation) = 0;
    //virtual void UndoImpl(Simulation &simulation) = 0;

private:
    void AssertModeValid(Simulation &simulation) const;
};