#include "Application/Manager.h"
#include "Application/View.h"
#include "World/GameArea.h"
#include "Console/Parser.h"

size_t main(size_t argc, char *argv[])
{
    Manager *manager = new Manager(argc, argv);
    manager->ExecuteGame();

    return 0;
}