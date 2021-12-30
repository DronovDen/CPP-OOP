#include "ChangeMode.h"
#include "../Application/Manager.h"
#include "../GameModes/AutoScan.h"
#include "../Robot/Sapper.h"
#include "../Robot/Collector.h"

ChangeMode::ChangeMode(std::string newModeName, Manager *newManager, size_t newStepsNum)
    : modeName{newModeName}, manager{newManager}, stepsNum{newStepsNum}
{
}

ChangeMode::ChangeMode(std::string newModeName, Manager *newManager)
    : modeName{newModeName}, manager{newManager}
{
}

bool ChangeMode::Execute(Robot *robot)
{
    auto modes = manager->GetModesRange();
    ModeBasement *currentMode = nullptr;
    currentMode = (modes->find(this->modeName))->second;
    auto assemblies = manager->GetActiveRobots();
    for (size_t i = 0; i < assemblies->size(); i++)
    {
        if (dynamic_cast<Collector *>(assemblies->at(i).second))
        {
            assemblies->at(i).first = currentMode;
            if (this->modeName == "AUTOSCAN")
            {
                dynamic_cast<AutoScan *>(currentMode)->SetStepsNum(this->stepsNum);
            }
        }
        else if (dynamic_cast<Sapper *>(assemblies->at(i).second) && this->modeName == "AUTOGRAB")
        {
            assemblies->at(i).first = currentMode;
        }
    }
    return true;
}