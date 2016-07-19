#include <iostream>
#include <string>
#include <fstream>
#include "textdisplay.h"
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


void TextDisplay::notify(Player *p) {
  /* --- notify the player --- */
  int pos_h;
  int pos_w;

  int pos = p->getPos();

  if (pos < 10) {
    pos_h = height - (pos * 5 + 1);
    pos_w = 92;
  } else if (pos < 20) {
    pos_h = 5;
    pos_w = width - (pos * 9 + 81);
  } else if (pos < 30) {
    pos_h = (pos * 5) - 95;
    pos_w = 2;
  } else {
    pos_h = 55;
    pos_w = (pos * 9) - 268;
  }

  for (int i = 0; i < maxPlayer; ++i) {
    char c = theDisplay[pos_h - 1][pos_w - 1 + i];
    if (c == ' ') {
      theDisplay[pos_h - 1][pos_w - 1 + i] = p->getSymbol();
      break;
    }
  }
}

void TextDisplay::notify(Square *s) {
  /* --- notify the square --- */
  int info_h;
  int info_w;

  int index = s->getIndex();

  if (index < 10) {
    info_h = height - (index * 5 + 4);
    info_w = 92;
  } else if (index < 20) {
    info_h = 2;
    info_w = width - (index * 9 + 81);
  } else if (index < 30) {
    info_h = (index * 5) - 98;
    info_w = 2;
  } else {
    info_h = 52;
    info_w = (index * 9) - 268;
  }

  Building *building = dynamic_cast<Building *>(s);
  Player *owner = building->getOwner();

  Academic *academic = dynamic_cast<Academic *>(s);
  int level = academic->getImpLevel();

  if (level != 0) {
    theDisplay[info_h - 1][info_w - 1] = 'O';
    theDisplay[info_h - 1][info_w] = ':';
    theDisplay[info_h - 1][info_w + 1] = level;
  }

  if (owner != nullptr) {
    theDisplay[info_h - 1][info_w + 4] = 'L';
    theDisplay[info_h - 1][info_w + 5] = ':';
    theDisplay[info_h - 1][info_w + 6] = owner->getSymbol();
  }
}
