#include "ConsoleArgs.h"
#include <stdexcept>

ConsoleArgs::ConsoleArgs(int argc, char **argv)
    : argsCount(argc), arguments(argv)
{
}

const char *ConsoleArgs::GetArgByIdx(unsigned index) const
{
    if (index >= argsCount)
        throw std::runtime_error("Console argument index out of range");
    return arguments[index];
}
