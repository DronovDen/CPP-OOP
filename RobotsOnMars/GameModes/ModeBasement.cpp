#include "ModeBasement.h"

void ModeBasement::SetCommand(ICommand *command)
{
    this->command = command;
}

void ModeBasement::SetManager(Manager *manager)
{
    this->manager = manager;
}

bool ModeBasement::Execute(Robot *robot)
{
    return true;
}