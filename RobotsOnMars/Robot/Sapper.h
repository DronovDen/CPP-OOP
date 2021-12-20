#pragma once

//class Robot;
#include "Robot.h"
//#include "World/World.h"
//class Robot;

class GameArea;

class Sapper : public Robot
{
public:
    Sapper(GameArea *globalMap, Server *server);
    virtual ~Sapper() = default;
    void Move(const Direction &direction) override;
    void MoveImplementation(CellType newPos) override;
    void Defuse();
};
