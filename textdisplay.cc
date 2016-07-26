#include "textdisplay.h"
#include <iostream>
#include <string>
#include <fstream>
#include "player.h"
#include "building.h"
using namespace std;


// Constants:

const int height = 56;
const int width  = 101;

const int box_h = 5;
const int box_w = 9;

const int index_bot_left  = 10;
const int index_top_left  = 20;
const int index_top_right = 30;

const int maxPlayer = 8;
const int maxLevel  = 5;

const char levelSymbol = 'I';


// Colours: (reference from github.com/whitedevops/colors)

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

void setDisplayPosition(int &row, int &col, int index, bool isPlayer) {
  /* --- caculate pos on board for first line in each square --- */
  if (index < index_bot_left) {
    row = 52;
    col = width - (index * box_w) - 9;
  } else if (index < index_top_left) {
    row = height - ((index - index_bot_left) * box_h) - 4;
    col = 2;
  } else if (index < index_top_right) {
    row = 2;
    col = ((index - index_top_left) * box_w) + 2;
  } else if (index < 40) {
    row = ((index - index_top_right) * box_h) + 2;
    col = 92;
  }
  if (isPlayer) row += 3;
}


void displayEffect(int row, int col) {
  /* --- display effects --- */
  if (row == 51) {
    if (col == 64 || col == 82)
      cout << BackgroundYellow << Black;           // Arts1  - Yellow
    if (col == 10 || col == 19 || col == 37) 
      cout << BackgroundLightYellow << Black;      // Arts2  - Light Yellow
  }

  if (col == 1) {
    if (row == 31 || row == 36 || row == 46) 
      cout << BackgroundMagenta << Black;          // Eng    - Magenta
    if (row == 6 || row == 11 || row == 21) 
      cout << BackgroundCyan << Black;             // Health - Cyan
  }

  if (row == 1) {
    if (col == 10 || col == 28 || col == 37) 
      cout << BackgroundLightGreen << Black;       // Env    - Light Green
    if (col == 55 || col == 64 || col == 82) 
      cout << BackgroundBlue << Black;             // Sci1   - Blue
  }

  if (col == 91) {
    if (row == 6 || row == 11 || row == 21) 
      cout << BackgroundLightBlue << Black;        // Sci2   - Light Blue
    if (row == 36 || row == 46) 
      cout << BackgroundLightRed << Black;         // Math   - Light Red
  }
}


void resetEffect(int col) {
  /* --- reset effects --- */
  if (col % box_w == maxPlayer) cout << Default << BackgroundDefault;
}


// Class Functions: /////////////////////////////////////////////////////////////

void TextDisplay::replaceChar(int row, int col, char from, char to,int repeatTimes, bool isRepeated) {
  /* --- used for add or remove players --- */
  char c;
  for (int i = 0; i < repeatTimes; ++i) {
    c = theDisplay[row - 1][col - 1 + i];
    if (c == from) {
      theDisplay[row - 1][col - 1 + i] = to;
      if (!isRepeated) break;
    }
  }
}


void TextDisplay::setString(int row, int col, string s) {
  int len = s.length();
  for (int i = 0; i < len; ++i) {
    theDisplay[row - 1][col - 1 + i] = s.at(i);
  }
}


TextDisplay::TextDisplay(){
  /* --- set up the board --- */
  theDisplay = new char *[height];
  for (int i = 0; i < height; ++i) theDisplay[i] = new char[width];

  ifstream file;
  file.open("board.txt");  // "board.txt" contains the text board frame

  char c;

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      file.get(c);
      theDisplay[i][j] = c;
    }
  }

  file.close();

  /* --- set rules --- */
  setString(13, 44, "DISPLAY TIPS");
  setString(15, 29, "1. O:$ - This property is owned by the player");
  setString(16, 29, "   with the symbol $.");
  setString(17, 29, "2. III - This property has 3 improvements.");
  setString(18, 29, "3. *MC - This property is being mortgaged.");
  setString(19, 29, "4. Properties with the same colour belong to");
  setString(20, 29, "   the same monopoly block.");
}


