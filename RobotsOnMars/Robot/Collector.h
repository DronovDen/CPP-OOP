#pragma once
#include "Robot.h"

class Collector : public Robot
{
public:
    Collector(GameArea *gameArea, Server *server);
    ~Collector();
    void Move(const Direction &direction) override;
    void MoveImplementation(CellType newPos) override;
    void Collect();
    void Scan();
    void ScanCell(size_t x, size_t y) const;
};