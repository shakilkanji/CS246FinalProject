#include "square.h"
#include "game.h"
using namespace std;

Square::Square(Game *game, int index, string name) : game(game), index(index), name(name) {}

Square::~Square() {}

int Square::getIndex() const {
	return index;
}

string Square::getName() const {
	return name;
}

void Square::notify(Player *landedPlayer) {
	if (index == 0) {	// Collect OSAP
		landedPlayer->updateBalance(200);
		cout << "You Collect 200" << endl;
	} else if (index == 4) {	// Tuition
		// game->chooseTuition(landedPlayer);
	} else if (index == 7 || index == 22 || index == 36) {	// Needles Hall
		cout << ">> Landed on Needles Hall" << endl;
		game->Needles(landedPlayer);
	} else if (index == 10) {	// DC Tims
		cout << ">> Landed on DC Tims, nothing happens." << endl;
	} else if (index == 2 || index == 17 || index == 33) {	// SLC
		cout << ">> Landed on SLC" << endl;
		game->SLC(landedPlayer);
	} else if (index == 20) {	// Goose Nesting
		cout << ">> You are attacked by a flock of geese, but nothing happens." << endl;
	} else if (index == 30) {	// Go To Tims
		landedPlayer->setPos(10);
		landedPlayer->setDCTurn(0);
		// make sure to end landedPlayer's turn (if they rolled doubles)
	} else if (index == 38) {	// Co-op Fee
		if (landedPlayer->getBalance() < 150) {
			game->forceBankruptcy(landedPlayer, 150, nullptr);
		} else {
			landedPlayer->updateBalance(-150);
		}
	} else cout << index << endl;

}
