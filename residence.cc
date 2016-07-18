#include "residence.h"
using namespace std;

Residence::Residence(Game *game, int index, string name, int cost) : Building(game, index, name, cost) {}

Residence::Residence(Game *game, int index, string name, int cost, Player *owner, bool mortgaged) : 
	Building(game, index, name, cost, owner, mortgaged) {}

Residence::~Residence() {}

int Residence::getFees() const {
	if (owner->getNumRes() == 1) return 25;
	if (owner->getNumRes() == 2) return 50;
	if (owner->getNumRes() == 3) return 100;
	if (owner->getNumRes() == 4) return 200;
	return 0;
}
