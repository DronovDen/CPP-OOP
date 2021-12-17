#pragma once

//#include "Cell.h"
#include <vector>
#include <string>
#include <fstream>

class MapLoader
{
public:
    MapLoader(std::string fileName);

    std::vector<std::vector<Cell>> Load() const;

private:
    static CellType ConvertCellTypes(char symb);

    std::string mapFile;
};