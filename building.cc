#include "building.h"
#include "game.h"
using namespace std;

Building::Building(Game *game, int index, string name, int cost) : Square(game, index, name), cost(cost) {
	    impLevel = 0;
	    owner = nullptr;
}

// Building::Building(Game *game, int index, string name, int cost, Player *owner, bool mortgaged) : 
// 	Square(game, index, name), cost(cost), owner(owner), mortgaged(mortgaged) {		
// 	impLevel = 0;
// 	owner = nullptr;
// }

// Building::Building(Game *game, int index, string name, int cost, Player *owner, int impLevel) : 
// 	Square(game, index, name), cost(cost), owner(owner), impLevel(impLevel) {

	
// 	owner = nullptr;
// }

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

int Building::getValue() const {
	if (getImpLevel() == -1) return 0;
	return cost;
}

int Building::getCost() const {
	return cost;
}

void Building::notify(Player *landedPlayer) {
	cout << ">> You have landed on " << getName() << ". ";
	if (owner == nullptr) {
		cout << "It is unowned." << endl;
		game->askToBuy(this, landedPlayer);
	} else if (owner == landedPlayer) {
		cout << "You own this property." << endl;
	} else {
		cout << "It is owned by " << owner->getName() << ". ";
		int fees = getFees();
		cout << "You must pay " << "$" << fees << "." << endl;
		if (landedPlayer->getBalance() < fees) {
			game->forceBankruptcy(landedPlayer, fees, owner);
		} else {
			landedPlayer->updateBalance(fees * -1);
			owner->updateBalance(fees);
			cout << ">> Your new balance is $" <<  landedPlayer->getBalance() << "." << endl;
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
