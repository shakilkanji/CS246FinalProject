#ifndef __GYM_H__
#define __GYM_H__
#include <iostream>
#include <string>
#include "building.h"

class Gym : public Building {
  public:
  	Gym(Game *game, const int index, const std::string name, const int cost);
  	Gym(Game *game, const int index, const std::string name, const int cost, Player *owner, bool mortgaged);
  	~Gym();

  	int getFees() const;
};

#endif
