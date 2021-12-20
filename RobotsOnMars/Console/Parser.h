#pragma once

#include "Commands/ICommand.h"
#include "GameModes/ModeBasement.h"
#include "Commands/Scan.h"
#include "Commands/ChangeMode.h"
#include "Commands/Grab.h"
#include "Commands/Move.h"
#include "Commands/SapperManagement.h"
#include <unordered_map>
#include <map>
#include <functional>

class Parser
{

public:
    Parser();
    ICommand *GetCurrentCommand(Manager *manager, bool need);
    ICommand *ParseCommand(Manager *manager, bool need);
    //ICommand *Parse(std::istream &stream);

    std::string getNextWord();
    size_t getNextNumber();
    Direction decodeDirection(char dir);
    void clearCurrentParsedCommand();
    void split(const std::string &s, char delimiter);
    void getCommandLine(std::istream &cin);
    bool isValidMapSymbol(char &symbol);

private:
    size_t commandIdx;
    vector<string> CommandsToBeParsed;
};
