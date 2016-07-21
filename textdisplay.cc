#include <iostream>
#include <string>
#include <fstream>
#include "textdisplay.h"
#include "player.h"
#include "building.h"
#include "academic.h"
using namespace std;


// Constants:
const int height = 56;
const int width = 101;

const int box_h = 5;
const int box_w = 9;

const int maxPlayer = 8;
const int maxLevel = 5;
const char levelSymbol = 'I';

const int numNonBuild = 6;
const int nonBuilding[numNonBuild] = {5, 12, 15, 25, 28, 35};


TextDisplay::TextDisplay(){
  /* --- set up the board --- */
  theDisplay = new char *[height];
  for (int i = 0; i < height; ++i) {
    theDisplay[i] = new char[width];
  }

  ifstream file;
  file.open("board.txt");

  char c;

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      file.get(c);
      theDisplay[i][j] = c;
    }
  }

  file.close();
}


TextDisplay::~TextDisplay() {
  /* --- clean the board --- */
  for (int i = 0; i < height; ++i) {
    delete [] theDisplay[i];
  }
  delete [] theDisplay;
}


void TextDisplay::display() {
  /* --- display the board --- */
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      cout << theDisplay[i][j];
    }
  }
}


void setPlayerDisplayPos(int &pos_h, int &pos_w, int pos) {
  /* --- caculate pos on board for displaying players --- */
  if (pos < 10) {
    pos_h = 55;
    pos_w = width - (pos * box_w) - 9;
  } else if (pos < 20) {
    pos_h = height - ((pos - 10) * box_h) - 1;
    pos_w = 2;
  } else if (pos < 30) {
    pos_h = 5;
    pos_w = ((pos - 20) * box_w) + 2;
  } else {
    pos_h = ((pos - 30) * box_h) + 5;
    pos_w = 92;
  }
}


void setSquareDisplayInfo(int &info_h, int &info_w, int index) {
  /* --- caculate pos on board for displaying ownerships and levels --- */
  if (index < 10) {
    info_h = 52;
    info_w = width - (index * box_w) - 9;
  } else if (index < 20) {
    info_h = height - ((index - 10) * box_h) - 4;
    info_w = 2;
  } else if (index < 30) {
    info_h = 2;
    info_w = ((index - 20) * box_w) + 2;
  } else {
    info_h = ((index - 30) * box_h) + 2;
    info_w = 92;
  }

  for (int i = 0; i < numNonBuild; ++i) {
    if (index == nonBuilding[i]) info_h -= 2;
  }
}


void replaceChar(int pos_h, int pos_w, char **theDisplay, 
  char from, char to, int repeatTimes, bool isRepeated) {
  /* --- used for add or remove players --- */
  for (int i = 0; i < repeatTimes; ++i) {
    char c = theDisplay[pos_h - 1][pos_w - 1 + i];
    if (c == from) {
      theDisplay[pos_h - 1][pos_w - 1 + i] = to;
      if (!isRepeated) break;
    }
  }
}


void TextDisplay::removePlayer(Player *p) {
  /* --- remove the player --- */
  int pos_h;
  int pos_w;
  int pos = p->getPos();

  char symbol = p->getSymbol();

  setPlayerDisplayPos(pos_h, pos_w, pos);             // remove Player
  replaceChar(pos_h, pos_w, theDisplay, symbol, ' ', maxPlayer, false);
}


void TextDisplay::notify(Player *p, int oldPos) {
  /* --- notify the player (change pos) --- */
  int pos_h;
  int pos_w;
  int pos = p->getPos();

  char symbol = p->getSymbol();

  setPlayerDisplayPos(pos_h, pos_w, oldPos);           // remove Player from old pos
  replaceChar(pos_h, pos_w, theDisplay, symbol, ' ', maxPlayer, false);

  setPlayerDisplayPos(pos_h, pos_w, pos);              // add Player to its new pos
  replaceChar(pos_h, pos_w, theDisplay, ' ', symbol, maxPlayer, false);
}


void TextDisplay::notify(Building *b) {
  /* --- notify the square (display info) --- */
  int info_h;
  int info_w;
  int index = b->getIndex();

  setSquareDisplayInfo(info_h, info_w, index);

  Player *owner = b->getOwner();

  if (owner != nullptr) {    // only display ownership when the property is owned
    theDisplay[info_h + 1][info_w + 4] = 'O';
    theDisplay[info_h + 1][info_w + 5] = ':';
    theDisplay[info_h + 1][info_w + 6] = owner->getSymbol();
  }
  
  int level = b->getImpLevel();

  // cout << "TextDisplay" << level << endl;
  // replaceChar(info_h, info_w, theDisplay, levelSymbol, ' ', maxLevel);
  // replaceChar(info_h, info_w, theDisplay, ' ', levelSymbol, level);


  replaceChar(info_h, info_w, theDisplay, levelSymbol, ' ', maxLevel, true);
  replaceChar(info_h, info_w, theDisplay, ' ', levelSymbol, level, true);

}
