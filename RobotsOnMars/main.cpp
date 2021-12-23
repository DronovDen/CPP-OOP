#include "Application/Manager.h"

int main(int argc, char *argv[])
{
    Manager* manager = new Manager(argc, argv);
    manager->ExecuteGame();

    return 0;
}