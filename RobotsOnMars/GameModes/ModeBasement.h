#pragma once
class ICommand;
class ManualCommands;
class Robot;
class Manager;
class Server;

enum class Mode
{
    MANUAL,
    SCAN,
    GRAB,
};

class ModeBasement
{
public:
    ModeBasement() = default;
    ~ModeBasement() = default;

    virtual void SetCommand(ICommand *command);
    virtual void SetServer(Server *newServer);
    virtual bool Execute(Robot *robot);

    ICommand *command;
    Server *server;
};