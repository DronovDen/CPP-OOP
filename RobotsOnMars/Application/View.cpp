#include "View.h"
#include <iostream>

void View::Render(Robot *robot, GameArea &map)
{
    system("cls");

    if (robot->GetCoordinates().x >= map.GetVisibleGlobalMapWidth() - 1)
    {
        long diff = robot->GetCoordinates().x - map.GetVisibleGlobalMapWidth() + 2;
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
        this->offsetY = 0;
    }
    for (size_t i = this->offsetY; i < map.GetVisibleGlobalMapHeight() + this->offsetY; ++i)
    {
        for (size_t j = this->offsetX; j < map.GetVisibleGlobalMapWidth() + this->offsetX; ++j)
        {
            Coordinates posize_t(j, i);
            if (map.GetCell(posize_t).GetType() == CellType::EMPTY)
            {
                std::cout << ".";
            }
            else if (map.GetCell(posize_t).GetType() == CellType::ROCK)
            {
                std::cout << "^";
            }
            else if (map.GetCell(posize_t).GetType() == CellType::DIAMOND)
            {
                std::cout << "D";
            }
            else if (map.GetCell(posize_t).GetType() == CellType::BOMB)
            {
                std::cout << "*";
            }
            else if (map.GetCell(posize_t).GetType() == CellType::COLLECTOR)
            {
                std::cout << "C";
            }
            else if (map.GetCell(posize_t).GetType() == CellType::SAPPER)
            {
                std::cout << "S";
            }
            else if (map.GetCell(posize_t).GetType() == CellType::UNKNOWN)
            {
                std::cout << "?";
            }
        }
        std::cout << std::endl;
    }
}