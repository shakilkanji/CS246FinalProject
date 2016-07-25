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
  int numTimsCups;

  int balance;
  int position;

  int DCTurn;

  bool bankrupt;

 public:
  Player(char symbol, std::string playerName);
  Player(char symbol, std::string playerName, int numTimsCups, int balance, int position, int DCTurn);
  ~Player();

  char getSymbol() ;
  std::string getName() ;

  void updateBalance(int n);
  int getBalance() const;

  void setNumGym(int n);
  int getNumGym() const;

  void setNumRes(int n);
  int getNumRes() const;

  void setNumTimsCups(int n);
  int getNumTimsCups() const;

  void setDCTurn(int n);
  int getDCTurn() const;

  void setPos(int n);
  int getPos() const;

  bool isBankrupt() const;
  void setBankrupt(); // will only be set immediately before a player is to be deleted from the game
};

#endif
