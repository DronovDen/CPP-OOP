#include "Replace.h"

static BlockMaker<Replace> ReplaceBlockMaker("replace");

void Replace::work(vector<string> params, string &text)
{
    if (text.empty())
    {
        throw runtime_error("Work text is empty!");
    }
    
    //params[0] == word1
    //params[1] == word2
    if (params.size() != 2)
    {
        throw runtime_error("Too few parameters to replace!");
    }
    if (params[0].size() != params[1].size())
    {
        throw runtime_error("Words have different sizes!");
    }
    
    string oldWord = params[0];
    string newWord = params[1];

    size_t pos = text.find(oldWord);
    while (pos != string::npos)
    {
        text.replace(pos, oldWord.size(), newWord);
        pos = text.find(oldWord, pos); //searching oldWord after pos
    }
}