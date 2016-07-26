#include "game.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;

Game::Game() : numplayer(0), currentplayer(0), rimcup(0), firstdice(0), seconddice(0),
  test(false), rolled(false), roll_time(0) {

  td = new TextDisplay;
  isWon = false;

  for(int i = 0 ; i < 8 ; i++){
    player[i] = nullptr;
  }
  gameboard[0] = new Square(this, 0, "COLLECT OSAP");
  gameboard[1] = new Academic(this, 1, "AL", 40, 50, "Arts1", 2, 10, 30, 90, 160, 250);
  gameboard[2] = new Square(this, 2, "SLC");
  gameboard[3] = new Academic(this, 3, "ML", 40, 50, "Arts1", 4, 20, 60, 180, 320, 450);
  gameboard[4] = new Square(this, 4, "TUITION");
  gameboard[5] = new Residence(this, 5, "MKV", 200);
  gameboard[6] = new Academic(this, 6, "ECH", 100, 50, "Arts2", 6, 30, 90, 270, 400, 550);
  gameboard[7] = new Square(this, 7, "NEEDLES HALL");
  gameboard[8] = new Academic(this, 8, "PAS", 100, 50, "Arts2", 6, 30, 90, 270, 400, 550);
  gameboard[9] = new Academic(this, 9, "HH", 120, 50, "Arts2", 8, 40, 100, 300, 450, 600);
  gameboard[10] = new Square(this, 10, "DC Tims Line");
  gameboard[11] = new Academic(this, 11, "RCH", 140, 100, "Eng", 10, 50, 150, 450, 625, 750);
  gameboard[12] = new Gym(this, 12, "PAC", 150);
  gameboard[13] = new Academic(this, 13, "DWE", 140, 100, "Eng", 10, 50, 150, 450, 625, 750);
  gameboard[14] = new Academic(this, 14, "CPH", 160, 100, "Eng", 12, 60, 180, 500, 700, 900);
  gameboard[15] = new Residence(this, 15, "UWP", 200);
  gameboard[16] = new Academic(this, 16, "LHI", 180, 100, "Health", 14, 70, 200, 550, 750, 950);
  gameboard[17] = new Square(this, 17, "SLC");
  gameboard[18] = new Academic(this, 18, "BMH", 180, 100, "Health", 14, 70, 200, 550, 750, 950);
  gameboard[19] = new Academic(this, 19, "OPT", 200, 100, "Health", 16, 80, 220, 600, 800, 1000);
  gameboard[20] = new Square(this, 20, "Goose Nesting");
  gameboard[21] = new Academic(this, 21, "EV1", 220, 150, "Env", 18, 90, 250, 700, 875, 1050);
  gameboard[22] = new Square(this, 22, "NEEDLES HALL");
  gameboard[23] = new Academic(this, 23, "EV2", 220, 150, "Env", 18, 90, 250, 700, 875, 1050);
  gameboard[24] = new Academic(this, 24, "EV3", 240, 150, "Env", 20, 100, 300, 750, 925, 1100);
  gameboard[25] = new Residence(this, 25, "V1", 200);
  gameboard[26] = new Academic(this, 26, "PHYS", 260, 150, "Sci1", 22, 110, 330, 800, 975, 1150);
  gameboard[27] = new Academic(this, 27, "B1", 260, 150, "Sci1", 22, 110, 330, 800, 975, 1150);
  gameboard[28] = new Gym(this, 28, "CIF", 150);
  gameboard[29] = new Academic(this, 29, "B2", 280, 150, "Sci1", 24, 120, 360, 850, 1025, 1200);
  gameboard[30] = new Square(this, 30, "GO TO TIMS");
  gameboard[31] = new Academic(this, 31, "EIT", 300, 200, "Sci2", 26, 130, 390, 900, 1100, 1275);
  gameboard[32] = new Academic(this, 32, "ESC", 300, 200, "Sci2", 26, 130, 390, 900, 1100, 1275);
  gameboard[33] = new Square(this, 33, "SLC");
  gameboard[34] = new Academic(this, 34, "C2", 320, 200, "Sci2", 28, 150, 450, 1000, 1200, 1400);
  gameboard[35] = new Residence(this, 35, "REV", 200);
  gameboard[36] = new Square(this, 36, "NEEDLES HALL");
  gameboard[37] = new Academic(this, 37, "MC", 350, 200, "Math", 35, 175, 500, 1100, 1300, 1500);
  gameboard[38] = new Square(this, 38, "COOP FEE");
  gameboard[39] = new Academic(this, 39, "DC", 400, 200, "Math", 50, 200, 600, 1400, 1700, 2000);
}

Game::~Game(){
  for (int i = 0; i < 40; ++i) {
    delete gameboard[i];
  }
  for (int i = 0; i < 8; ++i) {
    if (player[i]) delete player[i];
  }

  delete td;
}


