#include "ChangeMode.h"
#include "../Robot/Collector.h"
#include "../Robot/Sapper.h"
#include "../GameModes/AutoScan.h"
#include "../Application/Manager.h"
//#include "GameModes/AutoScan.h"

ChangeMode::ChangeMode(std::string modeName, Manager *manager, int stepsNum)
    : modeName{modeName}, manager{manager}, stepsNum{stepsNum}
{
}

ChangeMode::ChangeMode(std::string modeName, Manager *manager)
    : modeName{modeName}, manager{manager}
{
}

bool ChangeMode::Execute()
{
    auto modes = manager->GetModesRange();
    //Mode* currentMode = nullptr;
    ModeBasement *currentMode = (modes->find(this->modeName))->second;
    auto assemblies = manager->GetActiveRobots();
    for (int i = 0; i < assemblies->size(); i++)
    {
        if (dynamic_cast<Collector *>(assemblies->at(i).second))
        {
            assemblies->at(i).first = currentMode;
            if (this->modeName == "SCAN")
            {
                dynamic_cast<AutoScan *>(currentMode)->SetStepsNum(this->stepsNum);
            }
        }
        else if (dynamic_cast<Sapper *>(assemblies->at(i).second) && this->modeName == "AUTO")
        {
            assemblies->at(i).first = currentMode;
        }
    }
}