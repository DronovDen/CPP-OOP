#pragma once

class World;
class Player;
class ModeBasement;
class IView;
class ICommandParser;
class CommandServer;

class Simulation
{
public:
    World *World{nullptr};
    Player *Player{nullptr};
    ModeBasement *Mode{nullptr};
    IView *View{nullptr};
    ICommandParser *CommandParser{nullptr};
    //??????????????
    CommandServer *CommandServer{nullptr};
    //=============
};