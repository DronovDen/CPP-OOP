#pragma once

#include "Coordinates.h"
#include "Cell.h"
#include "cstdio"
#include "cstdlib"
#include "iostream"
#include "vector"
#include "ctime"
//#include "MapLoader.h"

class GameArea
{
public:
    GameArea(std::vector<std::vector<Cell>> &map);
    GameArea(const int &x_size, const int &y_size);
    GameArea();
    ~GameArea();

    void CreateEmptyMap();
    void CreateRandomGlobalMap();

    void SetDiamondsAmount(const int &diamondsAmount) { this->diamondsAmount = diamondsAmount; };
    void SetBombsAmount(const int &bombAmount) { this->bombsAmount = bombAmount; };

    void SetVisibleGlobalMapWidth(const int &visibleGlobalMapX) { this->visibleGlobalMapWidth = visibleGlobalMapWidth; };
    void SetVisibleGlobalMapHeight(const int &visibleGlobalMapHeight) { this->visibleGlobalMapHeight = visibleGlobalMapHeight; };

    int GetDiamondsAmount() { return this->diamondsAmount; }
    int GetBombsAmount() { return this->bombsAmount; }

    int GetVisibleGlobalMapWidth() { return visibleGlobalMapWidth; };
    int GetVisibleGlobalMapHeight() { return visibleGlobalMapHeight; };

    int getMapSizeX() { return mapWidth; };
    int getMapSizeY() { return mapHeight; };
    void SetMapWidth(const int &width) { this->mapWidth = mapHeight; };
    void setMapHeight(const int &height) { this->mapHeight = height; };

    void Resize(int x, int y);

    bool IsCellOnMap(Coordinates point) const;

    int GetWidth() const;
    int GetHeight() const;

    Cell GetCell(int x, int y);
    Cell GetCell(const Coordinates &point);
    const Cell &GetCell(int x, int y) const;
    void SetCell(const Coordinates &coordinates, const CellType &cell);

    const std::vector<std::vector<Cell>> &GetMap() const;

private:
    int mapWidth;
    int mapHeight;

    int visibleGlobalMapHeight;
    int visibleGlobalMapWidth;

    int diamondsAmount;
    int bombsAmount;
    int rockAmount;

    std::vector<std::vector<Cell>> map;
};
