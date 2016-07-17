#ifndef _PLAYER_H_
#define _PLAYER_H_

class Game;

class Player {
  int numGym;
  int numRes;
  char symbol;
  std::string playerName; 
  int balance;
  int position;

  int DCTurn;

  Game *g;

 public:
  Player(char symbol,std::string playerName, int numGym, int numRes, int balance, int position, int DCTurn, Game *g);
  ~Player();

  updateBalance(int n);
  
  char getSymbol();
  
  std::string getName();

  int getAssets();
  int getTotalValue();

  void setNumGym(int n);
  int getNumGym();

  void setNumRes(int n);
  int getNumRes();

  void setDCTurn(int n);
  int getDCTurn();

  void setPos(int n);
  int getPos();

  bool isBankrupt();
};

#endif
