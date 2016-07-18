#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__
#include <iostream>
#include <string>
#include "building.h"

class Residence : public Building {
  public:
  	Residence(Game *game, const int index, const std::string name, const int cost);
  	Residence(Game *game, const int index, const std::string name, const int cost, Player *owner, bool mortgaged);
  	~Residence();

  	int getFees() const;
};

#endif
