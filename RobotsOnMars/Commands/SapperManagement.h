#pragma once
#include "../Commands/ICommand.h"
#include <string>

class Manager;

class SapperManagement : public ICommand
{
public:
    SapperManagement(std::string switcher, Manager *Manager);
    //virtual ~SapperManagement() = default;
    virtual bool Execute(Robot *robot) override;
    //virtual CommandType GetCommandType() { return CommandType::SAPPER; };

private:
    Manager *manager;
    std::string state;
};
