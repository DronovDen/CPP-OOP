//#include "IBlockMaker.h"
#include "BlockFactory.h"

template <class T>
class BlockMaker : public IBlockMaker
{
public:
    BlockMaker(std::string BlockName)
    {
        BlockFactory::Instance().RegisterNewBlock(BlockName, this);
    }
    virtual IWorker *create() const
    {
        return new T();
    }
};