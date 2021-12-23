#pragma once
#include "../World/GameArea.h"
#include "../Commands/SapperManagement.h"
#include "../Robot/Direction.h"
//#include "../Commands/ICommand.h"
//#include <unordered_map>
//#include <map>
#include <sstream>
#include <vector>
#include <string>
//#include <functional>
//#include <iostream>

class Manager;
class ICommand;


class Parser
{

public:
    Parser();
    ICommand *GetCurrentCommand(Manager *manager, bool necessary);
    ICommand *ParseCommand(Manager *manager, bool necessary);
    //ICommand *Parse(std::istream &stream);

    std::string GetNextWord();
    //int GetNextNumber();
    Direction ParseDirection(char dir);
    void ClearCommandsBuffer();
    //void split(const std::string &s, char delimiter);
    void GetConsoleArgs(std::istream &cin);

private:
    int commandIdx;
    int mapWidth;
    int mapHeight;
    std::vector<std::string> CommandsBuffer;
};
