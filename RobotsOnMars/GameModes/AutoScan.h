#pragma once

#include "AutoMode.h"

class AutoScan : public AutoMode
{
public:
    AutoScan(Simulation &simulation, std::size_t stepsNum);

    virtual ~AutoScan() = default;

    virtual void RenderPath() override;

private:
    bool Step() const;
    std::size_t stepsNum{0};

    //cells restricted for collector
    std::vector<CellType> restrictedCells = {CellType::BOMB, CellType::ROCK};

};
