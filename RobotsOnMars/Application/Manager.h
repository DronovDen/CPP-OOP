#pragma once
//#include "World/GameArea.h"
//#include "GameModes/ModeBasement.h"
//#include "Commands/ICommand.h"
//#include "Console/ConsoleArgs.h"
//#include "Console/CommandParser.h"
//#include <map>
#include "World/World.h"
#include "Console/Parser.h"
#include "Robot/Server.h"
#include "Robot/Collector.h"
#include "GameModes/InactiveMode.h"
#include "GameModes/AutoGrab.h"

class World;
class Player;
class ModeBasement;
class IView;
class Parser;
class ICommand;
class Server;
class Server;
class GameArea;
class Robot;

using namespace std;

class Manager
{
public:
    Manager(int argc, char **argv);
    ~Manager();

    void ExecuteGame();
    bool DoStep();

    GameArea *GetGlobalMap() { return &globalMap; }
    //????
    GameArea GetCurrentMap() { return *currentMap; }
    //GameArea* GetCurrentMap() {return currentMap;};
    auto GetModesRange() { return &modesRange; }
    auto GetCommandParser() { return commandParser; }
    auto GetServer() { return server; }
    auto GetActiveRobots() { return &activeRobots; };

private:
    GameArea globalMap;
    GameArea *currentMap;
    map<string, ModeBasement *> modesRange;
    vector<pair<ModeBasement *, Robot *>> activeRobots;
    Parser *commandParser;
    MapLoader *loader;
    ICommand *currCommand;
    Server *server;
    IView gameView;
};