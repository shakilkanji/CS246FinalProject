#ifndef __BUILDING_H__
#define __BUILDING_H__
#include <iostream>
#include <string>
#include "square.h"

class Building : public Square {
  protected:
  	const int cost;
  	Player *owner;
  	bool mortgaged;

  public:
  	Building(Game *game, const int index, const std::string name, const int cost);
  	virtual ~Destructor();

  	Player *getOwner() const;
  	void setOwner(Player *newOwner);

  	virtual int getFees() = 0;

  	bool getMortgaged() const;
  	void setMortgaged(bool isMortgaged);

  	virtual int getValue() const;

  	int getCost() const;

  	virtual void notify(Player *landedPlayer) = 0;
};

#endif