void Game::normalinit(){
  td->display();

  cout << ">> Welcome to Watopoly!" << endl;
  cout << ">> Please enter the number of players in the game [2-8]:" << endl;

  string s;
  int temp_num;

  while (cin >> s) {
    istringstream ss{s};
    if (ss >> temp_num) {
      if (temp_num <= 8 && temp_num >= 2) {
        numplayer = temp_num;
        break;
      } else {
        cout << ">> Your input is out of range, please enter a number between 2 and 8 (inclusive)." << endl;
      } 
    } else {
      cout << ">> You have to enter a number." << endl;
    }
  }

   
  //initial player's name
  for( int current = 0 ; current < numplayer ; current++ ){
    cout << endl;
    cout << ">> Hello, player" << current + 1 << "!" << endl;
    cout << ">> Please input your name:" << endl;;
        
    string temp_name;
        

    while(cin >> temp_name){
      bool chosen = false;

      if( temp_name == "BANK"){
  	    cout << ">> Sorry, you cannot choose this name, please choose a different one." << endl;
  		  cin >> temp_name;
      }

      for(int i = 0 ; i <current ;i++ ){
        if(temp_name == playername[i]){
       	  chosen = true;
        }
      }

      if(chosen == true ){
      	cout << ">> Someone has already chosen this name, please change to another one." << endl;
      } else{
      	playername[current] = temp_name;
      	break;
      }
    }


    //initial player's character 
    cout << endl;
    cout << ">> Hello, " << playername[current] << "! Please choose an character which represents you." << endl;
    cout << ">> You can choose from:" << endl;
    cout << ">> G (Goose) / B (GRT BUS) / D (Tim Hortons Doughnut) / P (Professor)" <<endl;
    cout << ">> S (Student) / $ (Money) / L (Laptop) / T (Pink tie)" << endl;

    char temp_symbol;
    
    while( cin >> temp_symbol){ 
    	bool chosen_symbol = false; 

      if(temp_symbol=='G'||temp_symbol=='B'||temp_symbol=='D'||temp_symbol=='P'
      	||temp_symbol=='S'||temp_symbol=='$'||temp_symbol=='L'||temp_symbol=='T'){
            
        for(int i = 0; i < current ; i++){
        	if(temp_symbol == chosensymbol[i]){
     	      chosen_symbol = true;
          }
        }
            
        if(chosen_symbol == true ){
        	cout << ">> Someone has already chosen this character, please change to another one" << endl;
        } else {
        	chosensymbol[current] = temp_symbol;
    	    break;
        }
      } else {
      	cout << ">> Please enter a valid character. " << endl;
      }
    }
  }
      
  for(int i = 0 ; i < numplayer ; i++){
  player[i] = new Player(chosensymbol[i], playername[i]);
  }

  for(int i = 0 ; i < numplayer ; i++){       
  cout << player[i]->getSymbol() << " " << player[i]->getName() << endl;
  }

}

   
void Game::run(){
	string command;
    
  while(!isWon) {
    next();

    while(!isWon) {
      cin >> command;
      if (command == "roll" || command == "Roll") {

        if (rolled == true) { // if the player has already roll the dice 
          cout << ">> You cannot roll the dice anymore in this turn." << endl;   
        } else {  // player has not rolled
          int dice_result = diceroll();
          roll_time += 1;

          if(dicepair() == true) {
            if(roll_time == 3) {  // after 3 rolls, player is sent to DC tims line and cannot move
              cout << ">> You have rolled 3 doubles. Go to DC Tims Line! " << endl;
              int old_pos = player[currentplayer]->getPos();
              player[currentplayer]->setPos(10);
              player[currentplayer]->setDCTurn(0);
              td->notify(player[currentplayer], old_pos);
              td->display();
              displayCommands();
              rolled = true;
              if (player[currentplayer]->isBankrupt()) break;
            } else if (player[currentplayer]->getDCTurn() >= 0) {
              cout << ">> Congratulations, you rolled a double. Escape the DC Tims Line!" << endl;
              move(dice_result);
              rolled = true;
              if (player[currentplayer]->isBankrupt()) break;
            } else {
              move(dice_result);
              if (player[currentplayer]->getDCTurn() != 0) {
                cout << ">> You rolled a double, please roll again." << endl;
              }
              if (player[currentplayer]->isBankrupt()) break;
            }    
          } else { // roll a nondouble dice 
            if (player[currentplayer]->getDCTurn() == -1) {
              move(dice_result);
              displayCommands();
              rolled = true;
              if (player[currentplayer]->isBankrupt()) break;
            } else if (player[currentplayer]->getDCTurn() == 2) {
              player[currentplayer]->setDCTurn(3);
              cout << ">> You did not roll a double. Please pay or redeem now to leave the DC Tims Line." << endl;
              if (player[currentplayer]->getNumTimsCups() == 0 && player[currentplayer]->getBalance() < 50) {
                forceBankruptcy(player[currentplayer], 50, nullptr);
                if (player[currentplayer]->isBankrupt()) break;
              } else {
                displayCommands();
              }
            } else {
              player[currentplayer]->setDCTurn(player[currentplayer]->getDCTurn()+1);
              cout << ">> You did not roll a double. Stay in DC Tims Line." << endl;
              rolled = true;
              if (player[currentplayer]->isBankrupt()) break;
            }
          }
        }

      } else if (command == "brothers") {
        string property;
        cin >> property;

        int propertyIndex = getAcademicIndex(property);
        if (propertyIndex >= 0) {
          int i = isMonopolized(gameboard[propertyIndex]);
          if (test) cout << ">> Monopolized code: " << i << endl;
        }

      } else if( command == "trade" || command == "Trade") {

        cout << ">> You will do a trade" << endl;
        trade();

      } else if( command == "improve" || command == "Improve") {

        string property;
        cin >> property;

        int propertyIndex = getAcademicIndex(property);
        if (propertyIndex >= 0) {
          Academic *ap = static_cast<Academic *>(gameboard[propertyIndex]);
          string buySell;
          cin >> buySell;

          if (buySell == "buy" || buySell == "Buy") buyImprovement(ap, player[currentplayer]);
          else if (buySell == "sell" || buySell == "Sell") sellImprovement(ap, player[currentplayer]);
        }
      } else if(command == "mortgage" || command == "Mortgage") {

        string mortgageProperty;
        cin >> mortgageProperty;
        int buildingIndex = getBuildingIndex(mortgageProperty);
        
        if (buildingIndex >= 0) {
          Building *bp = static_cast<Building *>(gameboard[buildingIndex]);
          mortgageBuilding(bp, player[currentplayer]);
        }

      } else if(command == "unmortgage" || command == "Unmortgage") {

        string unmortgageProperty;
        cin >> unmortgageProperty;
        int buildingIndex = getBuildingIndex(unmortgageProperty);
        if (buildingIndex >= 0) {
          Building *bp = static_cast<Building *>(gameboard[buildingIndex]);
          unmortgageBuilding(bp, player[currentplayer]);
        } 

      } else if(command == "assets" || command == "Assets") {

        displayAssets(player[currentplayer]); 
        displayCommands();

      } else if(command == "all" || command == "All") {

        displayAllAssets();
        displayCommands();

      } else if(command == "save" || command == "Save") {

        string saveFile;
        cin >> saveFile;
        saveGame(saveFile);
        cout << ">> Successfully saved in "<< saveFile << "!" << endl;
 
      } else if(command == "next" || command == "Next") {

        if (rolled == false){
          cout << ">> You have not rolled, please roll to complete your turn." << endl;
        } else if (player[currentplayer]->getDCTurn() >= 3) {
          cout << ">> You must pay or redeem to leave DC Tims Line and complete your turn." << endl;
        } else {
          cout << ">> Turn complete." << endl;  
          
          //find next player 
          do { 
            currentplayer = (currentplayer + 1) % 8;
          }        
          while (player[currentplayer] == nullptr);

          next();
        }

      } else if ((command == "pay" || command == "Pay") && player[currentplayer]->getDCTurn() >= 0) {
        if (player[currentplayer]->getBalance() >= 50) {
          player[currentplayer]->updateBalance(-50);
          player[currentplayer]->setDCTurn(-1);
          cout << ">> Thank you for paying. Your new balance is $" << player[currentplayer]->getBalance() << "." << endl;
          displayCommands();
        } else {
          cout << ">> You do not have enough funds to leave DC Tims Line." << endl;
          displayCommands();
        }
      } else if ((command == "redeem" || command == "Redeem") && player[currentplayer]->getDCTurn() >= 0) {
        int timsCups = player[currentplayer]->getNumTimsCups();
        if (timsCups >= 1) {
          player[currentplayer]->setNumTimsCups(timsCups-1);
          player[currentplayer]->setDCTurn(-1);
          rimcup--;
          displayCommands();
        } else {
          cout << ">> You do not have a Roll Up The Rim cup to leave DC Tims Line." << endl;
          displayCommands();
        }
      } else if(command == "exit" || command == "Exit" || command == "quit" || command == "Quit") {

        cout << ">> You will exit the game now." << endl;
        return;
      }
    }
  }
}

