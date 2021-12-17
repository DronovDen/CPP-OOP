#pragma once
#include "ModeBasement.h"

class ManualMode : public ModeBasement
{
public:
    ManualMode(Simulation &simulation);
    virtual ~ManualMode() = default;
    virtual void OnFrame() override;
};
