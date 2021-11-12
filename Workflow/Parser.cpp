#include "Parser.h"

using namespace std;

vector<size_t> Parser::GetSchemeDescription()
{
    return schemeDescription;
}

map<size_t, pair<string, vector<string>>> Parser::parse(BlockFactory *bf, string schemeFileName)
{
    ifstream schemeFile;
    string current;
    size_t currBlockID;
    string currBlockName;
    vector<string> currParams;

    map<size_t, pair<string, vector<string>>> blocks;
    /*
    FOR EXAMPLE:
    "2 = writefile out_file.txt"
    blocks[2] = <"writefile", vector[0] = "out_file.txt">

    OR:
    10 =  replace word1 word2
    blocks[10] = <"replace", vector[0] = "word1", vector[1] = "word2">
    */

    schemeFile.open(schemeFileName);
    if (!schemeFile.is_open())
    {
        throw runtime_error("Can't open scheme file!");
    }

    schemeFile >> current;
    if (current != "desc")
    {
        throw runtime_error("Wrong scheme description!");
    }

    while (true)
    {
        currParams.clear();
        schemeFile >> current;

        if (current == "csed")
            break;

        currBlockID = stoi(current);
        schemeFile >> current; //skipping "="
        schemeFile >> current;
        currBlockName = current;

        IWorker *block;
        block = bf->CreateBlock(currBlockName);
        size_t currentParamsNum = block->GetNumberOfParams();

        for (size_t i = 0; i < currentParamsNum; i++)
        {
            schemeFile >> current;
            currParams.push_back(current);
        }
        blocks[currBlockID] = make_pair(currBlockName, currParams);

        delete block;
    }

    //1 -> 3 -> 10 -> 3 -> 2
    schemeDescription.clear(); //???
    while (schemeFile >> current)
    {
        if (current != "->")
        {
            schemeDescription.push_back(stoi(current));
        }
    }

    schemeFile.close();
    return blocks;
}
