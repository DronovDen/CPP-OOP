#pragma once
#include "Blocks/Dump.h"
//#include "BlockFactory.h"
//#include <map>

using namespace std;

class Parser
{
private:
    vector<size_t> schemeDescription;
public:
    map<size_t, pair<string, vector<string>>> parse(BlockFactory *bf, string schemeFile);
    vector<size_t> GetSchemeDescription();
};