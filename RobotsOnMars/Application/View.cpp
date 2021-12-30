#include "View.h"
#include <iostream>

void View::Render(Robot *robot, GameArea &map)
{
    system("cls");

    if (robot->GetCoordinates().x >= map.GetVisibleGlobalMapWidth() - 1)
    {
        this->offsetX = robot->GetCoordinates().x - map.GetVisibleGlobalMapWidth() + 5;
        /*if (diff + robot->GetCoordinates().x < map.getMapSizeX())
        {
            this->offsetX = diff;
        }*/
    }
    else if (robot->GetCoordinates().x < map.GetVisibleGlobalMapWidth() - 1)
    {
        this->offsetX = 0;
    }

    if (robot->GetCoordinates().y >= map.GetVisibleGlobalMapHeight() - 1)
    {
        this->offsetY = robot->GetCoordinates().y - map.GetVisibleGlobalMapHeight() + 5;
        /*if (diff + robot->GetCoordinates().y < map.getMapSizeY())
        {
            this->offsetY = diff;
        }*/
    }
    else if (robot->GetCoordinates().x < map.GetVisibleGlobalMapWidth())
    {
        this->offsetY = 0;
    }

    //maybe this->offset % map.GetVisibleGlobalMapHeight() ????
    size_t maxY;
    size_t maxX;
    if (offsetY + map.GetVisibleGlobalMapHeight() <= map.getMapSizeY())
        maxY = map.GetVisibleGlobalMapHeight() + offsetY;
    else
    {
        //maxY = map.getMapSizeY();
        maxY = map.getMapSizeY() - map.GetVisibleGlobalMapHeight();
    }
    if (offsetX + map.GetVisibleGlobalMapWidth() <= map.getMapSizeX())
        maxX = map.GetVisibleGlobalMapWidth() + offsetX;
    else 
    {
        //maxX = map.getMapSizeX();
        maxX = map.getMapSizeX() - map.GetVisibleGlobalMapWidth();
    }

    for (size_t i = this->offsetY; i < maxY; ++i)
    {
        for (size_t j = this->offsetX; j < maxX; ++j)
        {
            Coordinates point(j, i);
            if (map.GetCell(point).GetType() == CellType::EMPTY)
            {
                std::cout << ".";
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