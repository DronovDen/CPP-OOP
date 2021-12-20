#include "GameArea.h"
#include <memory>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <stdexcept>

GameArea::GameArea(std::vector<std::vector<Cell>> &map)
    : map(std::move(map))
{
}

GameArea::GameArea(const size_t &x_size, const size_t &y_size)
{
    mapWidth = x_size;
    mapHeight = y_size;
    diamondsAmount = 0;
    bombsAmount = 0;
    visibleGlobalMapWidth = (x_size >= 15) ? 15 : x_size % 15;
    visibleGlobalMapHeight = (y_size >= 15) ? 15 : y_size % 15;

    createEmptyMap();
}

GameArea::GameArea()
{
    mapWidth = 20;
    mapHeight = 20;
    diamondsAmount = 0;
    bombsAmount = 0;
    visibleGlobalMapHeight = 10;
    visibleGlobalMapWidth = 10;
}

void GameArea::createEmptyMap()
{
    std::vector<std::vector<Cell>> mapHolder;
    Resize(mapWidth, mapHeight);

    for (size_t i = 0; i < mapHeight; ++i)
    {
        for (size_t j = 0; j < mapWidth; ++j)
        {
            mapHolder[i][j] = Cell(CellType::UNKNOWN);
        }
    }
    map = mapHolder;
}

void GameArea::createRandomGlobalMap()
{
    srand(time(nullptr));

    createEmptyMap();

    for (size_t i = 0; i < this->mapHeight; ++i)
    {
        for (size_t j = 0; j < this->mapWidth; ++j)
        {
            map[i][j] = CellType::EMPTY;
        }
    }

    this->diamondsAmount = 20;
    this->bombsAmount = 10;
    this->rockAmount = 10;

    size_t currentDiamondsAmount = 0;
    size_t currentBombAmount = 0;
    size_t currentRockAmount = 0;
    

    for (int i = 0; i < 20; ++i)
    {
        if (currentRockAmount < this->rockAmount)
        {
            map[rand() % 15][rand() % 15] = (CellType::ROCK);
            currentRockAmount++;
        }
        if (currentDiamondsAmount < this->diamondsAmount)
        {
            map[rand() % 15][rand() % 15] = (CellType::DIAMOND);
            currentDiamondsAmount++;
        }
        if (currentBombAmount < this->bombsAmount)
        {
            map[rand() % 15][rand() % 15] = (CellType::BOMB);
            currentBombAmount++;
        }
    }
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

Cell GameArea::GetCell(Coordinates point)
{
    if (point.x >= map.size() || point.y >= map[point.x].size())
        throw std::runtime_error("Invalid cell coordinates");
    return map[point.y][point.x];
}

Cell GameArea::GetCell(size_t x, size_t y)
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

void GameArea::SetCell(const Coordinates& coordinates, const CellType& cell) {
    map[coordinates.y][coordinates.x] = cell;
}

const std::vector<std::vector<Cell>> &GameArea::GetMap() const
{
    return map;
}
