#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include "game.h"

using namespace std;


int main(int argc, char* argv[]) {
	Game g;
	// Dice d;

	cout <<"   _____________________        "  <<endl;
	cout <<"  ( Welcome to Watopoly )       "  <<endl;
	cout <<"   ---------------------        "  <<endl;
	cout <<"          o   ^__^              "  <<endl;
	cout <<"           o  (oo)________      "  <<endl;
	cout <<"              (__)      ) |--   "  <<endl;
	cout <<"                  ||----w |     "  <<endl;
	cout <<"                  ||     ||     "  <<endl;
	cout <<"                                "  <<endl;


	bool loaded = false;
	for (int i = 0; i < argc; ++i) {
		string cur_argc = argv[i];
		if (cur_argc == "-testing") {
			g.settest();
			cout << "Testing mode started." << endl;
		} else if (cur_argc == "-load") {
			if (i < argc-1) {
				++i;
				cur_argc = argv[i];
				if (g.loadGame(cur_argc)) {
					loaded = true;
				}
			} else {
				cout << "Please specify file name." << endl;
				return 0;
			}
		}
	}
	if (!loaded) g.normalinit();
	g.run();
}

    
