#pragma once

//#include "Robot/Robot.h"
//class Robot;

enum class CellType : unsigned char
{
    EMPTY,
    ROCK,
    DIAMOND,
    BOMB,
    UNKNOWN,
};

class Cell
{
public:
    Cell() = default;

    CellType GetType() const;
    void SetType(CellType type);

    Robot *GetRobot() const;
    void SetRobot(Robot *entity);

private:
    Robot *robotOnCell{nullptr};
    CellType type{CellType::UNKNOWN};
};