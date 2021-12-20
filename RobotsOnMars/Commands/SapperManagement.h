#pragma once
#include "Commands/ICommand.h"
#include "Application/Manager.h"
#include "Player/Player.h"


class SapperManagement : public ICommand
{
public:
    SapperManagement(std::string switcher, Manager* Manager);
    virtual ~SapperManagement() = default;
    virtual void Execute() override;
    virtual CommandType GetCommandType() { return CommandType::SAPPER; };

private:
    Manager *manager;
    std::string state;
};
