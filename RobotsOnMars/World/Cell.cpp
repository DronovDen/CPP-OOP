#pragma once

#include "Cell.h"

CellType Cell::GetType() const
{
    return type;
}

void Cell::SetType(CellType type)
{
    type = type;
}

Robot *Cell::GetRobot() const
{
    return robotOnCell;
}

void Cell::SetRobot(Robot *entity)
{
    robotOnCell = entity;
}
