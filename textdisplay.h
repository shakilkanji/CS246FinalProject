#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <string>

class Player;
class Building;


class TextDisplay {

  char **theDisplay;

  void replaceChar(int row, int col, char from, char to,int repeatTimes, bool isRepeated);
  void setString(int row, int col, std::string s);

 public:
  
  TextDisplay();
  ~TextDisplay();

  void display();

  void removePlayer(Player *p);
  
  void notify(Player *p, int oldPos);
  void notify(Building *b);
};

#endif
