#pragma once
#include "ModeBasement.h"
#include "iostream"

class InactiveMode : public ModeBasement
{
public:
    InactiveMode(Simulation &simulation);
    virtual ~InactiveMode() = default;
    bool Execute(Robot* robot);
    //virtual void OnFrame() override;
};