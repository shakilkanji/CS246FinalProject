#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include "game.h"

using namespace std;


int main(int argc, char* argv[]){
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

for ( int i = 0 ; i < argc ; i++){
	string cur_argc = argv[i];
	if( cur_argc == "-testing" ) {
	   // g.settest();
       // g.test == true;;
       cout << "Testing mode start" << endl;
	}
	else {
		// g.initGame();
		// cout << "Game start" << endl;
	}
}
    cout << "Game start" << endl;
	g.normalinit();
	// g.run();

}

    
