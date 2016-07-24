#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include "game.h"
using namespace std;

const int welcome_h = 14;
const int welcome_w = 101;

const string ResetAll = "\033[0m";
const string Reverse    = "\033[7m";


void displayWelcome() {

	ifstream file;
  file.open("welcome.txt");

  char c;

  for (int i = 0; i < welcome_h; ++i) {
    for (int j = 0; j < welcome_w; ++j) {
      file.get(c);
      if (c == '*') cout << Reverse << ' ';
      if (c != '*') cout << c;
      if (c == '*') cout << ResetAll;
    }
  }

  file.close();
}


int main(int argc, char* argv[]) {
	Game g;
	// Dice d;

	displayWelcome();

	bool loaded = false;
	for (int i = 0; i < argc; ++i) {
		string cur_argc = argv[i];
		if (cur_argc == "-testing") {
			g.settest();
			cout << ">> Testing mode started." << endl;
		} else if (cur_argc == "-load") {
			if (i < argc-1) {
				++i;
				cur_argc = argv[i];
				if (g.loadGame(cur_argc)) {
					loaded = true;
				}
			} else {
				cout << ">> Please specify file name." << endl;
				return 0;
			}
		}
	}
	if (!loaded) g.normalinit();
	g.run();
}
