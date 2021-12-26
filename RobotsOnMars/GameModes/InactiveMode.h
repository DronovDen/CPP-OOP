#pragma once
#include "ModeBasement.h"
#include "iostream"

class InactiveMode : public ModeBasement
{
public:
    InactiveMode() = default;
    ~InactiveMode() = default;
    //virtual ~InactiveMode() = default;
    bool Execute(Robot *robot);
    //virtual void OnFrame() override;
};