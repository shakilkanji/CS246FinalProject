#include "gym.h"
#include "game.h"
using namespace std;

Gym::Gym(Game *game, int index, string name, int cost) : Building(game, index, name, cost) {}

Gym::Gym(Game *game, int index, string name, int cost, Player *owner, bool mortgaged) : 
	Building(game, index, name, cost, owner, mortgaged) {}

Gym::~Gym() {}

int Gym::getFees() const {
	cout << owner->getName() << " has " << game->getNumGym(owner) << endl;
	if (game->getNumGym(owner) == 1) return game->getsumdice() * 4;
	if (game->getNumGym(owner) == 2) return game->getsumdice() * 10;
	return 0;
	
}
