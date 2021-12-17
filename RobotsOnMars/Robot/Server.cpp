#include "Server.h"
#include "Robot.h"

bool Server::isCellAvaliable(const Coordinates &coordinates) const
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

void Server::notifyRobotCreated(Robot *robot, const Coordinates &coordinates)
{
    robotsCoordinates.push_back(make_pair(coordinates, robot));
    vector<pair<Coordinates, CellType>> box;
    robotsChanges.emplace(robot, box);
}

void Server::notifyRobotDeleted(Robot *robot, const Coordinates &coordinates)
{
    for (size_t i = 0; i < robotsCoordinates.size(); ++i)
    {
        if (robotsCoordinates.at(i).first == coordinates)
        {
            robotsCoordinates.erase(robotsCoordinates.begin() + i);
        }
    }
    robotsChanges.erase(robot);
    actualGameArea->GetCell(coordinates.x, coordinates.y).SetType(CellType::EMPTY);
}

void Server::notifyCellScanned(Robot *robot, const pair<Coordinates, CellType> scannedCell)
{
    robotsChanges.find(robot)->second.push_back(scannedCell);
    if (scannedCell.second == CellType::DIAMOND)
        diamondsAvaliable.push_back(scannedCell.first);
    if (scannedCell.second == CellType::BOMB)
        bombsAvaliable.push_back(scannedCell.first);
}

void Server::notifyDiamondCollected(Robot *robot, const Coordinates &coordinates)
{
    robotsChanges.find(robot)->second.push_back(make_pair(coordinates, CellType::EMPTY));
    for (size_t i = 0; i < diamondsAvaliable.size(); ++i)
    {
        if (diamondsAvaliable.at(i) == coordinates)
        {
            diamondsAvaliable.erase(diamondsAvaliable.begin() + i);
            this->collectedDiamondsAmount++;
        }
    }
}

void Server::notifyBombDefused(Robot *robot, const Coordinates &coordinates)
{
    robotsChanges.find(robot)->second.push_back(make_pair(coordinates, CellType::EMPTY));
    for (size_t i = 0; i < bombsAvaliable.size(); ++i)
    {
        if (bombsAvaliable.at(i) == coordinates)
        {
            bombsAvaliable.erase(bombsAvaliable.begin() + i);
        }
    }
}

void Server::notifyRobotMoved(const Robot *robot, const Coordinates &prevCoordinates, const Coordinates &newCoordinates)
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
        GameArea *internalMap = i.second->getMap();
        for (auto j : robotsChanges)
        {
            if (i.second != j.first)
            { // Do nothing for one robot
                for (auto k : j.second)
                {
                    if (k.second == CellType::EMPTY && internalMap->getCell(k.first) != CellType::DIAMOND)
                    {
                        internalMap->setCell(k.first, CellType::EMPTY);
                    }
                    if (k.second == CellType::EMPTY && internalMap->getCell(k.first) != CellType::BOMB)
                    {
                        internalMap->setCell(k.first, CellType::EMPTY);
                    }
                    else
                    {
                        internalMap->setCell(k.first, k.second);
                    }
                }
            }
        }

        for (auto t : robotsCoordinates)
        {
            if (i.second != t.second)
            {
                if (dynamic_cast<Explorer *>(t.second) && internalMap->getCell(t.first) != CellType::Cell_Explorer)
                {
                    internalMap->setCell(t.first, CellType::Cell_Explorer);
                }
                if (dynamic_cast<Sapper *>(t.second) && internalMap->getCell(t.first) != CellType::Cell_Sapper)
                {
                    internalMap->setCell(t.first, CellType::Cell_Sapper);
                }
            }
        }
    }

    for (auto i = robotsChanges.begin(); i != robotsChanges.end(); ++i)
    {
        i->second.clear();
    }

    setActualMap(robotsCoordinates.at(0).second->getInternalMap());
}