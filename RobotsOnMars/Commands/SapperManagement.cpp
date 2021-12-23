#include "SapperManagement.h"
#include "../Robot/Sapper.h"
#include "../Application/Manager.h"

SapperManagement::SapperManagement(std::string switcher, Manager *manager)
    : state(switcher), manager(manager)
{
}

bool SapperManagement::Execute()
{
    auto assemblies = manager->GetActiveRobots();
    if (state == "ON")
    {
        auto modes = manager->GetModesRange();
        Sapper *sap = new Sapper(manager->GetGlobalMap(), manager->GetServer());
        assemblies->push_back(std::make_pair((modes->find("INACTIVE"))->second, sap));
    }
    else if (state == "OFF")
    {
        for (int i = 0; i < assemblies->size(); i++)
        {
            if (dynamic_cast<Sapper *>(assemblies->at(i).second))
            {
                Robot *ref = assemblies->at(i).second;
                assemblies->erase(assemblies->begin() + i);
                delete dynamic_cast<Sapper *>(ref);
            }
        }
    }
}