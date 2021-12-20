#pragma once

//#include "World/IEntity.h"
//#include "GameArea/Cell.h"
//#include "GameArea/GameArea.h"

#include "Server.h"
#include <utility>
#include "Sapper.h"

//class Cell;
//class World;
//class GameArea;

enum class Direction : unsigned char
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};


class Robot
{
public:
    Robot();
    virtual ~Robot();

    void SetServer(Server* server) {this->server = server;};
    Server* GetServer(){return this->server;};

    World* GetWorld() { return this->world; }
    void* SetWorld(World* environment) { this->world = world; }

    GameArea* GetExploredArea() { return this->exploredGameArea; };
    void SetExploredArea(GameArea* map) { this->exploredGameArea = map; };

    Coordinates Robot::GetPosition() const { return position; };
    //std::pair<std::size_t, std::size_t> GetPosition() const;

    virtual void Move(Direction direction) = 0;
    virtual void Move(size_t x, size_t y) = 0;


    bool IsAvailableToMove(const Coordinates& coordinates, Robot * robot) const;
    Coordinates CalculateTargetPos(const Direction& direction);
    Coordinates GetSpawnCoordinates();

    void SetCoordinates(const Coordinates& coordinates) { this->position = coordinates;}
    const Coordinates& GetCoordinates() { return this->position;}

    virtual void Move(const Direction& direction) = 0;
    void updateMap();
    
    Direction GetDirection(const Coordinates& diff); 
    Coordinates CalculateNewCoordinates(const Direction& direction);  

    void ClearCell(CellType targetCell);

    //size_t GetScore() const;

    //GameArea &getMap() { return exploredGameArea; };

    //RobotType GetType() const;

protected:

    //virtual bool CanBeSetOnCell(const Cell &cell) const = 0;

    //virtual bool AvailableForConcrete(size_t x, size_t y) const;

    //std::pair<size_t, size_t> CalculateTargetPos(Direction dir) const;

    Server *server;
    GameArea *exploredGameArea; //unique for each robot
    Coordinates position;
    World* world;

    //not really useful
    //State state{State::ACTIVE};
    //size_t coord_x{0};
    //size_t coord_y{0};
    //size_t score{0};
};