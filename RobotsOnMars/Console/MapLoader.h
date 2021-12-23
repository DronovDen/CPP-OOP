#pragma once
#include "../World/Cell.h"
#include "../World/GameArea.h"

//class GameArea;

class MapLoader
{
public:
    MapLoader(std::string fileName);

    GameArea Load() const;

private:
    static CellType ConvertCellTypes(char symb);

    std::string mapFile;
};