#include "building.h"
#include "game.h"
using namespace std;

Building::Building(Game *game, int index, string name, int cost) : Square(game, index, name), cost(cost) {}

Building::Building(Game *game, int index, string name, int cost, Player *owner, bool mortgaged) : 
	Square(game, index, name), cost(cost), owner(owner), mortgaged(mortgaged) {}

Building::~Building() {}

Player* Building::getOwner() const {
	return owner;
}

void Building::setOwner(Player *newOwner) {
	owner = newOwner;
}

bool Building::getMortgaged() const {
	return mortgaged;
}

void Building::setMortgaged(bool isMortgaged) {
	mortgaged = isMortgaged;
}

int Building::getValue() const {
	if (mortgaged) return 0;
	return cost;
}

int Building::getCost() const {
	return cost;
}

void Building::notify(Player *landedPlayer) {
	if (owner == nullptr) game->askToBuy(this, landedPlayer);
	else if (owner == landedPlayer) cout << "You own this property." << endl;
	else {
		int fees = getFees();
		if (landedPlayer->getBalance() < fees) {
			// game->forceBankruptcy(landedPlayer, owner, fees);
		} else {
			landedPlayer->updateBalance(fees * -1);
			owner->updateBalance(fees);
		}
	}
}

ostream& operator<<(ostream& out, const Building& b) {
	Player *owner = b.getOwner();
	string ownerName = "Unowned";
	if (owner) ownerName = owner->getName();
	out << b.getName() << " " << ownerName << endl;
	return out;
}