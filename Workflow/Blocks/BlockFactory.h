#pragma once
#include "IBlockMaker.h"

class BlockFactory
{
private:
    //string <- BlockName
    std::map<std::string, IBlockMaker *> BlockMap;
    //BlockFactory() = default;

public:
    static BlockFactory &Instance();
    IWorker *CreateBlock(std::string BlockName);
    void RegisterNewBlock(std::string NewBlockName, IBlockMaker *NewBlock);
};