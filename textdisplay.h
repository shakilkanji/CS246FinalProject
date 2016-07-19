#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include "game.h"

class Player;
class Square;

class TextDisplay {

  char **theDisplay;

 public:

  TextDisplay();
  ~TextDisplay();

  void display();

  void notify(Player *p);
  void notify(Square *s);
};

#endif
