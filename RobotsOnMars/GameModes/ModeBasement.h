#pragma once

enum class Mode : unsigned char
{
    MANUAL,
    SCAN,
    GRAB,
};

class ModeBasement
{
public:
    ModeBasement(Simulation &simulation, Mode mode) : simulation(simulation), mode(mode){};
    virtual ~ModeBasement() = default;
    virtual Mode GetMode() const { return mode; };
    virtual void RenderPath() = 0;
    void Render() const;

    //or protected?
    Simulation &simulation;
    Mode mode;
};