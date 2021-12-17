#pragma once

#include "Robot.h"

class Collector : public Robot
{
public:
    Collector(World &world, GameArea &gameArea);

    ~Collector() = default;

    void Collect();

    void Scan() const;

private:
    bool CanBeSetOnCell(const Cell &cell) const override;

    bool AvailableForConcrete(size_t x, size_t y) const override;

    void ScanCell(size_t x, size_t y) const;
};