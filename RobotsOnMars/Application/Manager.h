#pragma once
//#include "World/GameArea.h"
//#include "GameModes/ModeBasement.h"
//#include "Commands/ICommand.h"
//#include "Console/ConsoleArgs.h"
//#include "Console/CommandParser.h"
//#include <map>

class World;
class Player;
class ModeBasement;
class IView;
class CommandParser;
class ICommand;
class Server;
class Server;
class GameArea;
class Robot;

using namespace std;

class Manager
{
public:
    Manager(ConsoleArgs &args);
    ~Manager();

    void ExecuteGame();
    bool DoStep();

    GameArea *GetGlobalMap() { return &globalMap; }
    GameArea GetCurrentMap() { return *currentMap; }
    //GameArea* GetCurrentMap() {return currentMap;};
    auto GetPossibleModes() { return &possibleModes; }
    CommandParser *GetCommandParser() { return commandParser; }
    auto GetServer() { return server; }
    auto GetActiveRobots() { return &activeRobots; };

private:
    GameArea globalMap;
    GameArea *currentMap;
    map<string, ModeBasement *> possibleModes;
    vector<pair<ModeBasement *, Robot *>> activeRobots;
    CommandParser *commandParser;
    ICommand *currCommand;
    Server *server;
    IView gameView;
};