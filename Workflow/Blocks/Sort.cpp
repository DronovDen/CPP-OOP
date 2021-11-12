#include "Sort.h"

static BlockMaker<Sort> SortBlockMaker("sort");

void Sort::work(std::vector<std::string> params, std::string &text)
{
    if (text.empty())
    {
        throw std::runtime_error("Work text is empty!");
    }

    std::vector<std::string> strings;
    std::string currentStr = "";
    char currentSymb;
    size_t i = 0;
    while (i < text.size())
    {
        currentSymb = text.at(i);
        if ((currentSymb != '\n') && (i != text.size() - 1))
        {
            currentStr += currentSymb;
        }
        else
        {
            strings.push_back(currentStr + '\n');
            currentStr = "";
        }
        i++;
    }

    //Lexicographical sorting
    std::sort(strings.begin(), strings.end());
    std::string ret_string = "";
    for (size_t i = 0; i < strings.size(); i++)
    {
        ret_string += strings[i];
    }
    text = ret_string;
}