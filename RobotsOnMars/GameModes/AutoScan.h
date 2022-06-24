#pragma once
#include "AutoMode.h"

class AutoScan : public AutoMode
{
public:
    AutoScan() = default;
    ~AutoScan() = default;

    void SetStepsNum(size_t steps) { this->stepsNum = steps; };
    bool Execute(Robot *robot) override;
    bool Step(Robot *robot);

    size_t stepsNum;
    std::vector<CellType> restrictedCells = {CellType::BOMB, CellType::ROCK};
};
