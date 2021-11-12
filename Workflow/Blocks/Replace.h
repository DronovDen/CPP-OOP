#pragma once
/* #include "IWorker.h"
#include "BlockMaker.h"
#include <string>
#include <vector>
#include <algorithm> */
#include "Sort.h"

using namespace std;

class Replace : public IWorker
{
public:
    void work(std::vector<std::string> params, std::string &text);
    size_t GetNumberOfParams() { return 2; };
    Replace() = default;
    BLOCK_TYPE GetBlockType() { return BLOCK_TYPE::MODIFICATION; };
};