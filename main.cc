#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include "game.h"
using namespace std;

const int welcome_h = 12;
const int welcome_w = 101;

const string BackgroundDefault      = "\033[49m";
const string BackgroundLightGray    = "\033[47m";
const string BackgroundLightRed     = "\033[101m";
const string BackgroundLightGreen   = "\033[102m";
const string BackgroundLightYellow  = "\033[103m";
const string BackgroundLightBlue    = "\033[104m";
const string BackgroundLightMagenta = "\033[105m";
const string BackgroundLightCyan    = "\033[106m";


void displayWelcome() {

	ifstream file;
  file.open("welcome.txt");

  char c;

  for (int i = 0; i < welcome_h; ++i) {
    for (int j = 0; j < welcome_w; ++j) {
      file.get(c);

      if (c == 'Y') cout << BackgroundLightYellow;
      else if (c == 'P') cout << BackgroundLightMagenta;
      else if (c == 'C') cout << BackgroundLightCyan;
      else if (c == 'G') cout << BackgroundLightGreen;
      else if (c == 'B') cout << BackgroundLightBlue;
      else if (c == 'R') cout << BackgroundLightRed;
      else if (c == 'L') cout << BackgroundLightGray;

      if (c == 'Y' || c == 'P' || c == 'C' || c == 'G' || c == 'B' || c == 'R' || c == 'L')
        cout << ' ' << BackgroundDefault;
      else cout << c;
    }
  }
  cout << endl;

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
