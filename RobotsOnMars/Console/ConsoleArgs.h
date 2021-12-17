#pragma once

class ConsoleArgs
{
public:
    ConsoleArgs(int argc, char **argv);

    const char *GetArgByIdx(unsigned index) const;

private:
    unsigned argsCount;
    char **arguments;
};
