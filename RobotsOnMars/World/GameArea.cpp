#include "GameArea.h"
#include <memory>
#include <stdexcept>

GameArea::GameArea(std::vector<std::vector<Cell>> &map)
    : map(std::move(map))
{
}

void GameArea::Resize(size_t x, size_t y)
{
    //constructor of vector with size = y that stores vectors of Cells
    map = std::vector<std::vector<Cell>>(y, std::vector<Cell>(x));
}

std::size_t GameArea::GetWidth() const
{
    return map.size();
}

std::size_t GameArea::GetHeight() const
{
    if (!map.empty())
    {
        return map[0].size();
    }
    else
        return 0;
}

bool GameArea::IsCellOnMap(size_t x, size_t y) const
{
    return (x < map.size() && y < map[0].size());
}

Cell &GameArea::GetCell(size_t x, size_t y)
{
    if (x >= map.size() || y >= map[x].size())
        throw std::runtime_error("Invalid cell coordinates");
    return map[y][x];
}

const Cell &GameArea::GetCell(size_t x, size_t y) const
{
    if (x >= map.size() || y >= map[x].size())
        throw std::runtime_error("Invalid cell coordinates");
    return map[y][x];
}

const std::vector<std::vector<Cell>> &GameArea::GetMap() const
{
    return map;
}
