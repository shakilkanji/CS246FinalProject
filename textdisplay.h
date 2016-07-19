#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

class TextDisplay {

  char **theDisplay;

 public:

  TextDisplay();
  ~TextDisplay();

  void display();

  void addPlayer(Player *p);
  void notify(Player *p);
  void notify(Square *s);
};

#endif
