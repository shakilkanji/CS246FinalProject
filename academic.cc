#include "academic.h"
using namespace std;

Academic::Academic(Game *game, int index, string name, int cost, int impCost, string monoBlock, 
	int baseFee, int oneImpFee, int twoImpFee, int threeImpFee, int fourImpFee, int fiveImpFee) :
	Building(game, index, name, cost), impCost(impCost), monoBlock(monoBlock) {
		fees[0] = baseFee;
		fees[1] = oneImpFee;
		fees[2] = twoImpFee;
		fees[3] = threeImpFee;
		fees[4] = fourImpFee;
		fees[5] = fiveImpFee;
	}

Academic::Academic(Game *game, int index, string name, int cost, Player *owner, bool mortgaged, 
	int impCost, string monoBlock, bool monopolized, int impLevel, int baseFee, int oneImpFee, 
	int twoImpFee, int threeImpFee, int fourImpFee, int fiveImpFee) :
	Building(game, index, name, cost, owner, mortgaged), impCost(impCost), monoBlock(monoBlock),
	monopolized(monopolized), impLevel(impLevel) {
		fees[0] = baseFee;
		fees[1] = oneImpFee;
		fees[2] = twoImpFee;
		fees[3] = threeImpFee;
		fees[4] = fourImpFee;
		fees[5] = fiveImpFee;
	}

Academic::~Academic() {}

int Academic::getFees() {
	if (mortgaged) return 0;
	if (monopolized && impLevel == 0) return fees[impLevel]*2;
	return fees[impLevel];
}

int Academic::getImpLevel() {
	return impLevel;
}

void Academic::setImpLevel(int newImpLevel) {
	impLevel = newImpLevel;
}

bool Academic::isMonopolized() {
	return monopolized;
}

int Academic::getValue() {
	int impValue = impLevel * impCost;
	return impValue + cost;
}
