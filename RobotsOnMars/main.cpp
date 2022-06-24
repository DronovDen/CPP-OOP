#include "Application/Manager.h"
#include "Application/View.h"
#include "World/GameArea.h"
#include "Console/Parser.h"

int main()
{
    Manager *manager = new Manager();
    manager->ExecuteGame();
    return 0;
}