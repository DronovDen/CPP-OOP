#pragma once
#include "Grep.h"

class Sort : public IWorker
{
public:
    void work(std::vector<std::string> params, std::string &text);
    size_t GetNumberOfParams() { return 0; };
    Sort() = default;
    BLOCK_TYPE GetBlockType() { return BLOCK_TYPE::MODIFICATION; };
};