void Game::next(){
  if (player[currentplayer]->isBankrupt()) {
    delete player[currentplayer];
    player[currentplayer] = nullptr;

    //find next player 
    do { 
      currentplayer = (currentplayer + 1) % 8;
    }        
    while (player[currentplayer] == nullptr);

    numplayer -= 1;
  }

  for (int i = 0 ; i < 8; i++) {
    if(player[i] != nullptr){
      int pos = player[i]->getPos();
      td->notify(player[i],pos);
    }   
  }

  td->display();

  cout << ">> Hello! It is " << player[currentplayer]->getName() << "'s turn!" << endl;
  displayCommands();
  
  rolled = false;
  roll_time = 0;
}

void Game::displayCommands() {
   if (!isWon) {
     int currentplayerDCTurn = player[currentplayer]->getDCTurn();
     if (currentplayerDCTurn >= 0 && currentplayerDCTurn <= 2) {
       cout << endl;
       cout << ">> You are stuck in DC Tims Line (Turn " << currentplayerDCTurn;
       cout << "), please choose from the following commands:" << endl;
       cout << ">> 1. roll: roll two dice, and move your piece the sum of those dice if you get doubles." << endl;
       cout << ">> 2. next: give control to the next player. " << endl;
       cout << ">> 3. trade <player> <give> <receive>: offers to trade property/cash with another player." << endl;
       cout << ">> 4. improve <property> buy/sell: attempts to buy or sell an improvement for property." << endl;
       cout << ">> 5. mortgage <property>: attempts to mortgage property." << endl;
       cout << ">> 6. unmortgage <property>: attempts to unmortgage property." << endl;
       cout << ">> 7. assets: displays the assets of the current player." << endl;
       cout << ">> 8. all: displays the assets of every player." << endl;
       cout << ">> 9. save <filename>: saves the current state of the game to the given file." << endl;
       cout << ">> 10. pay: pay $50 to leave DC Tims Line." << endl;
       cout << ">> 11. redeem: redeem Roll Up The Rim to leave DC Tims Line." << endl;
     } else if (currentplayerDCTurn >= 3) {
       cout << ">> 1. pay: pay $50 to leave DC Tims Line." << endl;
       cout << ">> 2. redeem: redeem Roll Up The Rim to leave DC Tims Line." << endl;
     } else {
       cout << endl;
       cout << ">> Please choose from the following commands:" << endl;
       cout << ">> 1. roll: roll two dice, and move your piece the sum of those dice." << endl;
       cout << ">> 2. next: give control to the next player. " << endl;
       cout << ">> 3. trade <player> <give> <receive>: offers to trade property/cash with another player." << endl;
       cout << ">> 4. improve <property> buy/sell: attempts to buy or sell an improvement for property." << endl;
       cout << ">> 5. mortgage <property>: attempts to mortgage property." << endl;
       cout << ">> 6. unmortgage <property>: attempts to unmortgage property." << endl;
       cout << ">> 7. assets: displays the assets of the current player." << endl;
       cout << ">> 8. all: displays the assets of every player." << endl;
       cout << ">> 9. save <filename>: saves the current state of the game to the given file." << endl;
     }
   }
 }


void Game::askToBuy(Building *building, Player *buyer ) {
  if(buyer->getBalance() < building->getCost()){
    cout << ">> Sorry you don't have enough money to buy this building. " << "Your current balance is " << buyer->getBalance();
    cout << ">> This building costs " << building->getCost() << "." << endl;
    // cout << "Auctions will begin" << endl;
    auctionProperty(building);
    return;
  }
   
  cout << ">> Do you want to buy " << building->getName() << " for $" << building->getCost() << "? ";
  cout << "[yes/no/assets]" << endl;

  string temp_askbuy;
  while( cin >> temp_askbuy ){
    if(temp_askbuy == "yes" || temp_askbuy == "Yes"){
      building->setOwner(buyer);
      buyer->updateBalance( -1 * building->getCost() );
      td->notify(building);
      td->display();
      if(test) cout << ">> Test display" << endl;
      cout << ">> You have purchesd " << building->getName() << endl;
      break;
    } else if (temp_askbuy == "no" || temp_askbuy == "No"){
      // cout << "Auctions will begin" << endl;
      auctionProperty(building);
      break;
    } else if( temp_askbuy == "assets" || temp_askbuy == "Assets"){
      displayAssets(buyer);
    } else{
      cout << ">> Invalid command, please input [yes/no/assets]. " << endl;
    }
  }
}

