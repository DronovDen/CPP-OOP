#pragma once

#include "Robot.h"

class Collector : public Robot
{
public:
    Collector(GameArea *gameArea, Server *server);
    ~Collector();

    void Collect();

    void Scan() const;

private:
    void ScanCell(size_t x, size_t y) const;
};