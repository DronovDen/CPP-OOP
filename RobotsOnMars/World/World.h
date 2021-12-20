#pragma once

//#include "Robot/Robot.h"
#include "Robot/Coordinates.h"
#include "GameArea.h"
#include <string>

class World
{
public:
    World();
    ~World() = default;

    void SetGlobalMap(GameArea* area) { this->globalGameArea = area; }
	GameArea* GetGlobalMap() { return this->globalGameArea; }

	void SetDiamondHolder(bool status) { diamondHolder = status; }
	bool GetDiamondHolder() { return diamondHolder; }

	void SetBombHolder(bool status) { bombHolder = status; }
	bool GetBombHolder() { return bombHolder; }

	pair<Coordinates, CellType> Scan(const Coordinates& coordinates);
	
	Cell &GetCell(const Coordinates& coordinates) const;
	CellType GetCellInRobotWorld(const Coordinates& coordinates) const;

	bool CellIsEmpty(const Coordinates& coordinates) const;

	Coordinates GetGlobalRobotCoodinates(const Coordinates& coordinates) const;
	Coordinates GetRobotsMapCoord() const { return this->robotsMapCoord; };

    /* const GameArea &GetGameArea() const;

    Cell &GetCell(size_t x, size_t y);

    size_t GetWidth() const;
    size_t GetHeight() const; */

private:
    GameArea *globalGameArea;
    Coordinates robotsMapCoord;
    bool diamondHolder;
    bool bombHolder;

};