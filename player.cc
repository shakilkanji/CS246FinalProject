#include <string>
#include <vector>
#include "player.h"

Player::Player(int numGym, int numRes, int balance, int position, int DCTurn, Game *g):
  numGym{numGym}, numRes{numRes}, balance{balance}, position{position}, DCTurn{DCTurn}, g{g} {}

Player::~Player() { delete g; }


char getSymbol() const { 
  return symbol; 
}

string getName() const { 
  return playerName; 
}


void Player::updateBalance(int n) { 
  balance += n; 
}


/*void Player::addProperty(Building *b) {
  buildings.emplace_back(b);
}


int Player::getAssets() {
  int assets = 0;
  for (int i = 0; i < buildings.size(); ++i) {
    assets += buildings[i]->cost;
  }
}


int Player::getTotalValue() const {
  int imp = 0;
  for (int i = 0; i < buildings.size(); ++i) {
    imp += ( buildings[i]->impLevel * buildings[i]->impCost);
  }
  return balance + getAssets() + imp;
}*/


void Player::setNumGym(int n) { 
  numGym += n; 
}
int Player::getNumGym() const { 
  return numGym; 
}


void Player::setNumRes(int n) { 
  numRes += n; 
}
int Player::getNumRes() const { 
  return numRes; 
}


void Player::setDCTurn(int n) { 
  DCTurn += n; 
}
int Player::getDCTurn() const { 
  return DCTurn; 
}


void Player::setPos(int n) { 
  position += n; 
}
int Player::getPos() const { 
  return position; 
}

