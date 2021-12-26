#pragma once
//#include "ModeBasement.h"
#include "AutoMode.h"
//#include "Robot/Coordinates.h"
//#include <vector>
//#include <deque>
//#include <functional>

class AutoScan : public AutoMode
{
public:
    AutoScan() = default;
    ~AutoScan() = default;

    void SetStepsNum(size_t steps) { this->stepsNum = steps; };
    bool Execute(Robot *robot) override;
    bool Step(Robot *robot);

    //std::deque<Direction> FindPath(Robot *robot, CellType targetCell, std::vector<CellType> &restrictedCells);
    //bool ExploreArea(std::vector<Coordinates> &posize_ts, CellType targetCell, std::vector<CellType> &restrictedCells);
    //void ImplementPath(std::vector<Coordinates> &path, Robot *robot);
    //virtual void RenderPath() override;

private:
    size_t stepsNum;
    //std::vector<Coordinates> scanData;

    //cells restricted for collector
    std::vector<CellType> restrictedCells = {CellType::BOMB, CellType::ROCK};
};
