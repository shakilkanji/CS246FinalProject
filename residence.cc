#include "residence.h"
#include "game.h"
using namespace std;

Residence::Residence(Game *game, int index, string name, int cost) : Building(game, index, name, cost) {}

Residence::Residence(Game *game, int index, string name, int cost, Player *owner, bool mortgaged) : 
	Building(game, index, name, cost, owner, mortgaged) {}

Residence::~Residence() {}

int Residence::getFees() const {
	cout << owner->getName() << " has " << game->getNumRes(owner) << endl;
	if (game->getNumRes(owner) == 1) return 25;
	if (game->getNumRes(owner) == 2) return 50;
	if (game->getNumRes(owner) == 3) return 100;
	if (game->getNumRes(owner) == 4) return 200;
	return 0;
}
