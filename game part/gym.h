#ifndef __GYM_H__
#define __GYM_H__
#include <iostream>
#include <string>

class Gym : public Building {
  public:
  	Gym(Game *game, const int index, const std::string name);
  	~Gym();

  	int getFees() const;

  	void notify(Player *landedPlayer);
};

#endif
