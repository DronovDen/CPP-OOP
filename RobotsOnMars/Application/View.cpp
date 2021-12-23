#include "View.h"
#include <iostream>

void View::Render(Robot *robot, GameArea &map)
{
    system("cls");

    if (robot->GetCoordinates().x >= map.GetVisibleGlobalMapWidth() - 1)
    {
        long long diff = robot->GetCoordinates().x - map.GetVisibleGlobalMapWidth() + 2;
        if (diff + robot->GetCoordinates().x < map.getMapSizeX())
        {
            this->offsetX = diff;
        }
    }
    else if (robot->GetCoordinates().x < map.GetVisibleGlobalMapWidth() - 1)
    {
        this->offsetX = 0;
    }

    if (robot->GetCoordinates().y >= map.GetVisibleGlobalMapHeight() - 1)
    {
        long long diff = robot->GetCoordinates().y - map.GetVisibleGlobalMapHeight() + 2;
        if (diff + robot->GetCoordinates().y < map.getMapSizeY())
        {
            this->offsetY = diff;
        }
    }
    else if (robot->GetCoordinates().x < map.GetVisibleGlobalMapWidth())
    {
        this->offsetX = 0;
    }
    for (int i = this->offsetY; i < map.GetVisibleGlobalMapWidth() + this->offsetY; ++i)
    {
        for (int j = this->offsetX; j < map.GetVisibleGlobalMapHeight() + this->offsetY; ++j)
        {
            Coordinates point(i, j);
            if (map.GetCell(point).GetType() == CellType::EMPTY)
            {
                std::cout << " ";
            }
            else if (map.GetCell(point).GetType() == CellType::ROCK)
            {
                std::cout << "^";
            }
            else if (map.GetCell(point).GetType() == CellType::DIAMOND)
            {
                std::cout << "D";
            }
            else if (map.GetCell(point).GetType() == CellType::BOMB)
            {
                std::cout << "*";
            }
            else if (map.GetCell(point).GetType() == CellType::COLLECTOR)
            {
                std::cout << "C";
            }
            else if (map.GetCell(point).GetType() == CellType::SAPPER)
            {
                std::cout << "S";
            }
            else if (map.GetCell(point).GetType() == CellType::UNKNOWN)
            {
                std::cout << "?";
            }
        }
        std::cout << std::endl;
    }
}