#pragma once

//#include "World/IEntity.h"
//#include "GameArea/Cell.h"
//#include "GameArea/GameArea.h"

#include "Server.h"
#include <utility>

//class Cell;
//class World;
//class GameArea;

enum class RobotType : unsigned char
{
    COLLECTOR,
    SAPPER,
};

enum class Direction : unsigned char
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

enum class State : unsigned char
{
    ACTIVE,
    DESTROYED,
};

class Robot
{
public:
    Robot(RobotType type, World &world, GameArea &gameArea);

    virtual ~Robot();

    virtual void SetPosition();

    std::pair<std::size_t, std::size_t> GetPosition() const;

    void Move(Direction direction);
    void Move(size_t x, size_t y);

    void ClearCell(CellType targetCell);

    size_t GetScore() const;

    GameArea* getMap() {return exploredGameArea;};

    RobotType GetType() const;

protected:
    virtual bool CanBeSetOnCell(const Cell &cell) const = 0;

    bool AvailableToMove(size_t x, size_t y) const;

    virtual bool AvailableForConcrete(size_t x, size_t y) const;

    std::pair<size_t, size_t> CalculateTargetPos(Direction dir) const;

    RobotType type;
    Server &server;
    World &world;
    GameArea *exploredGameArea; //unique for each robot
    State state{State::ACTIVE};
    size_t coord_x{0};
    size_t coord_y{0};
    size_t score{0};
};