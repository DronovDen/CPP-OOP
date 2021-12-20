#include "App.h"
#include "Console/CommandParser.h"
#include "Console/ConsoleArgs.h"
#include "World/World.h"
#include "World/MapLoader.h"
#include "Player/Player.h"
#include "Commands/CommandServer.h"
#include "GameModes/ManualMode.h"
#include "Graphics/SfmlView.h"

#include <sstream>

App::~App()
{
    delete simulation.Player;
    delete simulation.World;
    delete simulation.CommandParser;
    delete simulation.CommandServer;
    delete simulation.View;
    delete simulation.Mode;
}

void App::Open(ConsoleArgs &args)
{
    CreateWorld(args);
    CreateInput();
    CreateCommandServer();
    CreatePlayer();
    CreateMode();
    CreateView();
}

void App::Run() const
{
    OnFirstFrame();

    while (true)
    {
        OnFrame();
    }

    /* for (;;)
    {
        OnFrame();
    } */
}

void App::Render() const
{
    simulation.View->Render(*simulation.Player);
}

void App::OnFirstFrame() const
{
    Render();
}

void App::OnFrame() const
{
    if (const auto command = ScanCommand())
    {
        simulation.CommandServer->Execute(command);

        simulation.Mode->OnFrame();

        Render();
        simulation.View->Present();
    }
}

ICommand *App::ScanCommand() const
{
    auto &inputCommand = simulation.View->ScanConsole();
    std::stringstream commandStream(inputCommand);
    return simulation.CommandParser->Parse(commandStream);
}

void App::CreateWorld(ConsoleArgs &args)
{
    const GameAreaLoader loader(args.GetArg(1));
    simulation.World = new World(loader.Load());
}

void App::CreatePlayer()
{
    simulation.Player = new Player(simulation);
}

void App::CreateMode()
{
    simulation.Mode = new ManualMode(simulation);

    simulation.Mode->SetOnStepCallback([&]
                                       {
                                           Render();
                                           m_gameInterface.View->Present();
                                       });
}

void App::CreateView()
{
    simulation.View = new SfmlView;

    simulation.View->Open();
}

void App::CreateInput()
{
    simulation.CommandParser = new CommandParser;
}

void App::CreateCommandServer()
{
    simulation.CommandServer = new CommandServer(simulation);
}