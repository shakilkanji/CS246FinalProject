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
  	Building(Game *game, const int index, const std::string name, const int cost, 
  		Player *owner, bool mortgaged);		// Constructor for loaded games (not default)
  	virtual ~Building();

  	Player *getOwner() const;
  	void setOwner(Player *newOwner);

  	virtual int getFees() const = 0;

  	bool getMortgaged() const;
  	void setMortgaged(bool isMortgaged);

  	virtual int getValue() const;

  	int getCost() const;

  	void notify(Player *landedPlayer) override;

    bool isAcademic();
};

std::ostream& operator<<(std::ostream& out, const Building& b);

#endif
