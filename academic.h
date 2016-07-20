#ifndef __ACADEMIC_H__
#define __ACADEMIC_H__
#include <iostream>
#include <string>
#include "building.h"

class Academic : public Building {
	const int impCost;
	const std::string monoBlock;
	int fees[6];

  public:
  	Academic(Game *game, const int index, const std::string name, const int cost, const int impCost, 
  		const std::string monoBlock, const int baseFee, const int oneImpFee, const int twoImpFee, 
  		const int threeImpFee, const int fourImpFee, const int fiveImpFee);
  	Academic(Game *game, const int index, const std::string name, const int cost, Player *owner, 
  		bool mortgaged, const int impCost, const std::string monoBlock, int impLevel,
  		const int baseFee, const int oneImpFee, const int twoImpFee, const int threeImpFee, 
  		const int fourImpFee, const int fiveImpFee);

  	~Academic();

  	int getFees() const override;

    std::string getMonoBlock() const;

    int getImpCost() const;

  	int getValue() const override;	// during bankruptcy calculation, divide by 2
};

std::ostream& operator<<(std::ostream& out, const Academic& a);

#endif
