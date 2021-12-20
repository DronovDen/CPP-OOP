#pragma once
#include "GameArea.h"

class World
{
public:
    World();
    ~World() = default;

    void SetGlobalGameArea(GameArea *area) { this->globalGameArea = area; }
    GameArea *GetGlobalGameArea() { return this->globalGameArea; }

    void SetDiamondHolder(bool status) { diamondHolder = status; }
    bool GetDiamondHolder() { return diamondHolder; }

    void SetBombHolder(bool status) { bombHolder = status; }
    bool GetBombHolder() { return bombHolder; }

    std::pair<Coordinates, CellType> Scan(const Coordinates &coordinates);

    Cell &GetCell(const Coordinates &coordinates) const;
    CellType GetCellInRobotWorld(const Coordinates &coordinates) const;

    bool CellIsEmpty(const Coordinates &coordinates) const;

    Coordinates GetGlobalRobotCoodinates(const Coordinates &coordinates) const;
    Coordinates GetRobotsMapCoord() const { return this->robotsMapCoord; };

private:
    GameArea *globalGameArea;
    Coordinates robotsMapCoord;
    bool diamondHolder;
    bool bombHolder;
};