#include <iostream>
#include <string>
#include <fstream>
#include "textdisplay.h"
#include "square.h"
#include "player.h"
#include "building.h"
#include "academic.h"
using namespace std;


const int height = 56;
const int width = 101;
const int maxPlayer = 8;

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
  if (pos < 10) {
    pos_h = 55;
    pos_w = width - (pos * 9) - 9;
  } else if (pos < 20) {
    pos_h = height - ((pos - 10) * 5) - 1;
    pos_w = 2;
  } else if (pos < 30) {
    pos_h = 5;
    pos_w = ((pos - 20) * 9) + 2;
  } else if (pos < 40) {
    pos_h = ((pos - 30) * 5) + 5;
    pos_w = 92;
  }
}


void setSquareDisplayInfo(int &info_h, int &info_w, int index) {
  if (index < 10) {
    info_h = 52;
    info_w = width - (index * 9) - 9;
  } else if (index < 20) {
    info_h = height - ((index - 10) * 5) - 4;
    info_w = 2;
  } else if (index < 30) {
    info_h = 2;
    info_w = ((index - 20) * 9) + 2;
  } else if (index < 40) {
    info_h = ((index - 30) * 5) + 1;
    info_w = 92;
  }

  if (index == 5 || index == 12 || index == 15 || index == 25 || index == 28 || index == 35) {
    ++info_h;
  }
}


void replaceChar(int pos_h, int pos_w, char **theDisplay, char from, char to) {
  for (int i = 0; i < maxPlayer; ++i) {
    char c = theDisplay[pos_h - 1][pos_w - 1 + i];
    if (c == from) {
      theDisplay[pos_h - 1][pos_w - 1 + i] = to;
      break;
    }
  }
}


void TextDisplay::removePlayer(Player *p) {
  /* --- notify the player --- */
  int pos_h;
  int pos_w;
  int pos = p->getPos();

  char symbol = p->getSymbol();

  setPlayerDisplayPos(pos_h, pos_w, pos);
  replaceChar(pos_h, pos_w, theDisplay, symbol, ' ');
}


void TextDisplay::notify(Player *p, int oldPos) {
  /* --- notify the player --- */
  int pos_h;
  int pos_w;
  int pos = p->getPos();

  char symbol = p->getSymbol();

  setPlayerDisplayPos(pos_h, pos_w, oldPos);
  replaceChar(pos_h, pos_w, theDisplay, symbol, ' ');

  setPlayerDisplayPos(pos_h, pos_w, pos);
  replaceChar(pos_h, pos_w, theDisplay, ' ', symbol);
}


void TextDisplay::notify(Building *b) {
  /* --- notify the square --- */
  int info_h;
  int info_w;
  int index = b->getIndex();

  setSquareDisplayInfo(info_h, info_w, index);

  Player *owner = b->getOwner();

  if (owner != nullptr) {
    theDisplay[info_h - 1][info_w - 1] = 'O';
    theDisplay[info_h - 1][info_w] = ':';
    theDisplay[info_h - 1][info_w + 1] = owner->getSymbol();
  }

  int level = 0;
  Academic *academic = dynamic_cast<Academic *>(b);
  level = academic->getImpLevel();

  if (level != 0) {
    theDisplay[info_h - 1][info_w + 4] = 'L';
    theDisplay[info_h - 1][info_w + 5] = ':';
    theDisplay[info_h - 1][info_w + 6] = level;
  }
}
