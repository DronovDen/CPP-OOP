#pragma once
#include "ModeBasement.h"
//#include "World/World.h"
#include "Robot/Robot.h"
//#include "Commands/ICommand.h"

//#include "Robot/Coordinates.h"
//#include <unordered_map>

class AutoMode : public ModeBasement
{
public:
    AutoMode();
    virtual ~AutoMode() = default;

    //or protected?
    std::deque<Direction> FindPath(Robot *robot, CellType targetCell, std::vector<CellType> &restrictedCells);
    bool ExploreArea(std::vector<Coordinates> &points, CellType targetCell, std::vector<CellType> &restrictedCells);

private:
    static Coordinates Up(const Coordinates &p);
    static Coordinates Down(const Coordinates &p);
    static Coordinates Right(const Coordinates &p);
    static Coordinates Left(const Coordinates &p);

    using TDir = std::map<Direction, std::function<Coordinates(const Coordinates &p)>>;

    bool ExploreArea(std::vector<Coordinates> &points, CellType desiredCell, std::vector<CellType> &forbiddenCells);

    std::deque<Direction> Convert(const std::vector<Coordinates> &points);
    Direction FindDirection(const Coordinates &from, const Coordinates &to);

    //might be mutable
    TDir directions;
};