void Game::trade() {
    string temp_trader;
    string give;
    string receive;
    int givenumber = 0;
    int receivenumber = 0;
    bool givemoney = false;
    bool receivemoney = false;

    cin >> temp_trader;
    cin >> give;
    cin >> receive;
    
    istringstream give_s(give);
    if(give_s >> givenumber){
     givemoney = true;    
    }
    
    istringstream receive_s(receive);
    if(receive_s >> receivenumber){
     receivemoney = true;    
    }
      
      int trade_give_building_index = getBuildingIndex(give);
    if(givemoney == false){
       trade_give_building_index = getBuildingIndex(give);
    }

      int trade_receive_building_index = -1;
    if(receivemoney == false){
       trade_receive_building_index = getBuildingIndex(receive);
    }

    int trader_index = getplayer(temp_trader);
    if (trader_index == -1){
      cout << ">> Sorry, the player you want to trade is not exist." << endl;
      return;
    }else if ( player[trader_index]->getName() == player[currentplayer]->getName()){
      cout << ">> You cannot trade with yourself." << endl;
      return;
    }else if ( givemoney && receivemoney){
      cout << ">> You can not trade money for money!" << endl;
      return;
    }
    
    //give money want to buy building
    else if ( (givemoney== true )  && (receivemoney == false) ){
      if(givenumber > player[currentplayer]->getBalance()){
        cout << ">> You do not have enough money!" << endl;
        return;
      }

      else if( trade_receive_building_index == -1){
        cout << ">> The building you want to trade is not exist!" << endl;
        return;
      }
      else {
        Building *bp = dynamic_cast<Building *>(gameboard[trade_receive_building_index]);
        if(bp->getOwner() == nullptr){
          cout << ">> The person you want to trade does not own this building!" << endl;
          return;
        }
        else if(bp->getOwner()->getName() != temp_trader){
          cout << ">> The person you want to trade does not own this building!" << endl;
          return;
        }
        else if(isMonopolized(bp) == 3){
          cout << ">> The building cannot be traded since there is improvement in its monopoly!" << endl;
          return;
        }
        else {
          cout << ">> " << player[trader_index]->getName() << ", you can choose to trade or not" << endl;
          cout << ">> " << player[currentplayer]->getName() <<  " wants to spend " << give << " to buy your " << bp->getName() << endl;
          cout << ">> You can [accept]/[reject]/[assets]" << endl;
          string command;
          while(cin >> command){
            if(command == "reject"){
              cout << ">> Trade is rejected" << endl;
              return;
            }
            else if(command == "assets"){
             displayAssets(player[trader_index]);
           }
           else if(command == "accept"){
             player[currentplayer]->updateBalance(-1 * givenumber);
             player[trader_index]->updateBalance(givenumber);
             bp->setOwner(player[currentplayer]);
             td->notify(bp);
             td->display();
             cout << ">> Trade successfully!" << endl;
             cout << ">> " << player[currentplayer]->getName() << " spend " << givenumber << " to get " << bp->getName() << endl;
             return;
           }
           else{
            cout << ">> Invalid input! Please input [accept]/[reject]/[assets]" << endl;
           }
        }
      }

    }
  }
  
  //give building want to get money
  else if( (givemoney== false )  && (receivemoney == true) ){
      if(receivenumber > player[trader_index]->getBalance()){
        cout << ">> The player you want to trade do not have enough money!" << endl;
        return;
      }     

      else if( trade_give_building_index == -1){
        cout << ">> The building you want to trade is not exist!" << endl;
        return;
      }
      else{
        Building *bp = dynamic_cast<Building *>(gameboard[trade_give_building_index]);
        if(bp->getOwner() == nullptr){
          cout << ">> You do not own this building!" << endl;
          return;
        }
        else if(bp->getOwner()->getName() != player[currentplayer]->getName()){
          cout << ">> You do not own this building!" << endl;
          return;
        }
        else if(isMonopolized(bp) == 3){
          cout << ">> The building cannot be traded since there is improvement in its monopoly!" << endl;
          return;
        }
        else{
          cout << ">> " << player[trader_index]->getName() << ", you can choose to trade or not" << endl;
          cout << ">> " << player[currentplayer]->getName() <<  " wants to trade " << give << " for" << receivenumber << endl;
          cout << ">> You can [accept]/[reject]/[assets]" << endl;
          string command;
          while(cin >> command){
            if(command == "reject"){
              cout << ">> Trade is rejected" << endl;
              return;
            }
            else if(command == "assets"){
             displayAssets(player[trader_index]);
           }
           else if(command == "accept"){
             
             player[currentplayer]->updateBalance( receivenumber);
             player[trader_index]->updateBalance(-1 *receivenumber);
             bp->setOwner(player[trader_index]);
             td->notify(bp);
             td->display();
             cout << ">> Trade successfully!" << endl;
             cout << ">> " << player[currentplayer] << "trade " << bp->getName() << " for " << receivenumber  << endl;
             return;
           }
           else{
            cout << ">> Invalid input! Please input [accept]/[reject]/[assets]" << endl;
           }
        }
      }
      }
      }
      else if((givemoney == false)&& (receivemoney == false)){
          if( trade_give_building_index == -1){
          cout << ">> The building you want to trade is not exist!" << endl;
           return;
          }
          else if( trade_receive_building_index == -1){
          cout << ">> The building you want to trade is not exist!" << endl;
           return;
          }

          else{
           Building *bp_give = dynamic_cast<Building *>(gameboard[trade_give_building_index]);
           Building *bp_receive = dynamic_cast<Building *>(gameboard[trade_receive_building_index]);
           if(bp_give->getOwner() == nullptr){
            cout << ">> You do not own this building!" << endl;
            return;
           }
           else if(bp_receive->getOwner() == nullptr){
            cout << ">> The player you want to trade do not own this building!" << endl;
            return;
           }
           else if(bp_give->getOwner()->getName() != player[currentplayer]->getName()){
            cout << ">> You do not own this building!" << endl;
           }
           else if(bp_receive->getOwner()->getName()!= player[trader_index]->getName()){
            cout << ">> The player you want to trade do not own this building!" << endl;
            return;
           }
           else if(isMonopolized(bp_give) == 3){
            cout << ">> The building cannot be traded since there is improvement in its monopoly!" << endl;
           return;
           }
           else if(isMonopolized(bp_receive) == 3){
            cout << ">> The building cannot be traded since there is improvement in its monopoly!" << endl;
           return;
           }  
           else{
          cout << ">> " << player[trader_index]->getName() << ", you can choose to trade or not" << endl;
          cout << ">> " << player[currentplayer]->getName() <<  " wants to trade " << bp_give->getName() << " for" << bp_receive->getName() << endl;
          cout << ">> You can [accept]/[reject]/[assets]" << endl;
            string command;
            while(cin >> command){
            if(command == "reject"){
              cout << ">> Trade is rejected" << endl;
              return;
            }
            else if(command == "assets"){
             displayAssets(player[trader_index]);
           }
           else if(command == "accept"){             
            bp_give->setOwner(player[trader_index]);
            bp_receive->setOwner(player[currentplayer]);
            td->notify(bp_give);
            td->notify(bp_receive);
            td->display();
            cout << ">> Trade successfully!" << endl;
            cout << ">> " << player[currentplayer]->getName() << "trade " << bp_give->getName() << " for " << bp_receive->getName() << endl;
            return;
           }
           else{
            cout << ">> Invalid input! Please input [accept]/[reject]/[assets]" << endl;
           }
        }            
      }
    }
  }
}

  
//get index of player
int Game::getplayer(string name){
  for(int i = 0; i < numplayer; i ++){
    if(player[i]->getName() == name){
      return i;
    }  
  }
  return -1;
}


int Game::getsumdice(){
  return firstdice+seconddice;
}



bool Game::dicepair(){
  if(firstdice  != seconddice ){
  	return false;
  }
  else{
  	return true;
  }   
}

void Game::move(int move_blocks){
  int old_pos = player[currentplayer]->getPos();
  int current_pos =  player[currentplayer]->getPos() + move_blocks;

  if(current_pos > 39){
    current_pos -= 40;
    cout << ">> You pass OSAP and get 200$!" << endl;
    player[currentplayer]->updateBalance(200);
  }
 
  if(test) cout << ">> Player moved from " << player[currentplayer]->getPos();
  player[currentplayer]->setPos(current_pos);
  td->notify(player[currentplayer],old_pos);
  if(test) cout << " to " << player[currentplayer]->getPos() << "." << endl;

  td->display();
  gameboard[current_pos]->notify(player[currentplayer]);

  if (current_pos == 30) {
    td->notify(player[currentplayer], 30);
    td->display();
    rolled = true;
    displayCommands();
  }
}



void Game::settest(){
  test = true;
}


void Game::displayAssets(Player *player){
  cout << ">> Cash Balance: " << player->getBalance() << endl;
  cout << ">> Tims Cups: "  << player->getNumTimsCups() << endl;
  cout << ">> Properties(Name, Owner, Improvements): " << endl;
  for (int i = 0; i < 40; ++i) {
    Academic *ap = dynamic_cast<Academic *>(gameboard[i]);
    if (!ap) {
      Building *bp = dynamic_cast<Building *>(gameboard[i]);
      if (bp && bp->getOwner() == player) cout << ">> " << *bp;
    } else {
      if (ap->getOwner() == player) cout << ">> " << *ap;
    }
  }
}

