#include "SapperManagement.h"
#include "Robot/Sapper.h"

SapperManagement::SapperManagement(std::string switcher, Manager *manager)
    : state(switcher), manager(manager)
{
}

bool SapperManagement::Execute()
{
    auto assemblies = manager->GetActiveRobots();
    if (state == "ON")
    {
        auto modes = manager->GetPossibleModes();
        Sapper* sap = new Sapper(manager->GetGlobalMap(), manager->GetServer());
        assemblies->push_back(std::make_pair((modes->find("INACTIVE"))->second, sap));
    }
    else if(state == "OFF"){
        for (size_t i = 0; i < assemblies->size(); i++) {
			if (dynamic_cast<Sapper*>(assemblies->at(i).second)) {
				Robot* ref = assemblies->at(i).second;
				assemblies->erase(assemblies->begin() + i);
				delete dynamic_cast<Sapper*>(ref);
			}
		}
    }
}