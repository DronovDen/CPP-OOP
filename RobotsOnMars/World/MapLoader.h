#pragma once
#include "Cell.h"


class MapLoader
{
public:
    MapLoader(std::string fileName);

    std::vector<std::vector<Cell>> Load() const;

private:
    static CellType ConvertCellTypes(char symb);

    std::string mapFile;
};