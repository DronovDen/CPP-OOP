#pragma once

//#include "Robot/Robot.h"
#include "GameArea.h"
#include <string>

class World
{
public:
    World(GameArea &gameArea);

    const GameArea &GetGameArea() const;

    Cell &GetCell(size_t x, size_t y);

    size_t GetWidth() const;
    size_t GetHeight() const;

private:
    GameArea gameArea;
};