void Game::displayAllAssets() {
  cout << "Total Tims Cups in circulation: " << rimcup << "." << endl;
  for (int i = 0; i < 8; ++i) {
    if (player[i]) {
      cout << ">> " << player[i]->getName() << endl;
      displayAssets(player[i]);
      cout << endl;
    }
  }
}


void Game::auctionProperty(Building *building){
  cout << ">> Auction for " << building->getName() << " start!" << endl;
  int playerLeft = numplayer;
  int highestPrice = 0;
  int current_auction_player;
  int highestPlayer;
  bool active[8];

  //In the begining of a auction, all the players are active
  for(int i = 0 ; i < 8 ;i ++){
    if(player[i] != nullptr){
      if (player[i]->isBankrupt()) {
        playerLeft -= 1;
        active[i] = false;
      } else {
        active[i] = true;
      }
    }
    else{
      active[i] = false;
    }
  }

  for (int i = 0; i < 8; ++i) {
    if (active[i]) {
      current_auction_player = i;
      highestPlayer = i;
      break;
    }
  }

  string command_auction;

  while(playerLeft != 1){

    do {
      current_auction_player = (current_auction_player + 1) % 8;
    } while (!active[current_auction_player]);

    if(test) cout << "auction 1 "  << current_auction_player << endl;
    cout << ">> It is " << player[current_auction_player]->getName() <<" 's turn. " ;
    cout << "The bid is " << highestPrice <<"$ right now by " << player[highestPlayer]->getName() << endl;
    cout << ">> You can do [bid money]/[withdraw]/[assets]" << endl;

    if(test) cout << ">> auction 2" << endl;

    while(true){
      cin >> command_auction;
      int auction_number;

      if(command_auction == "bid"){
        cin >> auction_number;
        if(auction_number <= highestPrice){
          cout << ">> Sorry, you should bid more than the current price, which is "  << highestPrice << endl;
        } else if (auction_number > player[current_auction_player]->getBalance() ){
          cout << ">> Sorry, you don't have such money" << endl;
        } else if(auction_number > highestPrice){
          highestPrice = auction_number;
          highestPlayer = current_auction_player;
          cout << ">> Bid successfully, current bid price is " << highestPrice << endl;
          break;
        } else{
          cout << ">> Reached end of condition" << endl;
        }
      } else if(command_auction == "assets"){
        displayAssets(player[current_auction_player]);
      } else if(command_auction == "withdraw"){
        playerLeft -= 1;
        active[current_auction_player] = false;
        cout << ">> You withdraw this auction, " << "number of current candidates are " << playerLeft << endl;
        break;
      } else{ 
        cout << ">> invaild commands, please input [bid money]/[withdraw]/[assets]" << endl;
      }
    }
  }

  player[highestPlayer]->updateBalance(-1 * highestPrice);
  building->setOwner(player[highestPlayer]);
  td->notify(building);
  td->display();

  cout << ">> Auction is end, " << building->getName() << " is bought by";
  cout << player[highestPlayer]->getName() << " by " << highestPrice << " $. " << endl;
}



int Game::diceroll(){
  string n;
  srand(time(0));
  if (test == false) {
    firstdice = 1+rand()%6;
    seconddice = 1+rand()%6;
  } else {
    cout << ">> Testing mode: Please enter two numbers between 1 and 6 (inclusive)." << endl;
    cin >> firstdice >> seconddice;
  }
  int sum = firstdice + seconddice;

  cout << ">> First dice rolled: " << firstdice << ", Second dice rolled: " << seconddice << ". ";
  cout << "Sum: " << sum << "." << endl;

  return sum;
}

int Game::isMonopolized(const Square *square ) const {
    // return 0 if not all properties owned by same player (can't improve, can mortgage, can trade)
    // return 1 if all properties owned by same player, but at least one is mortgaged (can't improve, can mortgage, can trade)
    // return 2 if all properties owned, no improvements, no mortgages (can improve, can mortgage, DOUBLE rent, can trade)
    // return 3 if all properties owned, one property has improvements (can improve, can't mortgage, cannot trade)
    int academicIndex = getAcademicIndex(square->getName());
    if (academicIndex == -1) return -1;
    const Academic *academic = static_cast<const Academic *>(square);
    // Player *owner = academic->getOwner();
    string monoBlock = academic->getMonoBlock();

    vector<Academic *> brothers;
    for (int i = 0; i < 40; ++i) {
      Academic *ap = dynamic_cast<Academic *>(gameboard[i]);
      if (ap) {   // bp is null if gameboard[i] is not Building
        if (ap->getMonoBlock() == monoBlock) {
          brothers.emplace_back(ap);
        }
      }
    }

    for (auto it = brothers.begin(); it != brothers.end(); ++it) {
      if (academic->getOwner() != (*it)->getOwner()) return 0;
    }

    for (auto it = brothers.begin(); it != brothers.end(); ++it) {
      if ((*it)->getImpLevel() == -1) return 1;
    }

    for (auto it = brothers.begin(); it != brothers.end(); ++it) {
      if ((*it)->getImpLevel() > 0) return 3;
    }

    return 2;
}

void Game::chooseTuition(Player *landedPlayer) {
  int playerWorth = 0;
  playerWorth += landedPlayer->getBalance();
  for (int i = 0; i < 40; ++i) {
    Building *bp = dynamic_cast<Building *>(gameboard[i]);
    if (bp) {   // bp is null if gameboard[i] is not building
      if (bp->getOwner() == landedPlayer) {
        if (bp->getImpLevel() == -1 || bp->getImpLevel() == 0) {
          playerWorth += bp->getCost();
        } else {
          playerWorth += bp->getValue();
        }
      }
    }
  }
  cout << ">> Please choose between paying $300 or 10 percent of your total worth." << endl;
  cout << ">> 1. Fixed: Pay $300." << endl;
  cout << ">> 2. Percent: Pay 10 percent of your total worth." << endl;
  if (test) cout << "Total worth is $" << playerWorth << "." << endl;
  int percent = playerWorth / 10;
  while (true) {
    string command;
    cin >> command;
    if (command == "fixed" || command == "Fixed") {
      if (landedPlayer->getBalance() < 300) {
        cout << ">> You do not have enough funds to pay the $300 fee." << endl;
        forceBankruptcy(landedPlayer, 300, nullptr);
        break;
      } else {
        landedPlayer->updateBalance(-300);
        cout << ">> Thank you for paying $300 tuition." << endl;
        break;
      }
    } else if (command == "percent" || command == "Percent") {
      if (landedPlayer->getBalance() < percent) {
        cout << ">> You do not have enough funds to pay 10 percent of your worth." << endl;
        forceBankruptcy(landedPlayer, percent, nullptr);
        break;
      } else {
        landedPlayer->updateBalance(percent);
        cout << ">> Thank you for paying " << playerWorth/10 << "." << endl;
        break;
      }
    }
  }

}

