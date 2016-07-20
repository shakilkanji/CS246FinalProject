#include <string>
#include <vector>
#include "player.h"

using namespace std;
Player::Player(char symbol, string playerName, Game *g) : symbol(symbol), playerName(playerName), g(g) {
  numGym = 0;
  numRes = 0;
  balance = 1500;
  position = 0;
  DCTurn = -1;
}

Player::Player(char symbol, string playerName, Game *g, int numTimsCups, int balance, int position, int DCTurn) : 
  symbol(symbol), playerName(playerName), g(g), numTimsCups(numTimsCups), balance(balance), position(position), 
  DCTurn(DCTurn) {}

Player::~Player() {}

char Player::getSymbol()  { 
  return symbol; 
}

string Player::getName()  { 
  return playerName; 
}


void Player::updateBalance(int n) { 
  balance += n; 
}

int Player::getBalance() const {
  return balance;
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
  numGym = n; 
}
int Player::getNumGym() const { 
  return numGym; 
}


void Player::setNumRes(int n) { 
  numRes = n; 
}
int Player::getNumRes() const { 
  return numRes; 
}

void Player::setNumTimsCups(int n) {
  numTimsCups = n;
}

int Player::getNumTimsCups() const {
  return numTimsCups;
}

void Player::setDCTurn(int n) { 
  DCTurn = n; 
}
int Player::getDCTurn() const { 
  return DCTurn; 
}


void Player::setPos(int n) { 
  position = n; 
}
int Player::getPos() const { 
  return position; 
}

