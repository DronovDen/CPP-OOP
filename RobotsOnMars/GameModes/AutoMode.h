#pragma once
#include "ModeBasement.h"
//#include "World/World.h"
//#include "../Robot/Robot.h"
//#include "../Application/Manager.h"
#include "../World/Cell.h"
#include "../World/Coordinates.h"
#include "../Robot/Direction.h"
#include <deque>
#include <functional>
#include <vector>
//#include "Commands/ICommand.h"

//#include "Robot/Coordinates.h"
#include <map>

class Robot;

class AutoMode : public ModeBasement
{
public:
    AutoMode();
    virtual ~AutoMode() = default;
    std::deque<Direction> FindPath(Robot *robot, CellType targetCell, std::vector<CellType> &restrictedCells);
    bool ExploreArea(std::deque<Coordinates> &points, CellType targetCell, std::vector<CellType> &restrictedCells);

private:
    static Coordinates Up(const Coordinates &p);
    static Coordinates Down(const Coordinates &p);
    static Coordinates Right(const Coordinates &p);
    static Coordinates Left(const Coordinates &p);
    std::deque<Direction> Convert(const std::deque<Coordinates> &points);
    Direction FindDirection(const Coordinates &from, const Coordinates &to);

    using TDir = std::map<Direction, std::function<Coordinates(const Coordinates &p)>>;
    TDir directions;
};
