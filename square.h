#ifndef __SQUARE_H__
#define __SQUARE_H__
#include <iostream>
#include <string>
#include "player.h"

class Game;

class Square {
  protected:
  Game *game;			// pointer to the Game holding this square
	const int index;	// stores the square's location (0-39) on Gameboard
	const std::string name;	// stores the name of the square to be displayed

  public:
  	Square(Game *game, const int index, const std::string name);
  	virtual ~Square();

  	int getIndex() const;
  	std::string getName() const;
  	virtual void notify(Player *landedPlayer);
};


#endif
