#include "CommandParser.h"
#include <iostream>
#include <string>

CommandParser::CommandParser()
{
    InitializeCommandCreators();
}

CommandParser::~CommandParser()
{
}

ICommand *CommandParser::Parse(std::istream &stream)
{
    std::string commandType;
    stream >> commandType;

    const auto creatorIt = commandCreators.find(commandType);
    if (creatorIt != std::end(commandCreators))
        return creatorIt->second(stream);
    //throw std::runtime_error("Invalid command: " + commandType);
    std::cout << "Invalid command: " << commandType << std::endl;
    return nullptr;
}

void CommandParser::InitializeCommandCreators()
{
    commandCreators.emplace("MOVE", [](std::istream &stream)
                            { return ParseMove(stream); });
    commandCreators.emplace("SCAN", [](std::istream &)
                            { return new Scan; });
    commandCreators.emplace("GRAB", [](std::istream &)
                            { return new Grab; });
    commandCreators.emplace("SET_MODE", [](std::istream &stream)
                            { return ParseMode(stream); });
    commandCreators.emplace("SAPPER_ON", [](std::istream &stream)
                            { return new SapperSwitch(true); });
    commandCreators.emplace("SAPPER_OFF", [](std::istream &stream)
                            { return new SapperSwitch(false); });
}

ICommand *CommandParser::ParseMove(std::istream &stream)
{
    std::string directionStr;
    stream >> directionStr;
    auto direction = Direction::Count;
    if (directionStr == "D")
        direction = Direction::Down;
    if (directionStr == "U")
        direction = Direction::Up;
    if (directionStr == "R")
        direction = Direction::Right;
    if (directionStr == "L")
        direction = Direction::Left;

    return new Move(direction);
}

ICommand *CommandParser::ParseMode(std::istream &stream)
{
    std::string modeStr;
    stream >> modeStr;
    std::any argument = 0;
    auto mode = Mode::Count;
    if (modeStr == "manual")
    {
        mode = Mode::MANUAL;
    }
    else if (modeStr == "auto")
    {
        mode = Mode::GRAB;
    }
    else if (modeStr == "scan")
    {
        mode = Mode::SCAN;
        int n;
        stream >> n;
        argument = n;
    }
    return new ChangeMode(mode, std::move(argument));
}

/*ICommand *CommandParser::ParseSapper(std::istream &stream)
{
    std::string switcher;
    stream >> switcher;

    if (switcher == "ON")
        return new SapperSwitch(true);
    if (switcher == "OFF")
        return new SapperSwitch(false);

    return nullptr;
}*/
