#pragma once
#include <iostream>
#include <cstdlib>
#include "../World/GameArea.h"
#include "../Robot/Robot.h"

//class GameMaster;

class View
{
public:
    View() : offsetX{0}, offsetY{0} {}
    //char *color(size_t color, char *Message);
    void Render(Robot *robot, GameArea &map);

private:
    size_t offsetX;
    size_t offsetY;
};