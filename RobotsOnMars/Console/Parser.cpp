#include "Parser.h"
#include "../Commands/ICommand.h"
#include "../Commands/Scan.h"
#include "../Commands/ChangeMode.h"
#include "../Commands/Grab.h"
#include "../Commands/Move.h"
#include "../Commands/Quit.h"
#include "../Commands/SapperManagement.h"
#include "../GameModes/ManualMode.h"
#include "../Application/Manager.h"

//class Manager;

Parser::Parser() : commandIdx{0}, mapWidth{15}, mapHeight{15} {}

ICommand *Parser::GetCurrentCommand(Manager *manager, bool necessary)
{
    GetConsoleArgs(cin);
    ICommand *currentCommand = ParseCommand(manager, necessary);
    return currentCommand;
}

ICommand *Parser::ParseCommand(Manager *manager, bool necessary)
{
    ICommand *currentCommand = nullptr;
    size_t activeRobotsNum = manager->GetActiveRobots()->size();
    Robot *robot = manager->GetActiveRobots()->at(0).second;
    ModeBasement *currentMode = manager->GetActiveRobots()->at(0).first;
    string word = "";
    size_t stepsNum = 0;

    if (necessary)
    {
        word = GetNextWord();
        if (word == "QUIT")
        {
            currentCommand = new Quit(manager);
        }
        else if (word == "SET_MODE")
        { //Mode parsing
            word = GetNextWord();
            if (word == "MANUAL" || word == "AUTOGRAB")
            {
                currentCommand = new ChangeMode(word, manager);
            }
            else if (word == "AUTOSCAN")
            {
                //stepsNum = getNextNumber();
                stepsNum = stoull(CommandsBuffer.at(commandIdx));
                currentCommand = new ChangeMode(word, manager, stepsNum);
            }
        }

        else if (word == "SAPPER")
        { //sapper switching
            word = GetNextWord();
            if (word == "ON" || word == "OFF")
            {
                currentCommand = new SapperManagement(word, manager);
            }
        }
        else if (dynamic_cast<ManualMode *>(currentMode))
        {
            if (word == "GRAB")
            {
                currentCommand = new Grab();
            }
            else if (word == "MOVE")
            {
                word = GetNextWord();
                if (word == "U" || word == "R" || word == "L" || word == "D")
                {
                    //Direction dir = ParseDirection(word[0]);
                    //currentCommand = new Move(dir);
                    currentCommand = ParseMovement(word[0]);
                }
            }
            else if (word == "SCAN")
            {
                currentCommand = new Scan();
            }
        }
        }

    ClearCommandsBuffer();
    return currentCommand;
}

string Parser::GetNextWord()
{
    string word = CommandsBuffer.at(commandIdx);
    commandIdx++;
    return word;
}

ICommand *Parser::ParseMovement(char dir)
{
    Direction where;
    if (dir == 'U')
        where = Direction::UP;
    else if (dir == 'D')
        where = Direction::DOWN;
    else if (dir == 'R')
        where = Direction::RIGHT;
    else if (dir == 'L')
        where = Direction::LEFT;
    /*switch (dir)
    {
    case 'U':
        where = Direction::UP;
    case 'D':
        where = Direction::DOWN;
    case 'L':
        where = Direction::LEFT;
    case 'R':
        where = Direction::RIGHT;
    }*/

    return new Move(where);
}

/* void Parser::split(const std::string &s, char delimiter)
{
    vector<string> ToParse;
    string token;
    istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        ToParse.push_back(token);
    }
    CommandsBuffer = ToParse;
} */

void Parser::GetConsoleArgs(std::istream &cin)
{
    string cache = "";
    getline(cin, cache);
    //split(cache, ' ');
    vector<string> ToParse;
    string token;
    std::istringstream tokenStream(cache);
    while (getline(tokenStream, token, ' '))
    {
        ToParse.push_back(token);
    }
    CommandsBuffer = ToParse;
}

void Parser::ClearCommandsBuffer()
{
    commandIdx = 0;
    CommandsBuffer.clear();
}