TextDisplay::~TextDisplay() {
  /* --- clean the board --- */
  for (int i = 0; i < height; ++i) delete [] theDisplay[i];
  delete [] theDisplay;
}


void TextDisplay::display() {
  /* --- display (print) the board --- */
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      displayEffect(i, j);        // display colours for Monopoly Blocks

      if (theDisplay[i][j] == 'O' && theDisplay[i][j + 1] == ':') cout << Dim << Bold;
      else if (theDisplay[i][j] == '#')  cout << Reverse << ' ';

      if (theDisplay[i][j] != '#') cout << theDisplay[i][j]; // normal display

      if (theDisplay[i][j - 1] == ':' || theDisplay[i][j] == '#') {
        cout << ResetAll;
      }

      resetEffect(j);             // end colour to default
    }
  }
}


void TextDisplay::removePlayer(Player *p) {
  /* --- remove the player --- */
  int pos_h, pos_w;
  int pos = p->getPos();

  char symbol = p->getSymbol();

  setDisplayPosition(pos_h, pos_w, pos, true);              // remove Player
  replaceChar(pos_h, pos_w, symbol, ' ', maxPlayer, false);

  for (int row = 39; row < 39 + maxPlayer; ++row) {
    char c = theDisplay[row - 1][27];
    if (c == symbol) {
      int n = 27;
      while (true) {
        if (theDisplay[row - 1][n] == ' ' && theDisplay[row - 1][n + 1] == ' ') break;
        ++n;
      }
      setString(row, n + 1, " (declared bankruptcy)");
      break;
    }
  }
}


void TextDisplay::notify(Player *p, int oldPos) {
  /* --- notify the player (change pos) --- */
  int pos_h, pos_w;
  int pos = p->getPos();

  string name = p->getName();
  char symbol = p->getSymbol();

  setDisplayPosition(pos_h, pos_w, oldPos, true);           // remove Player from old pos
  replaceChar(pos_h, pos_w, symbol, ' ', maxPlayer, false);

  setDisplayPosition(pos_h, pos_w, pos, true);              // add Player to its new pos
  replaceChar(pos_h, pos_w, ' ', symbol, maxPlayer, false);

  setString(37, 28, "Current Players:");

  for (int row = 39; row < 39 + maxPlayer; ++row) {
    char c = theDisplay[row - 1][27];
    if (c == symbol) break;
    else if (c == ' ') {
      theDisplay[row - 1][27] = symbol;
      theDisplay[row - 1][29] = '-';
      setString(row, 32, name);
      break;
    }
  }
}


void TextDisplay::notify(Building *b) {
  /* --- notify the square (display info) --- */
  int info_h, info_w;
  int index = b->getIndex();
  Player *owner = b->getOwner();
  bool isAcademic = b->isAcademic();

  setDisplayPosition(info_h, info_w, index, false);

  int n = 0;
  char symbol;

  if (owner != nullptr) {       // only display ownership when the property is owned
    if (isAcademic) n = 2; else n = 0;
    symbol = owner->getSymbol();

    string ownership = "O:";
    ownership += symbol;
    setString(info_h + n, info_w + 5, ownership);
  }

  int level = b->getImpLevel(); // for displaying level

  if (level >= 0) {
    if (isAcademic) n = 2; else n = 0;
    setString(info_h + n, info_w - 1, "|");

    if (isAcademic) {
      replaceChar(info_h, info_w, levelSymbol, ' ', maxLevel, true);
      replaceChar(info_h, info_w, ' ', levelSymbol, level, true);
    }
  } else {            // for displaying mortgage
    if (isAcademic) n = 2; else n = 0;
    setString(info_h + n, info_w - 1, "*");
  }
}
