#include "ChangeMode.h"
//#include "../Robot/Collector.h"
//#include "../Robot/Sapper.h"
//#include "../GameModes/AutoScan.h"
#include "../Application/Manager.h"
#include "../GameModes/AutoScan.h"
#include "../Robot/Sapper.h"
#include "../Robot/Collector.h"
//#include "GameModes/AutoScan.h"

ChangeMode::ChangeMode(std::string modeName, Manager *manager, size_t stepsNum)
    : modeName{modeName}, manager{manager}, stepsNum{stepsNum}
{
}

ChangeMode::ChangeMode(std::string modeName, Manager *manager)
    : modeName{modeName}, manager{manager}
{
}

bool ChangeMode::Execute(Robot *robot)
{
    auto modes = manager->GetModesRange();
    //Mode* currentMode = nullptr;
    ModeBasement *currentMode = (modes->find(this->modeName))->second;
    auto assemblies = manager->GetActiveRobots();
    for (size_t i = 0; i < assemblies->size(); i++)
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
    return true;
}