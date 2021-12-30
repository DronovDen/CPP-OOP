#pragma once
#include <map>
#include "../GameModes/ModeBasement.h"
#include "../Robot/Robot.h"
#include "../Robot/Server.h"
#include "../Commands/ICommand.h"
#include "View.h"

class Parser;
class MapLoader;
class ManualMode;
class GameArea;

using namespace std;

class Manager
{
public:
    Manager();
    ~Manager();

    void ExecuteGame();
    bool DoStep();

    GameArea *GetGlobalMap() { return &globalMap; }
    GameArea GetCurrentMap() { return *currentMap; }

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
};