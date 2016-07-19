#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <iostream>
#include "player.h"
#include "square.h"
#include "building.h"
#include "academic.h"
#include "gym.h"
#include "residence.h"
#include "textdisplay.h"

class Game {
 // std::vector<std::vector<Player>> Players;
  std::string playername[8];
  char chosensymbol[8];
  Player *player[8];
  int numplayer;
  int currentplayer; 
  Square *gameboard[40];
  // Dice *dice;
  int rimcup;
  // BoardDisplay * display;
  int sumofdice;
  //dice part
   int firstdeice;
   int seconddice;
   bool test;
   bool rolled;
   int roll_time;
   bool isWon;
   // TextDisplay
   TextDisplay *td;

   int getPropertyIndex(std::string property);
   int getplayer(std::string name);

  public:
  	Game();
	  ~Game();
   
   void run();
   void normalinit();
   void next();
   void settest();
   void asktobuy(Building *building, Player *buyer);
   void auction();
   void assets();
   bool checkmonoimprov(std::string building);
   bool dicepair();
   int getsumdice();
   int diceroll(); 
   void forceBankruptcy(Player *landedPlayer, int fee);   // Player owes bank more than their current balance
};

/***************
 0:COLLECT OSAP     1:AL             2:SLC            3:ML          4:TUITION
 5:MKV              6:ECH            7:NEEDLES HALL   8:PAS         9:HH
 10:DC Tims Line    11:RCH           12:PAC           13:DWE        14:CPH
 15:UWP             16:LHI           17:SLC           18:BMH        19:OPT
 20:Goose Nesting   21:EV1           22:NEEDLES HALL  23:EV2        24:EV3
 25:V1              26:PHYS          27:B1            28:CIF        29:B2
 30:GO TO TIMS      31:EIT           32:ESC           33:SLC        34:C2
 35:REV             36:NEEDLES HALL  37:MC            38:COOP FEE   39:DC
 **************/

#endif