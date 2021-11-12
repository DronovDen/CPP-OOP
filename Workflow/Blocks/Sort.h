#pragma once
/* #include "IWorker.h"
#include "BlockMaker.h"
#include <string>
#include <vector>
#include <algorithm> */
#include "Grep.h"

class Sort : public IWorker
{
private:
    bool isLonger(std::string str1, std::string str2);
    void swap(std::string str1, std::string str2);

public:
    void work(std::vector<std::string> params, std::string &text);
    size_t GetNumberOfParams() { return 0; };
    Sort() = default;
    BLOCK_TYPE GetBlockType() { return BLOCK_TYPE::MODIFICATION; };
};