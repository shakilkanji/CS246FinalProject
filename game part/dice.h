#ifndef _DICE_H_
#define _DICE_H_

#include <string>
#include <sstream>
#include <iostream>

class Dice {
   int firstdeice;
   int seconddice;
   bool test;
   int seed;

   public:
   Dice();
   ~Dice();
   void settest();
   bool pair();
   // int sum();
   int roll();

}







#endif