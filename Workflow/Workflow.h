#pragma once
#include <iostream>

class Workflow
{
public:
    void execute(std::string schemeFile);
    ~Workflow() = default;
};
