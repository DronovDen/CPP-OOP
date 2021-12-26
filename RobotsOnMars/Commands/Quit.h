#include "ICommand.h"
//#include "Application/Manager.h"

class Manager;

class Quit : public ICommand
{
public:
    Quit(Manager *manager) : manager{manager} {};
    virtual bool Execute(Robot *robot) override { return true; };

private:
    Manager *manager;
};