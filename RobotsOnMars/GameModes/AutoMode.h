#pragma once
#include "ModeBasement.h"
#include "World/World.h"
#include "Application/Simulation.h"
#include "Robot/Robot.h"
#include "Player/Player.h"
#include <deque>
#include <functional>
#include <map>
#include <algorithm>
#include <vector>
//#include <unordered_map>

class AutoMode : public ModeBasement
{
public:
    //===============
    class Point
    {
    public:
        Point() = default;
        Point(size_t X, size_t Y);

        std::size_t X;
        std::size_t Y;
        const Point *previous{nullptr};

        bool operator==(const Point &point) const
        {
            return (point.X == X && point.Y == Y);
        }
    };
    //===============
    
    AutoMode(Simulation &simulation, Mode modeType);
    virtual ~AutoMode() = default;

    //or protected?
    std::deque<Direction> FindPath(const Robot &robot, CellType targetCell, const std::vector<CellType> &restrictedCells) const;

private:
    static Point Up(const Point &p);
    static Point Down(const Point &p);
    static Point Right(const Point &p);
    static Point Left(const Point &p);

    bool ExploreArea(std::vector<Point> &points, CellType desiredCell, const std::vector<CellType> &forbiddenCells) const;

    std::deque<Direction> Convert(const std::vector<Point> &points) const;
    Direction FindDirection(const Point &from, const Point &to) const;

    mutable std::map<Direction, std::function<Point(const Point &p)>> directions;
};
