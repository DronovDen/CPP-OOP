#include "ManualCommands.h"
#include "Application/Simulation.h"
#include "GameModes/ModeBasement.h"

#include <stdexcept>
#include <string>

void ManualCommands::Execute(Simulation &simulation)
{
    AssertModeValid(simulation);

    CommandImplementation(simulation);
}

/*void ManualCommands::Undo(Simulation &gameInterface)
{
    AssertModeValid(gameInterface);

    UndoImpl(gameInterface);
}*/

void ManualCommands::AssertModeValid(Simulation &simulation) const
{
    if (simulation.Mode->GetMode() != Mode::MANUAL)
    {
        throw std::runtime_error("This command is not suitable for Manual mode");
    }
}
