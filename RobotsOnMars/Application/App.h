#pragma once

#include "Simulation.h"

class ICommand;
class ConsoleArgs;

class App 
{
public:
    App() = default;
    ~App();

    void Open(ConsoleArgs &args);

    void Run() const;

private:
    void Render() const;
    void OnFirstFrame() const;
    void OnFrame() const;
    ICommand *ScanCommand() const;

    void CreateWorld(ConsoleArgs &args);
    void CreatePlayer();
    void CreateMode();
    void CreateView();
    void CreateInput();
    void CreateCommandServer();

    Simulation simulation;
};