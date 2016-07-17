#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include <vector>

class Game;


class Player {
  char symbol;
  std::string playerName; 

  int numGym;
  int numRes;

  int balance;
  int position;

  int DCTurn;

  Game *g;
  //std::vector <Building *> buildings;

 public:
  Player(char symbol,std::string playerName, Game *g);
  ~Player();

  char getSymbol() ;
  std::string getName() ;

  void updateBalance(int n);
  //void addProperty(Building *b);

  //int getAssets() const;
  //int getTotalValue() const;

  void setNumGym(int n);
  int getNumGym() const;

  void setNumRes(int n);
  int getNumRes() const;

  void setDCTurn(int n);
  int getDCTurn() const;

  void setPos(int n);
  int getPos() const;
};

#endif
