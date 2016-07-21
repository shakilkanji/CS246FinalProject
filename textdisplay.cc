#include "textdisplay.h"
#include <iostream>
#include <string>
#include <fstream>
#include "player.h"
#include "building.h"
#include "academic.h"
using namespace std;


// Constants:

const int height = 56;
const int width  = 101;

const int box_h = 5;
const int box_w = 9;

const int index_bot_left  = 10;
const int index_top_left  = 20;
const int index_top_right = 30;

const int maxSquare = 40;
const int maxPlayer = 8;
const int maxLevel  = 5;

const char levelSymbol = 'I';


// Colours: (from github.com/whitedevops/colors)

const string ResetAll = "\033[0m";

const string Bold       = "\033[1m";
const string Dim        = "\033[2m";
const string Underlined = "\033[4m";
const string Blink      = "\033[5m";
const string Reverse    = "\033[7m";
const string Hidden     = "\033[8m";

const string ResetBold       = "\033[21m";
const string ResetDim        = "\033[22m";
const string ResetUnderlined = "\033[24m";
const string ResetBlink      = "\033[25m";
const string ResetReverse    = "\033[27m";
const string ResetHidden     = "\033[28m";

const string Default      = "\033[39m";
const string Black        = "\033[30m";
const string Red          = "\033[31m";
const string Green        = "\033[32m";
const string Yellow       = "\033[33m";
const string Blue         = "\033[34m";
const string Magenta      = "\033[35m";
const string Cyan         = "\033[36m";
const string LightGray    = "\033[37m";
const string DarkGray     = "\033[90m";
const string LightRed     = "\033[91m";
const string LightGreen   = "\033[92m";
const string LightYellow  = "\033[93m";
const string LightBlue    = "\033[94m";
const string LightMagenta = "\033[95m";
const string LightCyan    = "\033[96m";
const string White        = "\033[97m";

const string BackgroundDefault      = "\033[49m";
const string BackgroundBlack        = "\033[40m";
const string BackgroundRed          = "\033[41m";
const string BackgroundGreen        = "\033[42m";
const string BackgroundYellow       = "\033[43m";
const string BackgroundBlue         = "\033[44m";
const string BackgroundMagenta      = "\033[45m";
const string BackgroundCyan         = "\033[46m";
const string BackgroundLightGray    = "\033[47m";
const string BackgroundDarkGray     = "\033[100m";
const string BackgroundLightRed     = "\033[101m";
const string BackgroundLightGreen   = "\033[102m";
const string BackgroundLightYellow  = "\033[103m";
const string BackgroundLightBlue    = "\033[104m";
const string BackgroundLightMagenta = "\033[105m";
const string BackgroundLightCyan    = "\033[106m";
const string BackgroundWhite        = "\033[107m";


// Helper Functions: ////////////////////////////////////////////////////////////

void setPlayerDisplayPos(int &pos_h, int &pos_w, int pos) {
  /* --- caculate pos on board for displaying players --- */
  if (pos < index_bot_left) {
    pos_h = 55;
    pos_w = width - (pos * box_w) - 9;
  } else if (pos < index_top_left) {
    pos_h = height - ((pos - index_bot_left) * box_h) - 1;
    pos_w = 2;
  } else if (pos < index_top_right) {
    pos_h = 5;
    pos_w = ((pos - index_top_left) * box_w) + 2;
  } else {
    pos_h = ((pos - index_top_right) * box_h) + 5;
    pos_w = 92;
  }
}


void setSquareDisplayInfo(int &info_h, int &info_w, int index) {
  /* --- caculate pos on board for displaying ownerships and levels --- */
  if (index < index_bot_left) {
    info_h = 52;
    info_w = width - (index * box_w) - 9;
  } else if (index < index_top_left) {
    info_h = height - ((index - index_bot_left) * box_h) - 4;
    info_w = 2;
  } else if (index < index_top_right) {
    info_h = 2;
    info_w = ((index - index_top_left) * box_w) + 2;
  } else {
    info_h = ((index - index_top_right) * box_h) + 2;
    info_w = 92;
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


// Class Functions: /////////////////////////////////////////////////////////////

TextDisplay::TextDisplay(){
  /* --- set up the board --- */
  theDisplay = new char *[height];
  for (int i = 0; i < height; ++i) theDisplay[i] = new char[width];

  int info_h;
  int info_w;
  char c;

  ifstream file;
  file.open("board.txt");  // "board.txt" contains the text board frame

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      file.get(c);
      theDisplay[i][j] = c;
    }
  }

  for (int index = 0; index < maxSquare; ++index){
    setSquareDisplayInfo(info_h, info_w, index);
    
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
  /* --- display (print) the board --- */
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      cout << theDisplay[i][j];
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
  if (!b->isAcademic()) info_h -= 2;

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
