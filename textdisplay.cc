#include <iostream>
#include <string>
#include <fstream>
#include "textdisplay.h"
#include "player.h"
using namespace std;


const int height = 56;
const int width = 101;

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
  int pos = p->getPos();


}

void TextDisplay::notify(Square *s) {
  int info_h;
  int info_w;

  int index = s->getIndex();

  switch (index) {
    case 1:
      info_h = 47; info_w = 92;
      break;
    case 3:
      info_h = 37; info_w = 92;
      break;
    case 6:
      info_h = 22; info_w = 92;
      break;
    case 8:
      info_h = 12; info_w = 92;
      break;
    case 9:
      info_h = 7; info_w = 92;
      break;
    case 11:
      info_h = 2; info_w = 83;
      break;
    case 13:
      info_h = 2; info_w = 65;
      break;
    case 14:
      info_h = 2; info_w = 56;
      break;
    case 16:
      info_h = 2; info_w = 38;
      break;
    case 17:
      info_h = 2; info_w = 29;
      break;
    case 19:
      info_h = 2; info_w = 11;
      break;
    case 21:
      info_h = 7; info_w = 2;
      break;
    case 22:
      info_h = 12; info_w = 2;
      break;
    case 24: 
      info_h = 22; info_w = 2;
      break;
    case 26:
      info_h = 32; info_w = 2;
      break;
    case 27:
      info_h = 37; info_w = 2;
      break;
    case 29:
      info_h = 47; info_w = 2;
      break;
    case 31:
      info_h = 52; info_w = 11;
      break;
    case 32:
      info_h = 52; info_w = 20;
      break;
    case 34:
      info_h = 52; info_w = 38;
      break;
    case 37:
      info_h = 52; info_w = 65;
      break;
    case 39:
      info_h = 52; info_w = 83;
      break;
  }
}
