#include "Application/Manager.h"
#include "World.h"

World::World() {
	diamondHolder = false;
	bombHolder = false;
	robotsMapCoord = {0, 0};
	globalGameArea = nullptr;
}

Coordinates World::GetGlobalRobotCoodinates(const Coordinates& coordinates) const {
	return { robotsMapCoord.x + coordinates.x, robotsMapCoord.y + coordinates.y };
}

Cell& World::GetCell(const Coordinates& coordinates) const {
	return globalGameArea->GetCell(coordinates);
}

CellType World::GetCellInRobotWorld(const Coordinates& coordinates) const {
	return globalGameArea->GetCell(GetGlobalRobotCoodinates(coordinates)).GetType();
} 

bool World::CellIsEmpty(const Coordinates& coordinates) const{
	return (GetCell(coordinates).GetType() == CellType::EMPTY);
}