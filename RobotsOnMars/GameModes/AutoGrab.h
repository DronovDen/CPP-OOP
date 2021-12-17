#pragma once
#include "AutoMode.h"

class AutoGrab : public AutoMode
{
public:
    AutoGrab(Simulation &simulation);

    virtual ~AutoGrab() = default;

    virtual void RenderPath() override;

private:

    void Defuse(); //sapper picks up bombs
    bool Collect(); //collector picks up diamonds
    void ImplementPath(Robot &robot, const std::deque<Direction> &path);
    bool Step();


};
