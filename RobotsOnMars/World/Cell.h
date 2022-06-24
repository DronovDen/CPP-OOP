#pragma once

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

private:
    CellType type{CellType::UNKNOWN};
};