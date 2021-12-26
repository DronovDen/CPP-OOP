#pragma once
//#include "World/GameArea.h"
//#include "GameModes/ModeBasement.h"
//#include "Commands/ICommand.h"
//#include "Console/ConsoleArgs.h"
//#include "Console/CommandParser.h"
#include <map>
//#include "World/World.h"

//#include "../World/GameArea.h"
#include "../GameModes/ModeBasement.h"
#include "../Robot/Robot.h"
#include "../Robot/Server.h"
#include "../Commands/ICommand.h"
//#include "../Console/Parser.h"
//#include "../Console/MapLoader.h"
//#include "../GameModes/InactiveMode.h"
//#include "../GameModes/AutoGrab.h"

//#include "../GameModes/ManualMode.h"
#include "View.h"

class Parser;
class MapLoader;
class ManualMode;
class GameArea;
//class Parser;

//#include "../Robot/Collector.h"

/* class World;
class Player;
class ModeBasement;
class View;
class Parser;
class ICommand;
class Server;
class Server;
class GameArea;
class Robot; */

using namespace std;

class Manager
{
public:
    Manager(size_t argc, char **argv);
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
    View gameView;
}; //TEST