#include "ManualMode.h"
#include "Application/Simulation.h"

ManualMode::ManualMode(Simulation &simulation)
    : ModeBasement(simulation, Mode::MANUAL)
{
}

void ManualMode::OnFrame()
{
    // TODO:: simulate

    Render();
}
