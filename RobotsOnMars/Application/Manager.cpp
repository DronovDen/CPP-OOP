#include "Manager.h"
#include "../Console/MapLoader.h"
#include "../GameModes/InactiveMode.h"
#include "../GameModes/AutoGrab.h"
#include "../GameModes/ManualMode.h"
#include "../GameModes/AutoScan.h"
#include "../Commands/ChangeMode.h"
#include "../Commands/Quit.h"
#include "../Commands/SapperManagement.h"
#include "../Commands/ManualCommands.h"
#include "../Console/Parser.h"

//class Parser;

Manager::Manager()
{
    currCommand = nullptr;
    commandParser = new Parser();
    //MapLoader loader("labyrinth.txt");
    MapLoader loader("map.txt");
    globalMap = loader.Load();
    //globalMap.createRandomGlobalMap();

    //this->parser->setFileNameOfMap(argc, argv);
    //this->parser->getMapFromFile(this->globalMap);

    server = new Server();

    ManualMode *manual = new ManualMode();
    AutoScan *autoScan = new AutoScan();
    AutoGrab *autoGrab = new AutoGrab();
    InactiveMode *inactive = new InactiveMode();

    modesRange["MANUAL"] = manual;
    modesRange["AUTOSCAN"] = autoScan;
    modesRange["AUTOGRAB"] = autoGrab;
    modesRange["INACTIVE"] = inactive;

    //modesRange = {{"MANUAL", mm}, {"SCAN", sm}, {"AUTO", am}, {"INACTIVE", im}};
    Collector *collector = new Collector(&globalMap, server);
    //server->NotifyRobotCreated(collector);
    activeRobots.push_back(std::make_pair(manual, collector));
}

Manager::~Manager()
{
    delete commandParser;
    delete server;

    for (size_t i = 0; i < modesRange.size(); ++i)
    {
        modesRange.erase(modesRange.begin());
    }

    for (auto i : activeRobots)
    {
        activeRobots.erase(activeRobots.begin());
    }

    /* for (size_t i = 0; i < activeRobots.size(); ++i)
    {
        activeRobots.erase(activeRobots.begin());
    }*/
}

void Manager::ExecuteGame()
{
    server->applyOthersRobotsChanges();
    gameView.Render(activeRobots.at(0).second, *(server->GetActualGameArea()));
    cout << endl
         << "Diamonds collected: " << server->GetCollectedDiamondsNum() << endl;
    cout << "Enter command: ";

    while (true)
    {
        if (!DoStep())
            break;
    }
}

bool Manager::DoStep()
{
    bool stepResult = true;

    try
    {
        currCommand = commandParser->GetCurrentCommand(this, stepResult);
        if (dynamic_cast<ManualCommands *>(currCommand))
        {
            dynamic_cast<ManualMode *>(activeRobots.at(0).first)->SetCommand(currCommand);
            stepResult = dynamic_cast<ManualMode *>(activeRobots.at(0).first)->ExecuteManual(activeRobots.at(0).second);
        }
        else if (dynamic_cast<ChangeMode *>(currCommand) ||
                 dynamic_cast<SapperManagement *>(currCommand) ||
                 dynamic_cast<Quit *>(currCommand))
        {
            stepResult = currCommand->Execute(nullptr);
        }

        delete currCommand;

        for (auto i : activeRobots)
        {
            //if not manual - perform preloaded behaviour
            if (!dynamic_cast<ManualMode *>(i.first))
            {
                //i.second->updateMap();
                stepResult = i.first->Execute(i.second);
            }
        }
        //activeRobots.at(0).second->updateMap();
    }
    catch (exception &ex)
    {
        cout << ex.what() << endl;
    }

    gameView.Render(activeRobots.at(0).second, *(server->GetActualGameArea()));
    cout << endl
         << "Diamonds collected: " << server->GetCollectedDiamondsNum() << endl;
    cout << "Enter command: ";

    return stepResult;
}