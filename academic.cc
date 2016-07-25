#include "academic.h"
#include "game.h"
using namespace std;

Academic::Academic(Game *game, int index, string name, int cost, int impCost, string monoBlock, 
	int baseFee, int oneImpFee, int twoImpFee, int threeImpFee, int fourImpFee, int fiveImpFee) :
	Building(game, index, name, cost), impCost(impCost), monoBlock(monoBlock) {
		impLevel = 0;
		fees[0] = baseFee;
		fees[1] = oneImpFee;
		fees[2] = twoImpFee;
		fees[3] = threeImpFee;
		fees[4] = fourImpFee;
		fees[5] = fiveImpFee;
	}

Academic::Academic(Game *game, int index, string name, int cost, Player *owner, bool mortgaged, 
	int impCost, string monoBlock, int newImpLevel, int baseFee, int oneImpFee, 
	int twoImpFee, int threeImpFee, int fourImpFee, int fiveImpFee) :
	Building(game, index, name, cost, owner, mortgaged), impCost(impCost), monoBlock(monoBlock) {
		impLevel = newImpLevel;
		fees[0] = baseFee;
		fees[1] = oneImpFee;
		fees[2] = twoImpFee;
		fees[3] = threeImpFee;
		fees[4] = fourImpFee;
		fees[5] = fiveImpFee;
	}

Academic::~Academic() {}

int Academic::getFees() const {
	if (getImpLevel() == -1) return 0;
	if (game->isMonopolized(this) >= 1 && impLevel == 0) return fees[impLevel]*2;
	return fees[impLevel];
}

string Academic::getMonoBlock() const {
	return monoBlock;
}

int Academic::getImpCost() const {
	return impCost;
}

int Academic::getValue() const {
	if (getImpLevel() == -1) return 0;
	int impValue = impLevel * impCost;
	return impValue + cost;
}

ostream& operator<<(ostream& out, const Academic& a) {
	Player *owner = a.getOwner();
	string ownerName = "BANK";
	if (owner) ownerName = owner->getName();
	out << a.getName() << " " << ownerName << " " << a.getImpLevel() << endl;
	return out;
}
