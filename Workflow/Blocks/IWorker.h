#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

enum class BLOCK_TYPE
{
    INPUT,
    OUTPUT,
    MODIFICATION
};

class IWorker
{
public:
    virtual void work(std::vector<std::string> params, std::string &text) = 0;
    virtual size_t GetNumberOfParams() = 0;
    virtual ~IWorker() = default;
    virtual BLOCK_TYPE GetBlockType() = 0;
};
