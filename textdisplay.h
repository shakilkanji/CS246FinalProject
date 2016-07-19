#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

class Player;
class Building;

class TextDisplay {

  char **theDisplay;

 public:

  TextDisplay();
  ~TextDisplay();

  void display();
  void removePlayer(Player *p);
  void notify(Player *p, int oldPos);
  void notify(Building *b);
};

#endif
