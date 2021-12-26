#pragma once
/* #include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <ctime>
#include <deque>
#include <functional>
#include <map>
#include <algorithm> */


enum class CellType : unsigned char
{
    EMPTY,
    ROCK,
    DIAMOND,
    BOMB,
    SAPPER,
    COLLECTOR,
    UNKNOWN
};

class Cell
{
public:
    Cell() = default;
    Cell(CellType new_type) : type{new_type} {}

    CellType GetType() const { return type; };
    void SetType(CellType new_type) { type = new_type; };

    //Robot *GetRobot() const { return robotOnCell; };

    //void SetRobot(Robot *entity) { robotOnCell = entity; };

private:
    //Robot *robotOnCell{nullptr};
    CellType type{CellType::UNKNOWN};
};