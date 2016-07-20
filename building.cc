#include "building.h"
#include "game.h"
using namespace std;

Building::Building(Game *game, int index, string name, int cost) : Square(game, index, name), cost(cost) {
	impLevel = 0;
	owner = nullptr;
}

Building::Building(Game *game, int index, string name, int cost, Player *owner, int impLevel) : 
	Square(game, index, name), cost(cost), owner(owner), impLevel(impLevel) {}

Building::~Building() {}

Player* Building::getOwner() const {
	return owner;
}

void Building::setOwner(Player *newOwner) {
	owner = newOwner;
}

int Building::getImpLevel() const {
	return impLevel;
}

void Building::setImpLevel(int newImpLevel) {
	impLevel = newImpLevel;
}

bool Building::getMortgaged() const {
	return impLevel == -1;
}

void Building::setMortgaged(bool isMortgaged) {
	if (isMortgaged) impLevel = -1;
	else impLevel = 0;
}

int Building::getValue() const {
	if (getMortgaged()) return 0;
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

bool Building::isAcademic(){
	if((index == 5 || index == 15 || index == 25 || index == 35)||(index == 28 || index == 12)){
		return false;
	}
	return true;
}



ostream& operator<<(ostream& out, const Building& b) {
	Player *owner = b.getOwner();
	string ownerName = "BANK";
	if (owner) ownerName = owner->getName();
	out << b.getName() << " " << ownerName << " " << b.getImpLevel() << endl;
	return out;
}