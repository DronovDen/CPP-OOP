#include "ModeBasement.h"

void ModeBasement::SetCommand(ICommand *command)
{
    this->command = command;
}

void ModeBasement::SetServer(Server* newServer)
{
    this->server = newServer;
}

bool ModeBasement::Execute(Robot *robot)
{
    return true;
}