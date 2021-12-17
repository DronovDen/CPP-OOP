#pragma once

//class Robot;
#include "Robot.h"
//#include "World/World.h"
//class Robot;

class GameArea;

class Sapper : public Robot
{
public:
    Sapper(World &world, GameArea &exploredGameArea);

    ~Sapper() = default;

    virtual void SetPosition() override;

    void Defuse();

private:
    bool CanBeSetOnCell(const Cell &cell) const override;
};
