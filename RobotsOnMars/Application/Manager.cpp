#include "Manager.h"

Manager::Manager(int argc, char *argv[])
{
    currentCommand = nullptr;
    parser = new Parser();
    globalMap.createRandomGlobalMap();
    //this->parser->setFileNameOfMap(argc, argv);
    //this->parser->getMapFromFile(this->globalMap);
    server = new Receiver();

    ManualMode *mm = new ManualMode();
    ScanMode *sm = new ScanMode();
    AutoMode *am = new AutoMode();
    IdleMode *im = new IdleMode();

    possibleModes = {{"MANNUAL", mm}, {"SCAN", sm}, {"AUTO", am}, {"INACTIVE", im}};

    Collector *collector = new Collector(&(this->globalMap), this->receiver);

    this->bundles.push_back(std::make_pair(mm, ex));
}

Manager::~Manager()
{
    delete parser;
    delete receiver;

    for (size_t i = 0; i < modes.size(); ++i)
    {
        modes.erase(modes.begin());
    }

    for (size_t i = 0; i < bundles.size(); ++i)
    {
        bundles.erase(bundles.begin());
    }
}

void Manager::play()
{
    receiver->applyOthersRobotsChanges();
    gameView.drawMapForCertainRobot(bundles.at(0).second, *(this->receiver->getActualMap()));
    cout << endl
         << "Apples collected in total: " << receiver->getCollectedApplesAmount() << endl;
    cout << "Enter command: ";

    while (doGameStep())
    {
    }
}

bool Manager::doGameStep()
{
    bool stepResult = true;

    try
    {

        this->currentCommand = this->parser->getCurrentCommand(this, stepResult);

        if (dynamic_cast<ManualModeCommandManager *>(this->currentCommand))
        {
            dynamic_cast<ManualMode *>(bundles.at(0).first)->setCommand(currentCommand);
            stepResult &= dynamic_cast<ManualMode *>(bundles.at(0).first)->executeMMCommand(bundles.at(0).second);
        }
        else if (dynamic_cast<ChangeModeCommand *>(this->currentCommand) ||
                 dynamic_cast<SapperManagerCommand *>(this->currentCommand) ||
                 dynamic_cast<QuitCommand *>(this->currentCommand))
        {
            stepResult &= currentCommand->execute();
        }

        delete currentCommand;

        for (auto i : bundles)
        {
            if (!dynamic_cast<ManualMode *>(i.first))
            {
                stepResult &= i.first->execute(i.second);
            }
        }

        //bundles.at(0).second->updateMap();
    }
    catch (exception &ex)
    {
        cout << ex.what() << endl;
    }

    gameView.drawMapForCertainRobot(bundles.at(0).second, *(this->receiver->getActualMap()));
    cout << endl
         << "Apples collected in total: " << receiver->getCollectedApplesAmount() << endl;
    cout << "Enter command: ";

    return stepResult;
}