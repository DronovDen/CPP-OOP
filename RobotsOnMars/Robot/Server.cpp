#include "Server.h"
//#include "Robot.h"
#include "../Robot/Sapper.h"
#include "../Robot/Collector.h"

class Collector;
class Sapper;

bool Server::IsCellAvaliable(const Coordinates &coordinates) const
{
    for (auto i : robotsCoordinates)
    {
        if (i.first == coordinates)
        {
            return false;
        }
    }
    return true;
}

void Server::NotifyRobotCreated(Robot *robot, const Coordinates &coordinates)
{
    robotsCoordinates.push_back(make_pair(coordinates, robot));
    vector<pair<Coordinates, CellType>> data;
    robotsCache.emplace(robot, data);
}

void Server::NotifyRobotDeleted(Robot *robot, const Coordinates &coordinates)
{
    for (size_t i = 0; i < robotsCoordinates.size(); ++i)
    {
        if (robotsCoordinates.at(i).first == coordinates)
        {
            robotsCoordinates.erase(robotsCoordinates.begin() + i);
        }
    }
    robotsCache.erase(robot);
    actualGameArea->GetCell(coordinates).SetType(CellType::EMPTY);
}

void Server::NotifyCellScanned(Robot *robot, const pair<Coordinates, CellType> scannedCell)
{
    //const_cast<Robot*>(robot);
    robotsCache.find(robot)->second.push_back(scannedCell);
    if (scannedCell.second == CellType::DIAMOND)
        diamondsAvaliable.push_back(scannedCell.first);
    if (scannedCell.second == CellType::BOMB)
        bombsAvaliable.push_back(scannedCell.first);
}

void Server::NotifyDiamondCollected(Robot *robot, const Coordinates &coordinates)
{
    robotsCache.find(robot)->second.push_back(make_pair(coordinates, CellType::EMPTY));
    for (size_t i = 0; i < diamondsAvaliable.size(); ++i)
    {
        if (diamondsAvaliable.at(i) == coordinates)
        {
            diamondsAvaliable.erase(diamondsAvaliable.begin() + i);
            this->collectedDiamonds++;
        }
    }
}

void Server::NotifyBombDefused(Robot *robot, const Coordinates &coordinates)
{
    robotsCache.find(robot)->second.push_back(make_pair(coordinates, CellType::EMPTY));
    for (size_t i = 0; i < bombsAvaliable.size(); ++i)
    {
        if (bombsAvaliable.at(i) == coordinates)
        {
            bombsAvaliable.erase(bombsAvaliable.begin() + i);
        }
    }
}

void Server::NotifyRobotMoved(const Robot *robot, const Coordinates &prevCoordinates, const Coordinates &newCoordinates)
{
    for (size_t i = 0; i < robotsCoordinates.size(); ++i)
    {
        if (robotsCoordinates.at(i).first == prevCoordinates)
        {
            robotsCoordinates.at(i).first = newCoordinates;
        }
    }
}

void Server::applyOthersRobotsChanges()
{
    for (auto i : robotsCoordinates)
    {
        GameArea *internalMap = i.second->GetExploredArea();
        for (auto j : robotsCache)
        {
            if (i.second != j.first) //i.second = Robot*
            //j.first = Robot* in robotChanges map
            //if there is only one robot - ignore
            {
                for (auto k : j.second) //j.second = vector<std::pair<Coordinates, CellType>>>
                {
                    if (k.second == CellType::EMPTY && internalMap->GetCell(k.first).GetType() != CellType::DIAMOND)
                    {
                        internalMap->GetCell(k.first).SetType(CellType::EMPTY);
                    }
                    if (k.second == CellType::EMPTY && internalMap->GetCell(k.first).GetType() != CellType::BOMB)
                    {
                        internalMap->GetCell(k.first).SetType(CellType::EMPTY);
                    }
                    else
                    {
                        internalMap->GetCell(k.first).SetType(k.second);
                    }
                }
            }
        }

        for (auto t : robotsCoordinates)
        {
            if (i.second != t.second)
            {
                if (dynamic_cast<Collector *>(t.second) && internalMap->GetCell(t.first.x, t.first.y).GetType() != CellType::COLLECTOR)
                {
                    internalMap->GetCell(t.first).SetType(CellType::COLLECTOR);
                }
                if (dynamic_cast<Sapper *>(t.second) && internalMap->GetCell(t.first.x, t.first.y).GetType() != CellType::SAPPER)
                {
                    internalMap->GetCell(t.first).SetType(CellType::SAPPER);
                }
            }
        }
    }

    for (auto i = robotsCache.begin(); i != robotsCache.end(); ++i)
    {
        i->second.clear();
    }

    SetActualGameArea(robotsCoordinates.at(0).second->GetExploredArea());
}