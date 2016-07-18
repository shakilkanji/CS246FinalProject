#include "residence.h"
using namespace std;

Residence::Residence(Game *game, int index, string name) : game(game), index(index), name(name) {}

Residence::Residence(Game *game, int index, string name, Player *owner, bool mortgaged) : game(game), 
	index(index), name(name), owner(owner), mortgaged(mortgaged) {}

Residence::~Residence() {}

int Residence::getFees() {
	if (owner->getNumRes() == 1) return 25;
	if (owner->getNumRes() == 2) return 50;
	if (owner->getNumRes() == 3) return 100;
	if (owner->getNumRes() == 4) return 200;
	return 0;
}