void Game::buyImprovement(Square *square, Player *player) {
    int academicIndex = getAcademicIndex(square->getName());
    if (academicIndex == -1) return;
    Academic *academic = static_cast<Academic *>(square);
    Player *owner = academic->getOwner();
    if (player != owner) {
        cout << ">> You do not own this property." << endl;
        return;
    }
    if (isMonopolized(academic) == 0) {
        cout << ">> You can only improve properties on which you own a monopoly." << endl;
        return;
    }
    if (isMonopolized(academic) == 1) {
        cout << ">> You may not improve a property which a mortgaged property in its block." << endl;
        return;
    }

    int ownerBalance = owner->getBalance();
    int impCost = academic->getImpCost();
    if (ownerBalance < impCost) {
        cout << ">> You do not have enough funds to improve this property." << endl;
        return;
    }
    int impLevel = academic->getImpLevel();
    if (impLevel == 5) {
        cout << ">> This property cannot be improved further." << endl;
        return;
    }
    academic->setImpLevel(impLevel+1);
    owner->updateBalance(impCost * -1);
    td->notify(academic);

    if(test) cout << ">> test  " << academic->getImpLevel() << endl;
    td->display();
    cout << ">> " << academic->getName() << " now has " << academic->getImpLevel() << " improvements. ";
    cout << "Your balance decreased to " << player->getBalance() << "." << endl;
    displayCommands();
}


void Game::sellImprovement(Square *square, Player *player) {
    int academicIndex = getAcademicIndex(square->getName());
    if (academicIndex == -1) return;
    Academic *academic = static_cast<Academic *>(square);
    Player *owner = academic->getOwner();
    if (player != owner) {
        cout << ">> You do not own this property." << endl;
        return;
    }
    int impCost = academic->getImpCost();
    int impLevel = academic->getImpLevel();
    if (impLevel == 0) {
        cout << ">> This property has no improvements." << endl;
        return;
    }
    if (impLevel == -1) {
        cout << ">> This property is mortgaged, and has no improvements." << endl;
        return;
    }
    academic->setImpLevel(impLevel-1);
    owner->updateBalance(impCost/2);
    td->notify(academic);
    td->display();
    cout << ">> " << academic->getName() << " now has " << academic->getImpLevel() << " improvements. ";
    cout << "Your balance increased to " << player->getBalance() << "." << endl;
    displayCommands();
}

void Game::mortgageBuilding(Square *square, Player *player) {
    int buildingIndex = getBuildingIndex(square->getName());
    if (buildingIndex == -1) return;
    Building *building = static_cast<Building *>(square);
    Player *owner = building->getOwner();
    if (player != owner) {
        cout << ">> You do not own this property." << endl;
        return;
    }
    if (isMonopolized(building) == 3) {
        cout << ">> You may not mortgage a building which has an improved building in its block." << endl;
        return;
    }
    if (building->getImpLevel() == -1) {
        cout << ">> This property is already mortgaged." << endl;
        return;
    }
    int mortgageValue = building->getCost() / 2;
    owner->updateBalance(mortgageValue);
    building->setImpLevel(-1);
    td->notify(building);
    cout << ">> " << building->getName() << " has been mortgaged. ";
    cout << "Your balance increased to " << player->getBalance() << "." << endl;
}

void Game::unmortgageBuilding(Square *square, Player *player) {
    int buildingIndex = getBuildingIndex(square->getName());
    if (buildingIndex == -1) return;
    Building *building = static_cast<Building *>(square);
    Player *owner = building->getOwner();
    if (player != owner) {
        cout << ">> You do not own this property." << endl;
        return;
    }
    if (building->getImpLevel() != -1) {
        cout << ">> This property is not mortgaged." << endl;
        return;
    }
    int unmortgageCost = building->getCost() * 6 / 10;
    int ownerBalance = owner->getBalance();
    if (ownerBalance < unmortgageCost) {
        cout << ">> You do not have enough funds to unmortgage this property." << endl;
        return;
    }
    owner->updateBalance(unmortgageCost * -1);
    building->setImpLevel(0);
    td->notify(building);
    cout << ">> " << building->getName() << " has been unmortgaged. ";
    cout << ">> Your balance decreased to " << player->getBalance() << "." << endl;
}

void Game::forceBankruptcy(Player *landedPlayer, int fee, Player *ownerPlayer) {
  int playerBalance = landedPlayer->getBalance();
  if (ownerPlayer) {
    cout << ">> You owe " << ownerPlayer->getName() << " $" << fee << ". " ;
    cout << "You only have $" << playerBalance << ". " << endl;
  } else {
    cout << ">> You owe the Bank $" << fee << ". " ;
    cout << "You only have $" << playerBalance << ". " << endl;
  }

  while (fee > landedPlayer->getBalance()) {
    int bankruptcyValue = 0;
    for (int i = 0; i < 40; ++i) {
      Building *bp = dynamic_cast<Building *>(gameboard[i]);
      if (bp) {   // bp is null if gameboard[i] is not building
        if (bp->getOwner() == landedPlayer) {
          bankruptcyValue += bp->getValue() / 2;
        }
      }
    }
    bankruptcyValue += landedPlayer->getBalance();

    if (bankruptcyValue < fee) {
      if (test) cout << ">> BankruptcyValue: " << bankruptcyValue << endl;
      if (test) cout << ">> Fee: " << fee << endl;
      cout << ">> 1. improve <property> buy/sell: attempts to buy or sell an improvement for property." << endl;
      cout << ">> 2. mortgage <property>: attempts to mortgage property." << endl;
      cout << ">> 3. assets: displays the assets of the current player." << endl;
      cout << ">> 4. all: displays the assets of every player." << endl;
      cout << ">> 5. bankrupt: player declares bankruptcy." << endl;
    } else {
      cout << ">> 1. improve <property> buy/sell: attempts to buy or sell an improvement for property." << endl;
      cout << ">> 2. mortgage <property>: attempts to mortgage property." << endl;
      cout << ">> 3. assets: displays the assets of the current player." << endl;
      cout << ">> 4. all: displays the assets of every player." << endl;
    }

    string command;
    cin >> command;

    if (command == "improve" || command == "Improve") {
      string property;
      cin >> property;
      int propertyIndex = getAcademicIndex(property);

      if (propertyIndex >= 0) {
        Academic *ap = static_cast<Academic *>(gameboard[propertyIndex]);
        string buySell;
        cin >> buySell;

        if (buySell == "buy" || buySell == "Buy") buyImprovement(ap, landedPlayer);
        else if (buySell == "sell" || buySell == "Sell") sellImprovement(ap, landedPlayer);
      }

    } else if (command == "mortgage" || command == "Mortgage") {
      string property;
      cin >> property;
      int propertyIndex = getBuildingIndex(property);

      if (propertyIndex >= 0) {
        Building *bp = static_cast<Building *>(gameboard[propertyIndex]);
        mortgageBuilding(bp, landedPlayer);
      }
    } else if (command == "assets" || command == "Assets") {
      displayAssets(landedPlayer);
    } else if (command == "all" || command == "All") {
      displayAllAssets();
    } else if ((command == "bankrupt" || command == "Bankrupt") && (bankruptcyValue < fee)) {
      if (ownerPlayer) declareBankruptcy(landedPlayer, ownerPlayer);
      else declareBankruptcy(landedPlayer, nullptr);
      return;
    }
  }

  cout << ">> You now have enough funds to pay your debt." << endl;
  landedPlayer->updateBalance(fee * -1);
  if (ownerPlayer) {
    ownerPlayer->updateBalance(fee);
  }
  cout << ">> Your new balance is " << landedPlayer->getBalance() << "." << endl;
}

