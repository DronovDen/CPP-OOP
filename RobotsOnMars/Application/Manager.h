#pragma once
#include "World/GameArea.h"
#include "GameModes/ModeBasement.h"
#include "Commands/ICommand.h"
#include "Console/ConsoleArgs.h"
#include <map>

class World;
class Player;
class ModeBasement;
class IView;
class ICommandParser;
class CommandServer;
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
    GameArea &GetCurrentMap() { return *currentMap; }
    //GameArea* GetCurrentMap() {return currentMap;};
    auto GetPossibleModes() { return &possibleModes; }
    ICommandParser *GetCommandParser() { return commandParser; }
    auto GetServer() { return server; }
    auto GetActiveRobots() { return &activeRobots; };

private:
    GameArea globalMap;
    map<string, ModeBasement *> possibleModes;
    ICommandParser *commandParser;
    Server *server;
    IView gameView;

    GameArea *currentMap;
    vector<pair<ModeBasement *, Robot *>> activeRobots;

    //ICommand *command;
};