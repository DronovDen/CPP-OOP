#pragma once
#include <sstream>
#include <vector>
#include <string>

class ManualMode;
class Manager;
class ICommand;

class Parser
{
public:
    Parser();
    ICommand *GetCurrentCommand(Manager *manager, bool necessary);
    ICommand *ParseCommand(Manager *manager, bool necessary);
    std::string GetNextWord();
    ICommand *ParseMovement(char dir);
    void ClearCommandsBuffer();
    void GetConsoleArgs(std::istream &cin);

private:
    size_t commandIdx;
    size_t mapWidth;
    size_t mapHeight;
    std::vector<std::string> CommandsBuffer;
};
