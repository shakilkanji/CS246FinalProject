#include "gym.h"
using namespace std;

Gym::Gym(Game *game, int index, string name) : game(game), index(index), name(name) {}

Gym::Gym(Game *game, int index, string name, Player *owner, bool mortgaged) : game(game), index(index),
	name(name), owner(owner), mortgaged(mortgaged) {}

Gym::~Gym() {}

int Gym::getFees() {
	if (owner->getNumGym() == 1) return game->getSumDice() * 4;
	if (owner->getNumGym() == 2) return game->getSumDice() * 10;
	return 0;
}
