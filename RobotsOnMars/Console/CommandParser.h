#pragma once

#include "Commands/ICommand.h"
#include "GameModes/ModeBasement.h"
#include "Commands/Scan.h"
#include "Commands/ChangeMode.h"
#include "Commands/Grab.h"
#include "Commands/Move.h"
#include "Commands/SapperSwitch.h"
#include <unordered_map>
#include <map>
#include <functional>

enum class CommandType : unsigned char;

class CommandParser
{
    //using TCreator = std::function<ICommand *(std::istream &stream)>;

public:
    CommandParser();
    ~CommandParser();
    ICommand *Parse(std::istream &stream);

private:
    void InitializeCommandCreators();

    static ICommand *ParseMove(std::istream &stream);
    static ICommand *ParseMode(std::istream &stream);
    //static ICommand *ParseSapper(std::istream &stream);

    std::map<std::string, std::function<ICommand *(std::istream &stream)>> commandCreators;
};
