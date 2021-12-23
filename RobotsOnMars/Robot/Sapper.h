#pragma once

//class Robot;
#include "Robot.h"
#include "Direction.h"
#include "../World/Cell.h"
//#include "World/World.h"
//class Robot;

class GameArea;
class Server;

class Sapper : public Robot
{
public:
    Sapper(GameArea *globalMap, Server *server);
    virtual ~Sapper();
    void Move(const Direction &direction) override;
    void MoveImplementation(CellType newPos) override;
    void Defuse();
};
