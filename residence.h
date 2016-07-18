#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__
#include <iostream>
#include <string>

class Residence : public Building {
  public:
  	Residence(Game *game, const int index, const std::string name);
  	Residence(Game *game, const int index, const std::string name, Player *owner, bool mortgaged);
  	~Residence();

  	int getFees() const;
};

#endif
