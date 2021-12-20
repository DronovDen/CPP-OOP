#include "Player.h"

Player::Player(Simulation &simulation)
    : collector(*simulation.World, exploredGameArea, server), simulation(simulation)
{

    exploredGameArea.Resize(simulation.World->GetWidth(), simulation.World->GetHeight());
    collector.SetPosition();
}

Sapper *Player::GetSapper() const
{
    //gives access to pointer on sapper
    //and no access to modify sapper
    //there is no move operation
    return sapper.get();
}

void Player::AddSapper()
{
    sapper = std::make_unique<Sapper>(*simulation.World, exploredGameArea);

    sapper->SetPosition();
}

void Player::RemoveSapper()
{
    sapper.reset(nullptr);
}

Collector &Player::GetCollector()
{
    return collector;
}

const Collector &Player::GetCollector() const
{
    return collector;
}

const GameArea &Player::GetExploredGameArea() const
{
    return exploredGameArea;
}
