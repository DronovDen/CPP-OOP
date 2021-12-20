#pragma once
#include "ModeBasement.h"
#include "iostream"

class InactiveMode : public ModeBasement
{
public:
    InactiveMode();
    virtual ~InactiveMode() = default;
    bool Execute(Robot* robot);
    //virtual void OnFrame() override;
};