void Game::declareBankruptcy(Player *landedPlayer, Player *ownerPlayer) {
  td->removePlayer(landedPlayer);
  td->display();
  landedPlayer->setBankrupt();

  if (numplayer == 2) { // game over
    if (ownerPlayer) {
      cout << ">> " << ownerPlayer->getName() << " has won the game. " << endl;
      isWon = true;
      return;
    } else {
      while (player[currentplayer] == nullptr) {
        currentplayer = (currentplayer + 1) % 8;
      }
      cout << ">> " << player[currentplayer]->getName() << " has won the game." << endl;
      isWon = true;
      return;
    }
  }

  if (ownerPlayer) {
    ownerPlayer->updateBalance(landedPlayer->getBalance());
    int ownerTimsCups = ownerPlayer->getNumTimsCups();
    int landedTimsCup = landedPlayer->getNumTimsCups();
    ownerPlayer->setNumTimsCups(ownerTimsCups+landedTimsCup);
  } else {
    rimcup -= landedPlayer->getNumTimsCups();
  }

  for (int i = 0; i < 40; ++i) {
    Building *bp = dynamic_cast<Building *>(gameboard[i]);
    if (bp) {
      if (bp->getOwner() == landedPlayer) {
        if (ownerPlayer) { 
          bp->setOwner(ownerPlayer);
          if (bp->getImpLevel() == -1) {
            string command;
            while (true) {
              cout << ">> Would you like to unmortgage " << bp->getName() << "? [yes/no]" << endl;
              cin >> command;
              if (command == "yes" || command == "Yes") {
                int unmortgageCost = bp->getCost() / 10 * 6;
                if (ownerPlayer->getBalance() >= unmortgageCost) {
                  unmortgageBuilding(bp, ownerPlayer);
                  break;
                } else {
                  cout << ">> You do not have enough funds to unmortgage this property." << endl;
                }
              } else if (command == "no" || command == "No") {
                int mortgageTransferCost = bp->getCost() / 10;
                if (ownerPlayer->getBalance() >= mortgageTransferCost) {
                  ownerPlayer->updateBalance(mortgageTransferCost * -1);
                  break;
                } else {
                  forceBankruptcy(ownerPlayer, mortgageTransferCost, nullptr);
                  break;
                }
              }
            }
          }
        } else {
          if (bp->getImpLevel() == -1) bp->setImpLevel(0);
          auctionProperty(bp);
        }
      }
    }
  }
}


int Game::getAcademicIndex(string square) const {
  for (int i = 0; i < 40; ++i) {
    Academic *ap = dynamic_cast<Academic *>(gameboard[i]);
    if (ap) {   // ap is null if gameboard[i] is not Academic
      if (ap->getName() == square) {
        return ap->getIndex();
      }
    }
  }

  cout << ">> This is not an Academic square." << endl;
  return -1;
}

int Game::getBuildingIndex(string square) const {
  for (int i = 0; i < 40; ++i) {
    Building *bp = dynamic_cast<Building *>(gameboard[i]);
    if (bp) {   // bp is null if gameboard[i] is not Building
      if (bp->getName() == square) {
        return bp->getIndex();
      }
    }
  }
  cout << ">> This is not a Building square. " << endl;
  return -1;
}


bool Game::loadGame(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    myfile >> numplayer;

    for (int i = 0; i < numplayer; ++i) { // Read player data
      myfile >> playername[i];

      if (playername[i] == "BANK") {
        cout << ">> Cannot have player named BANK." << endl;
        return false;
      }

      myfile >> chosensymbol[i];
      int playerNumTimsCups;
      myfile >> playerNumTimsCups;
      rimcup += playerNumTimsCups;
      int playerBalance;
      myfile >> playerBalance;
      int playerPosition;
      myfile >> playerPosition;
      int isStuckDC = 0;
      int playerDCTurn = -1;

      if (playerPosition == 10) {
        myfile >> isStuckDC;
        if (isStuckDC == 1) {
          myfile >> playerDCTurn;
        }
      }

      player[i] = new Player(chosensymbol[i], playername[i], playerNumTimsCups, playerBalance, 
      playerPosition, playerDCTurn);
      if (test) cout << ">> Added Player " << player[i]->getName() << endl;
    }

    for (int i = 0; i < 28; ++i) {  // Read property data
      string propertyName;
      myfile >> propertyName;
      int propertyIndex = getBuildingIndex(propertyName);
      Building *bp = static_cast<Building *>(gameboard[propertyIndex]);
      string propertyOwner;
      myfile >> propertyOwner;

      if (propertyOwner != "BANK") {
        for (int i = 0; i < numplayer; ++i) {
          if (player[i]->getName() == propertyOwner) {
            bp->setOwner(player[i]);
          }
        }
      }

      int propertyImprovements;
      myfile >> propertyImprovements;
      bp->setImpLevel(propertyImprovements);
      if (test) cout << ">> Loaded Property " << bp->getName() << endl;
    }

    currentplayer = 0;
    myfile.close();

    for(int i = 0 ; i < 40 ; i++) {
      Building *bp = dynamic_cast<Building *>(gameboard[i]);
      if (bp) td->notify(bp);
    }
    
    // td->display();
    return true;
  } else {
    cout << ">> Unable to open file." << endl;
    return false;
  }

}

void Game::saveGame(string filename) {
  ofstream myfile;
  myfile.open(filename);
  myfile << numplayer << endl;

  for (int i = 0; i < 8; ++i) { // Print player data
    if (player[i]) {
      myfile << player[i]->getName() << " " << player[i]->getSymbol() << " " << player[i]->getNumTimsCups();
      myfile << " " << player[i]->getBalance() << " " << player[i] ->getPos();
      if (player[i]->getPos() == 10) {  // Player is on DCTims Square
        myfile << " ";
        if (player[i]->getDCTurn() != -1) {  // Player is stuck in DCTims line
          myfile << 1 << " " << player[i]->getDCTurn();
        } else {  // Just visiting
          myfile << 0 << " ";
        }
      }
      myfile << endl;
    }
  }
  for (int i = 0; i < 40; ++i) {  // Print square data
    Academic *ap = dynamic_cast<Academic *>(gameboard[i]);
    if (ap) {
      myfile << *ap;
    }
    else {
      Building *bp = dynamic_cast<Building *>(gameboard[i]);
      if (bp) {
        myfile << *bp;
      }
    }
  }
}

