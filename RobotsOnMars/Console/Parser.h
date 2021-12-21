#pragma once
#include "Commands/ICommand.h"
#include "GameModes/ModeBasement.h"
#include "Commands/Scan.h"
#include "Commands/ChangeMode.h"
#include "Commands/Grab.h"
#include "Commands/Move.h"
#include "Commands/Quit.h"
#include "Commands/SapperManagement.h"
#include "GameModes/ManualMode.h"
#include <unordered_map>
#include <map>
#include <sstream>
#include <functional>
#include <iostream>

class Parser
{

public:
    Parser();
    ICommand *GetCurrentCommand(Manager *manager, bool necessary);
    ICommand *ParseCommand(Manager *manager, bool necessary);
    //ICommand *Parse(std::istream &stream);

    std::string GetNextWord();
    //size_t GetNextNumber();
    Direction ParseDirection(char dir);
    void ClearCommandsBuffer();
    //void split(const std::string &s, char delimiter);
    void GetConsoleArgs(std::istream &cin);

private:
    size_t commandIdx;
    size_t mapWidth;
    size_t mapHeight;
    vector<string> CommandsBuffer;
};
