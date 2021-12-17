#include "Sapper.h"
//#include "GameArea/World.h"

Sapper::Sapper(World &world, GameArea &exploredGameArea)
    : Robot(RobotType::SAPPER, world, exploredGameArea)
{
    SetPosition();
}

void Sapper::SetPosition()
{
    while (true)
    {
        size_t x = rand() % exploredGameArea.GetWidth();
        size_t y = rand() % exploredGameArea.GetHeight();
        Cell &cell = exploredGameArea.GetCell(x, y);
        if (CanBeSetOnCell(cell))
        {
            Move(x, y);
            break;
        }
    }
}

void Sapper::Defuse()
{
    ClearCell(CellType::BOMB);
}

bool Sapper::CanBeSetOnCell(const Cell &cell) const
{
    return (cell.GetType() != CellType::UNKNOWN && cell.GetType() != CellType::ROCK && cell.GetRobot() == nullptr);
}
