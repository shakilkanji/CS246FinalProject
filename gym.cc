#include "gym.h"
using namespace std;

Gym::Gym(Game *game, int index, string name, int cost) : Building(game, index, name, cost) {}

Gym::Gym(Game *game, int index, string name, int cost, Player *owner, bool mortgaged) : 
	Building(game, index, name, cost, owner, mortgaged) {}

Gym::~Gym() {}

int Gym::getFees() const {
	// if (owner->getNumGym() == 1) return game->getSumDice() * 4;
	// if (owner->getNumGym() == 2) return game->getSumDice() * 10;
	return 0;
	
}
