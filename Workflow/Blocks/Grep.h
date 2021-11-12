#pragma once
#include "WriteFile.h"

class Grep : public IWorker
{
private:
    bool ContainsWord(std::string text, std::string word);
public:
    void work(std::vector<std::string> params, std::string &text);
    size_t GetNumberOfParams() { return 1; };
    Grep() = default;
    BLOCK_TYPE GetBlockType() { return BLOCK_TYPE::MODIFICATION; };
};