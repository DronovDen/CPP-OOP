#include "BlockFactory.h"

BlockFactory &BlockFactory::Instance()
{
    static BlockFactory factory;
    return factory;
}

IWorker *BlockFactory::CreateBlock(std::string BlockName)
{
    auto block = this->BlockMap.find(BlockName);
    IBlockMaker *blockMaker = block->second;
    return blockMaker->create();
}

void BlockFactory::RegisterNewBlock(std::string NewBlockName, IBlockMaker *NewBlock)
{
    if (BlockMap.find(NewBlockName) != BlockMap.end())
    {
        throw std::runtime_error("Multiple registering of block");
    }
    BlockMap[NewBlockName] = NewBlock;
}