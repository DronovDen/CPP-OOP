#include "World.h"
//#include "GameArea/GameAreaLoader.h"

World::World(GameArea &gameArea)
    : gameArea(std::move(gameArea))
{
}

const GameArea &World::GetGameArea() const
{
    return gameArea;
}

Cell &World::GetCell(size_t x, size_t y)
{
    return gameArea.GetCell(x, y);
}

std::size_t World::GetWidth() const
{
    return gameArea.GetWidth();
}

std::size_t World::GetHeight() const
{
    return gameArea.GetHeight();
}
