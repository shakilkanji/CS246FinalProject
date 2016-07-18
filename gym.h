#ifndef __GYM_H__
#define __GYM_H__
#include <iostream>
#include <string>

class Gym : public Building {
  public:
  	Gym(Game *game, const int index, const std::string name);
  	Gym(Game *game, const int index, const std::string name, Player *owner, bool mortgaged);
  	~Gym();

  	int getFees() const;
};

#endif
