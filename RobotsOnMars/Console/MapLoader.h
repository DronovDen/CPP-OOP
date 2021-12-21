#pragma once
#include "Cell.h"
#include "World/GameArea.h"

class MapLoader
{
public:
    MapLoader(std::string fileName);

    GameArea Load() const;

private:
    static CellType ConvertCellTypes(char symb);

    std::string mapFile;
};