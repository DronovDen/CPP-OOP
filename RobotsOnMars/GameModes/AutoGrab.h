#pragma once
#include "AutoMode.h"
#include "../Robot/Collector.h"
#include "../Robot/Direction.h"
#include <deque>

class AutoGrab : public AutoMode
{
public:
    AutoGrab() = default;
    ~AutoGrab() = default;
    bool Execute(Robot *robot);
    bool Step(Robot *robot);
    void ImplementPath(Robot *robot, const std::deque<Direction> &path);
    bool Defuse(Robot *robot);  //sapper picks up bombs
    bool Collect(Robot *robot); //collector picks up diamonds
};
