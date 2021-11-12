#include "Grep.h"

static BlockMaker<Grep> GrepBlockMaker("grep");

bool Grep::ContainsWord(std::string text, std::string word)
{
    /* bool contains = false;
    for (size_t i = 0; i < text.size(); i++)
    {
        if ((i + word.size() - 1 > text.size()) && (contains == false))
			break;

		if (text[i] == word[0])
		{
			for (size_t j = 1; j < word.size(); j++)
			{
				if (text[i + j] == word[j])
				{
					if (j == word.size() - 1)
						contains = true;
				}
			}
		}
    }
    return contains; */

    bool contains = false;
    if (text.find(word) != std::string::npos)
    {
        contains = true;
    }
    return contains;
}
void Grep::work(std::vector<std::string> params, std::string &text)
{
    if (params.empty())
    {
        throw std::runtime_error("Too few arguments to find in text!");
    }

    if (text.empty())
    {
        throw std::runtime_error("Work text is empty!");
    }

    //params[0] = word
    if (params[0] == "")
    {
        throw std::runtime_error("Word to find is empty!");
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
    std::string ret_text = "";
    for (i = 0; i < strings.size(); i++)
    {
        if (ContainsWord(strings[i], params[0]))
        {
            ret_text += strings[i];
        }
    }
    text = ret_text;
}