#ifndef __ACADEMIC_H__
#define __ACADEMIC_H__
#include <iostream>
#include <string>

class Academic : public Building {
	int impLevel;
	const int impCost;
	const std::string monoBlock;
	bool monopolized;
	int Fees[6];

  public:
  	Academic(Game *game, const int index, const std::string name, const int cost, const int impCost, 
  		const std::string monoBlock, const int baseFee, const int oneImpFee, const int twoImpFee, 
  		const int threeImpFee, const int fourImpFee, const int fiveImpFee);
  	~Academic();

  	int getFees() const;

  	int getImpLevel() const;
  	void setImpLevel(int newImpLevel);

  	bool isMonopolized() const;

  	int getValue() const;

  	void notify(Player *landedPlayer);
};

#endif
