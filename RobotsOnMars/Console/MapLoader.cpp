#include "MapLoader.h"

MapLoader::MapLoader(std::string fileName)
    : mapFile(fileName)
{
}

GameArea MapLoader::Load() const
{
    std::ifstream input(mapFile);
    if (!input.is_open())
        throw std::runtime_error("Can't open map file");

    int width;
    int height;

    input >> width;
    input >> height;

    if (width == 0 || height == 0)
        throw std::runtime_error("Map size can't be zero");

    std::vector<std::vector<Cell>> map(height, std::vector<Cell>(width));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            char symbol;
            input >> symbol;
            map[i][j].SetType(ConvertCellTypes(symbol));
        }
    }

    GameArea Map(map);
    Map.SetMapWidth(width);
    Map.setMapHeight(height);
    return Map;
}

CellType MapLoader::ConvertCellTypes(char symb)
{
    if (symb == ' ')
        return CellType::EMPTY;
    if (symb == '^')
        return CellType::ROCK;
    if (symb == 'D')
        return CellType::DIAMOND;
    if (symb == '*')
        return CellType::BOMB;

    return CellType::UNKNOWN;
}