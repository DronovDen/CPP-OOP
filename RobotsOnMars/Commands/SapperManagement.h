#pragma once
#include "../Commands/ICommand.h"
#include <string>

class Manager;

class SapperManagement : public ICommand
{
public:
    SapperManagement(std::string switcher, Manager *Manager);
    virtual bool Execute(Robot *robot) override;

private:
    Manager *manager;
    std::string state;
};
