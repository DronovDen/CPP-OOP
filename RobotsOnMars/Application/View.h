#pragma once
#include <iostream>
#include <cstdlib>
#include "../World/GameArea.h"
#include "../Robot/Robot.h"

class View
{
public:
    View() : offsetX{0}, offsetY{0} {}
    void Render(Robot *robot, GameArea &map);

private:
    size_t offsetX;
    size_t offsetY;
};