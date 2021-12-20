#pragma once

#include "MapLoader.h"
#include <vector>
#include "Coordinates.h"

class GameArea
{
public:
    GameArea(std::vector<std::vector<Cell>> &map);
    GameArea(const size_t &x_size, const size_t &y_size);
    GameArea();
    ~GameArea();

    void createEmptyMap();
    void createRandomGlobalMap();

    void SetDiamondsAmount(const size_t &diamondsAmount) { this->diamondsAmount = diamondsAmount; };
    void SetBombsAmount(const size_t &bombAmount) { this->bombsAmount = bombAmount; };

    void SetVisibleGlobalMapWidth(const size_t &visibleGlobalMapX) { this->visibleGlobalMapWidth = visibleGlobalMapWidth; };
    void SetVisibleGlobalMapHeight(const size_t &visibleGlobalMapHeight) { this->visibleGlobalMapHeight = visibleGlobalMapHeight; };

    size_t GetDiamondsAmount() { return this->diamondsAmount; }
    size_t GetBombsAmount() { return this->bombsAmount; }

    size_t GetVisibleGlobalMapWidth() { return visibleGlobalMapWidth; };
    size_t GetVisibleGlobalMapHeight() { return visibleGlobalMapHeight; };

    size_t getMapSizeX() { return mapWidth; };
    size_t getMapSizeY() { return mapHeight; };

    void Resize(size_t x, size_t y);

    bool IsCellOnMap(Coordinates point) const;

    size_t GetWidth() const;
    size_t GetHeight() const;

    Cell GetCell(size_t x, size_t y);
    Cell GetCell(Coordinates point);
    const Cell &GetCell(size_t x, size_t y) const;
    void SetCell(const Coordinates &coordinates, const CellType &cell);

    const std::vector<std::vector<Cell>> &GetMap() const;

private:
    size_t mapWidth;
    size_t mapHeight;

    size_t visibleGlobalMapHeight;
    size_t visibleGlobalMapWidth;

    size_t diamondsAmount;
    size_t bombsAmount;
    size_t rockAmount;

    std::vector<std::vector<Cell>> map;
};
