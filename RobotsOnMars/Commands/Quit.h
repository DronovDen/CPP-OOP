#include "ICommand.h"
#include "Application/Manager.h"

class Quit : public ICommand
{
public:
    Quit(Manager *manager) : manager{manager} {};
    virtual bool Execute() override { return true; };

private:
    Manager *manager;
};