void Game::Needles(Player *landedPlayer){
  srand(time(0));
  int random;
  if(test) {
    cout << ">> You can set the result now [1-100]" << endl;
    cin >> random;
    }
    else{
      random = rand()%100 + 1;
    }
  
  if(random == 100){
    cout << ">> Instead of normal effect, you will get a Roll Up the Rim cup" << endl;
    if(rimcup == 4){
      cout << ">> Sorry, there is no more Roll Up the Rim cup right now, you will get other result" << endl;
      Needles(landedPlayer);
      return ;
    }
    else {
      int newimts = landedPlayer->getNumTimsCups();
      landedPlayer->setNumTimsCups(newimts+1) ;
      rimcup += 1;
      cout << ">> You get Roll Up the Rim cup, you have " << landedPlayer->getNumTimsCups() << " now." << endl;
    }
  }
  else {
    if(test) {
    cout << ">> You can set the result now [1-18]" << endl;
    cin >> random;
    }
   if(!test) {
    random = rand() % 18 + 1;
   }
    
    if(test) cout << ">> random numebr is " << random << endl;
    if(random <= 1){
      cout << ">> You lost 200$" << endl;
      if(landedPlayer->getBalance() < 200){
        forceBankruptcy(landedPlayer,200, nullptr);
      }
      else{
        landedPlayer->updateBalance(-1 * 200);
        cout << ">> You current balance is " << landedPlayer->getBalance() << endl;
      }
    }
    else if( random >= 2 && random <= 3){
      cout << ">> You lost 100$" << endl;
      if(landedPlayer->getBalance() < 100){
        forceBankruptcy(landedPlayer,100, nullptr);
      }
      else{
        landedPlayer->updateBalance(-1 * 100);
        cout << ">> You current balance is " << landedPlayer->getBalance() << endl;
      }
    }
    else if( random >= 4 && random <= 6){
      cout << ">> You lost 50$" << endl;
      if(landedPlayer->getBalance() < 50){
        forceBankruptcy(landedPlayer,50, nullptr);
      }
      else{
        landedPlayer->updateBalance(-1 * 50);
        cout << ">> You current balance is " << landedPlayer->getBalance() << endl;
      }
    }

    else if( random >= 7 && random <= 12){
      cout << ">> You get 25$" << endl;   
      landedPlayer->updateBalance(25);
      cout << ">> You current balance is " << landedPlayer->getBalance() << endl;      
    }
    else if( random >= 13 && random <= 15){
      cout << ">> You get 50$" << endl;   
      landedPlayer->updateBalance(50);
      cout << ">> You current balance is " << landedPlayer->getBalance() << endl;      
    }
    else if( random >= 16 && random <= 17){
      cout << ">> You get 100$" << endl;   
      landedPlayer->updateBalance(100);
      cout << ">> You current balance is " << landedPlayer->getBalance() << endl;      
    }
    else {
      cout << ">> You get 200$" << endl;   
      landedPlayer->updateBalance(200);
      cout << ">> You current balance is " << landedPlayer->getBalance() << endl;      
    }
  } 

}


void Game::SLC(Player*  landedPlayer){
  srand(time(0));
  int random;
  if(test) {
    cout << ">> You can set the result now [1-100]" << endl;
    cin >> random;
  } else {
      random = rand()%100 + 1;
  }

  if(random == 100){
    cout << ">> Instead of normal effect, you will get a Roll Up the Rim cup" << endl;
    if(rimcup == 4){
      cout << ">> Sorry, there is no more Roll Up the Rim cup right now, you will get other result" << endl;
      SLC(landedPlayer);
      return ;
    } else {
      int newimts = landedPlayer->getNumTimsCups();
      landedPlayer->setNumTimsCups(newimts+1) ;
      rimcup += 1;
      cout << ">> You get Roll Up the Rim cup, you have " << landedPlayer->getNumTimsCups() << " now." << endl;
    }
  } else {
     if (test) {
      cout << ">> You can set the result now [1-24]" << endl;
      cin >> random;
     } else {
     random = rand()%24 + 1;
     }
   if(random >= 1 && random <= 3){
   cout << ">> You go back 3" << endl;
   if(landedPlayer->getPos() == 2){
    move(37);
   }
   else{
    move(-3);
   }
   
   }
   else if(random >= 4 && random <= 7){
   cout << ">> You go back 2" << endl;
   move(-2);
   }
   else if(random >= 8 && random <= 11){
   cout << ">> You go back 1" << endl;
   move(-1);
   }
   else if(random >= 12 && random <= 14){
   cout << ">> You go forward 1" << endl;
   move(1);
 }
   else if(random >= 15 && random <= 18){
   cout << ">> You go forward 2" << endl;
   move(2);
   }
   else if(random >= 19 && random <= 22){
   cout << ">> You go forward 3" << endl;
   move(3);
  }
  else if(random == 23){
   cout << ">> You will go to OSAP" << endl;
   int old_pos = landedPlayer->getPos();
   landedPlayer->setPos(0);
   td->notify(landedPlayer,old_pos);
   td->display();
   gameboard[0]->notify(landedPlayer);
 }
   
  else {
    cout << ">> You will go to DC tims" << endl;
    int old_pos = landedPlayer->getPos();
    landedPlayer->setPos(10);
    landedPlayer->setDCTurn(0);
    td->notify(landedPlayer, old_pos);
    td->display();
  }
 }
}

int Game::getNumRes(Player *player){

   int result = 0;
   if(dynamic_cast<Building *>(gameboard[5])->getOwner() == player){
    if(dynamic_cast<Building *>(gameboard[5])->getImpLevel() != -1){
      result += 1;
    }
   }
   if(dynamic_cast<Building *>(gameboard[15])->getOwner() == player){
    if(dynamic_cast<Building *>(gameboard[15])->getImpLevel() != -1){
      result += 1;
    }
   }
   if(dynamic_cast<Building *>(gameboard[25])->getOwner() == player){
    if(dynamic_cast<Building *>(gameboard[25])->getImpLevel() != -1){
      result += 1;
    }
   }
   if(dynamic_cast<Building *>(gameboard[35])->getOwner() == player){
    if(dynamic_cast<Building *>(gameboard[35])->getImpLevel() != -1){
      result += 1;
    }
   }
   return result;
}

int Game::getNumGym(Player *player){
   int result = 0;
   if(dynamic_cast<Building *>(gameboard[12])->getOwner() == player){
    if(dynamic_cast<Building *>(gameboard[12])->getImpLevel() != -1){
      result += 1;
    }
   }
   if(dynamic_cast<Building *>(gameboard[28])->getOwner() == player){
    if(dynamic_cast<Building *>(gameboard[28])->getImpLevel() != -1){
      result += 1;
    }
   }
   return result;
}
