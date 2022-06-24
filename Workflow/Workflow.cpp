#include "Workflow.h"
#include "Parser.h"

void Workflow::execute(std::string schemeFile)
{
    BlockFactory &bf = BlockFactory::Instance();
    Parser parser;
    //Blocks is a map of blocks with their unique parameters stored in vector of strings
    map<size_t, pair<string, vector<string>>> Blocks = parser.parse(&bf, schemeFile);

    //Vector for storing coomands executing order
    vector<size_t> chain = parser.GetSchemeDescription();

    IWorker *block;
    string text = ""; // workstring

    for (size_t i = 0; i < chain.size(); i++)
    {
        block = bf.CreateBlock(Blocks[chain[i]].first);
        block->work(Blocks[chain[i]].second, text);
        delete block;
    }

    //delete text;
}