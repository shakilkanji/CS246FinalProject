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
}


void setSquareDisplayInfo(int &info_h, int &info_w, int index) {
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
  if (index == 5 || index == 12 || index == 15 || index == 25 || index == 28 || index == 35) {
    ++info_h;
  }
}


void TextDisplay::notify(Player *p, int oldPos) {
  /* --- notify the player --- */
  int pos_h;
  int pos_w;
  int pos = p->getPos();

  char symbol = p->getSymbol();

  setPlayerDisplayPos(pos_h, pos_w, oldPos);

  for (int i = 0; i < maxPlayer; ++i) {
    char c = theDisplay[pos_h - 1][pos_w - 1 + i];
    if (c == symbol) {
      theDisplay[pos_h - 1][pos_w - 1 + i] = ' ';
      break;
    }
  }

  setPlayerDisplayPos(pos_h, pos_w, pos);

  for (int i = 0; i < maxPlayer; ++i) {
    char c = theDisplay[pos_h - 1][pos_w - 1 + i];
    if (c == ' ') {
      theDisplay[pos_h - 1][pos_w - 1 + i] = symbol;
      break;
    }
  }
}


void TextDisplay::notify(Building *b) {
  /* --- notify the square --- */
  int info_h;
  int info_w;
  int index = s->getIndex();

  setSquareDisplayInfo(info_h, info_w, index);

  Player *owner = building->getOwner();

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
