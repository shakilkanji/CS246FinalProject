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
  	Building(const int index, const std::string name, const int cost);
  	virtual ~Destructor() = 0;

  	Player *getOwner()
};

#endif
