#pragma once
#include "BlockMaker.h"

class ReadFile : public IWorker
{
public:
    void work(std::vector<std::string> params, std::string &text);
    size_t GetNumberOfParams() { return 1; };
    ReadFile() = default; //???
    BLOCK_TYPE GetBlockType() { return BLOCK_TYPE::INPUT; };
};