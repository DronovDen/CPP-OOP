#pragma once

//#include "GameArea/GameArea.h"
#include "Robot/Collector.h"
#include "Robot/Sapper.h"
#include <memory>

struct Simulation;

class Player
{
public:
    Player(Simulation &simulation);

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

    Simulation &simulation;
    GameArea exploredGameArea;
};
