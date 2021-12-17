#pragma once

#include "Cell.h"
#include "MapLoader.h"
#include <vector>

class GameArea
{
public:
    GameArea(std::vector<std::vector<Cell>> &map);
    GameArea() = default;

    void Resize(size_t x, size_t y);

    bool IsCellOnMap(size_t x, size_t y) const;

    size_t GetWidth() const;
    size_t GetHeight() const;
    Cell &GetCell(size_t x, size_t y);
    const Cell &GetCell(size_t x, size_t y) const;
    const std::vector<std::vector<Cell>> &GetMap() const;

private:
    std::vector<std::vector<Cell>> map;
};
