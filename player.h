#ifndef _PLAYER_H_
#define _PLAYER_H_

class Game;

class Player {
  int numGym;
  int numRes;

  int balance;
  int position;

  int DCTurn;

  Game *g;

 public:
  Player(int numGym, int numRes, int balance, int position, int DCTurn, Game *g);
  ~Player();

  updateBalance(int n);

  int getAssets();
  int getTotalValue();

  setNumGym(int n);
  int getNumGym();

  setNumRes(int n);
  int getNumRes();

  setDCTurn(int n);
  int getDCTurn();

  setPos(int n);
  int getPos();

  bool isBankrupt();
};

#endif
