#pragma once

//#include "GameArea/GameArea.h"
#include "Application/Simulation.h"
#include "World/World.h"
#include "Robot/Server.h"
//#include "Robot/Collector.h"
//#include "Robot/Sapper.h"
#include <memory>

class Sapper;
class Collector;
class Simulation;

class Player
{
public:
    explicit Player(Simulation &simulation);

    Sapper *GetSapper() const;
    void AddSapper();
    void RemoveSapper();

    Collector &GetCollector();
    const Collector &GetCollector() const;

    const GameArea &GetExploredGameArea() const;

private:
    Collector collector;
    //std::unique_ptr<Collector> collector;
    std::unique_ptr<Sapper> sapper;
    //Server &server;
    Simulation &simulation;
    GameArea *exploredGameArea;
};
