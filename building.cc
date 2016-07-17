#include "building.h"
using namespace std;

Building::Building(int index, string name, int cost) : index(index), name(name), cost(cost), mortgaged(false) {}

Building::~Building() {}

Player* Building::getOwner() {
	return owner;
}

void Building::setOwner(Player *newOwner) {
	owner = newOwner;
}

bool Building::getMortgaged() {
	return mortgaged;
}

void Building::setMortgaged(bool isMortgaged) {
	mortgaged = isMortgaged;
}

int Building::getValue() {
	if (getMortgaged()) return cost/2;
	return cost;
}

int Building::getCost() {
	return cost;
}
