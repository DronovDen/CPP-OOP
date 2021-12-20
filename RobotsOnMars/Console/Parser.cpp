#include "Parser.h"

Parser::Parser() : commandIdx{0} {}

ICommand *Parser::GetCurrentCommand(Manager *manager, bool need)
{
    getCommandLine(cin);
    ICommand *currentCommand = parseCommand(manager, need);
    return currentCommand;
}

void Parser::split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    currentParsedCommand = tokens;
}

void Parser::getCommandLine(std::istream &cin)
{
    string box = "";
    getline(cin, box);
    //split(box, ' ');
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(box);
    while (std::getline(tokenStream, token, ' '))
    {
        tokens.push_back(token);
    }
    currentParsedCommand = tokens;
}
