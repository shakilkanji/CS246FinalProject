#ifndef __SQUARE_H__
#define __SQUARE_H__
#include <iostream>
#include <string>

class Player;

class Square {
  protected:
	const int index;	// stores the square's location (0-39) on Gameboard
	const std::string name;	// stores the name of the square to be displayed

  public:
  	Square(const int index, const std::string name);
  	virtual ~Square() = 0;	// pure virtual destructor

  	int getIndex() const;
  	std::string getName() const;

  	virtual void notify(Player *);
};


#endif
