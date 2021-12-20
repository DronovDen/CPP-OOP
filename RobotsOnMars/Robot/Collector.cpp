#include "Collector.h"
//#include "World/IWorld.h"
//#include "GameArea/Cell.h"
//#include "GameArea/GameArea.h"

Collector::Collector(GameArea gameArea, Server& server)
    : Robot(RobotType::COLLECTOR, world, gameArea, server)
{
}

void Collector::Collect()
{
    ClearCell(CellType::DIAMOND);
}

void Collector::Scan() const
{
    ScanCell(position.x - 1, position.y);
    ScanCell(position.x + 1, position.y);

    ScanCell(position.x, position.y + 1);
    ScanCell(position.x, position.y - 1);
}

bool Collector::CanBeSetOnCell(const Cell &cell) const
{
    return (cell.GetType() != CellType::ROCK && cell.GetType() != CellType::BOMB && cell.GetRobot() == nullptr);
}

//for collector it's BAD to go on bomb
bool Collector::AvailableForConcrete(size_t x, size_t y) const
{
    return (exploredGameArea.GetCell(x, y).GetType() != CellType::BOMB);
}

void Collector::ScanCell(size_t x, size_t y) const
{
    if (x >= world.GetWidth() || y >= world.GetHeight())
        return;
    exploredGameArea.GetCell(x, y).SetType(world.GetCell(x, y).GetType());
}
