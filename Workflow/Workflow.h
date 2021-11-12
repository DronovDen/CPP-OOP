#pragma once
/* #include <string>
#include <vector>
#include <map>
#include <fstream> */
#include <iostream>
/* #include "Parser.h"
#include "BlockFactory.h" */

class Workflow
{
public:
    void execute(std::string schemeFile);
    ~Workflow() = default;
};
