#include <string>
#include <vector>
#include "player.h"

using namespace std;
Player::Player(char symbol, string playerName) : symbol(symbol), playerName(playerName) {
  numGym = 0;
  numRes = 0;
  balance = 1500;
  position = 0;
  DCTurn = -1;
  numTimsCups = 0;
  bankrupt = false;
}

Player::Player(char symbol, string playerName, int numTimsCups, int balance, int position, int DCTurn) : 
  symbol(symbol), playerName(playerName), numTimsCups(numTimsCups), balance(balance), position(position), 
  DCTurn(DCTurn) {
    bankrupt = false;
  }

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


// void Player::setNumGym(int n) { 
//   numGym = n; 
// }
int Player::getNumGym() const { 
  
  return numGym; 
}


// void Player::setNumRes(int n) { 
//   numRes = n; 
// }
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

bool Player::isBankrupt() const {
  return bankrupt;
}

void Player::setBankrupt() {
  bankrupt = true;
}
