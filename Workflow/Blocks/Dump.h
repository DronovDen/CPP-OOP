#pragma once
/* #include "IWorker.h"
#include "BlockMaker.h" */
#include "Replace.h"

class Dump : public IWorker
{
public:
    void work(std::vector<std::string> params, std::string &text);
    size_t GetNumberOfParams() { return 1; };
    Dump() = default;
    BLOCK_TYPE GetBlockType() { return BLOCK_TYPE::MODIFICATION; };
};