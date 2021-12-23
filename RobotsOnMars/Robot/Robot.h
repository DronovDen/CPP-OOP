#pragma once
//#include "World/IEntity.h"
//#include "GameArea/Cell.h"
//#include "GameArea/GameArea.h"

//#include "Server.h"
#include "../World/World.h"
#include "../World/Coordinates.h"
#include "../World/GameArea.h"
#include "../Robot/Direction.h"
//#include <utility>
//#include "Sapper.h"

class Server;
//class Cell;
//class World;
//class GameArea;

class Robot
{
public:
    Robot();
    virtual ~Robot();

    void SetServer(Server *server) { this->server = server; };
    Server *GetServer() { return this->server; };

    World *GetWorld() { return this->world; }
    void SetWorld(World *environment) { this->world = world; }

    GameArea *GetExploredArea() { return this->exploredGameArea; };
    void SetExploredArea(GameArea *map) { this->exploredGameArea = map; };

    //Coordinates Robot::GetPosition() const { return position; };

    //virtual void Move(Direction direction) = 0;
    //virtual void Move(int x, int y) = 0;

    bool IsAvailableToMove(const Coordinates &coordinates, Robot *robot) const;
    Coordinates CalculateTargetPos(const Direction &direction);
    Coordinates GetSpawnCoordinates();

    void SetCoordinates(const Coordinates &coordinates) { position = coordinates; }
    const Coordinates &GetCoordinates() { return position; }

    virtual void Move(const Direction &direction) = 0;
    void updateMap();

    Direction GetDirection(const Coordinates &diff);
    Coordinates CalculateNewCoordinates(const Direction &direction);

    void ClearCell(CellType targetCell);

    virtual void MoveImplementation(CellType newPos) = 0;

protected:
    Server *server;
    GameArea *exploredGameArea; //unique for each robot
    Coordinates position;
    World *world;
};