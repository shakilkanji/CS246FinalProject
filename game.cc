#include "game.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <fstream>
#include <sstream>


using namespace std;

Game::Game():numplayer(0),currentplayer(0),rimcup(4),sumofdice(0),
firstdice(0),seconddice(0),test(false),rolled(false),roll_time(0){
  td = new TextDisplay;

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
  gameboard[25] = new Residence(this, 25, "UWP", 200);
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

  cout << "Welcome to Watopoly!" << endl;
  cout << "Please enter the number of players in the game [2-8]:" << endl;

  int temp_num;

  while (cin >> temp_num) {
    if (temp_num <= 8 && temp_num >= 2) {
      numplayer = temp_num;
      break;
    } 
    else {
      cout << "Your input is out of range, please enter a number between 2 and 8 (inclusive) " << endl;
    }
  }

   
  //initial player's name
  for( int current = 0 ; current < numplayer ; current++ ){
    cout << endl;
    cout << "Hello, player" << current + 1 << "!" <<" Please input your name:" << endl;;
        
    string temp_name;
        

    while(cin >> temp_name){
      bool chosen = false;

      if( temp_name == "BANK"){
  	    cout << "Sorry, you cannot choose this name, please choose a different one." << endl;
  		  cin >> temp_name;
      }

      for(int i = 0 ; i <current ;i++ ){
        if(temp_name == playername[i]){
       	  chosen = true;
        }
      }

      if(chosen == true ){
      	cout << "Someone has already chosen this name, please change to another one." << endl;
      } else{
      	playername[current] = temp_name;
      	break;
      }
    }


    //initial player's character 
    cout << endl;
    cout << "Hello, " << playername[current] << "! please choose an character whcih represents you." << endl;
    cout << "You can choose from:" << endl;
    cout << "G (Goose) / B (GRT BUS) / D (Tim Hortons Doughnut) / P (Professor)" <<endl;
    cout << "S (Student) / $ (Money) / L (Laptop) / T (Pink tie)" << endl;

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
        	cout << "Someone has already chosen this character, please change to another one" << endl;
        } else {
        	chosensymbol[current] = temp_symbol;
    	    break;
        }
      } else {
      	cout << "Please enter a valid character. " << endl;
      }
    }
  }
      
  for(int i = 0 ; i < numplayer ; i++){
  player[i] = new Player(chosensymbol[i], playername[i],this);
  }

  for(int i = 0 ; i < numplayer ; i++){       
  cout << player[i]->getSymbol() << " " << player[i]->getName() << endl;
  }

}

   
void Game::run(){
	string command;
    
  while(!isWon) {
    next();

    while(cin >> command) {
      if (command == "roll" || command == "Roll") {

        if (rolled == true) { // if the player has already roll the dice 
          cout << "You cannot roll the dice anymore in this turn" << endl;   
        } else {  // player has not rolled
          int dice_result = diceroll();
          roll_time += 1;
          move(dice_result);

          if(dicepair() == true) {
            if(roll_time == 3) {  // after 3 rolls, player is sent to DC tims line and cannot move
              cout << "You have rolled 3 doubles. Go to DC Tims Line! " << endl;
              rolled = true;
            } else {
              cout << "You rolled a double, please roll again. " << endl;
            }    
          } else { // roll a nondouble dice 
            displayCommands();
            rolled = true;
          }
        }

      } else if( command == "trade" || command == "Trade") {

        cout << "you will do a trade" << endl;

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

      } else if(command == "bankrupt" || command == "Bankrupt") {
        cout << "you will do a bankrupt" << endl;  

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
        cout << "Successfully saved in "<< saveFile << " !" << endl;

      } else if(command == "next" || command == "Next") {

        if (rolled == false){
          cout << "You have not rolled, please roll to complete your turn." << endl;
        } else {
          cout << "Turn complete." << endl;  
          
          //find next player 
          do { 
            currentplayer = (currentplayer + 1) % 8;
          }        
          while (player[currentplayer] == nullptr);

          next();
        }

      } else if(command == "exit" || command == "Exit") {

        cout << "You will exit the game now." << endl;
        return;
      }
    }
  }
  cout << "Somebody has won!" << endl;
}

void Game::next(){
  if (test) cout << "Start next()" << endl;
  for (int i = 0 ; i < 8; i++) {
    if(player[i] != nullptr){
      int pos = player[i]->getPos();
      td->notify(player[i],pos);
    }   
  }

  td->display();

  cout << "Hello! it is " << player[currentplayer]->getName() << "'s turn!" << endl;
  displayCommands();
  
  rolled = false;
  roll_time = 0;
}

void Game::displayCommands() {
    cout << endl;
    cout << "Please choose from the following commands:" << endl;
    cout << "1. roll: roll two dice, and move your piece the sum of those dice." << endl;
    cout << "2. next: give control to the next player. " << endl;
    cout << "3. trade <player> <give> <receive>: offers to trade property/cash with another player." << endl;
    cout << "4. improve <property> buy/sell: attempts to buy or sell an improvement for property." << endl;
    cout << "5. mortgage <property>: attempts to mortgage property." << endl;
    cout << "6. unmortgage <property>: attempts to unmortgage property." << endl;
    cout << "7. assets: displays the assets of the current player." << endl;
    cout << "8. all: displays the assets of every player." << endl;
    cout << "9. save <filename>: saves the current state of the game to the given file." << endl;
}


void Game::askToBuy(Building *building, Player *buyer ) {
  if(buyer->getBalance() < building->getCost()){
    cout << "Sorry you don't have enough money to buy this building. " << "Your current balance is " << buyer->getBalance();
    cout << "This building costs " << building->getCost() << "." << endl;
    // cout << "Auctions will begin" << endl;
    auctionProperty(building);
  }
   
  cout << "Do you want to buy " << building->getName() << " for $" << building->getCost() << "? ";
  cout << "[yes/no/assets]" << endl;

  string temp_askbuy;
  while( cin >> temp_askbuy ){
    if(temp_askbuy == "yes" || temp_askbuy == "Yes"){
      building->setOwner(buyer);
      buyer->updateBalance( -1 * building->getCost() );
      td->notify(building);
      td->display();
      cout << "You have purchesd " << building->getName() << endl;
      break;
    } else if (temp_askbuy == "no" || temp_askbuy == "No"){
      // cout << "Auctions will begin" << endl;
      auctionProperty(building);
      break;
    } else if( temp_askbuy == "assets" || temp_askbuy == "Assets"){
      displayAssets(buyer);
    } else{
      cout << "Invalid command, please input [yes/no/assets]. " << endl;
    }
  }
}


// void Game::trade() {
//     string temp_trader;
//     string give;
//     string receive;
//     int givenumber = 0;
//     int receivenumber = 0;
//     bool givemoney = false;
//     bool receivemoney = false;

//     cin >> temp_trader;
//     cin >> give;
//     cin >> receive;
    
//     istringstream give_s(give)
//     if(give_s >> givenumber){
//      givemoney = true;    
//     }
    
//     istringstream receive_s(receive)
//     if(receive_s >> receivenumber){
//      receivemoney = true;    
//     }

//     int trader_index = getplayer(string temp_trader);
//     if

// }

// bool Game::checkmonoimprov(string building){
//     int current_index = getPropertyIndex(building);
//     Building *current_pointerbuilding = dynamic_cast<Building *>(gameboard[current_index]);
//     Academic *current_pointeracademic = dynamic_cast<Academic *>(current_pointerbuilding);
//     for( int i = 0 ; i < 40 ; i++) {
//        int index =  getPropertyIndex( gameboard[i]->getName());
//       if ( ( index  != -1 )||( index != 12 )||( index != 28 )||( index != 28 )||
//         ( index != 5 )||( index != 15 )||( index != 25 )||( index != 31 ) ) {
//        Building *pointerbuilding = dynamic_cast<Building *>(gameboard[index]);
//        Academic *pointeracademic = dynamic_cast<Academic *>(pointerbuilding);
//        if(pointeracademic->getMonoBlock() == current_pointeracademic->getMonoBlock()) {
//          if(pointeracademic->getImpLevel() != 0 ){
//             return true;
//          }
//        }
//    }

// }
// }
      
  
    



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
  if (test) {
    cout << old_pos << endl;
    cout << move_blocks << endl;
    cout << current_pos << endl;
    cout << "previous pos is " << player[currentplayer]->getPos() <<endl;
  }

  if(current_pos > 39){
    current_pos -= 40;
    cout << "You pass OSAP and get 200$!" << endl;
    player[currentplayer]->updateBalance(200);
  }
 
  player[currentplayer]->setPos(current_pos);

  if(test){ cout<<"current pos is  " << player[currentplayer]->getPos() << endl; }

   td->notify(player[currentplayer],old_pos);
   td->display();

  if(test){ cout<<"current pos is  " << player[currentplayer]->getPos() << endl; }

   gameboard[current_pos]->notify(player[currentplayer]);

  if(test){ cout<<"final pos is " << current_pos << endl; }
}



void Game::settest(){
  test = true;
}


void Game::displayAssets(Player *player){
  cout << "Cash Balance: " << player->getBalance() << endl;
  cout << "Properties(Name, Owner, Improvements): " << endl;
  for (int i = 0; i < 40; ++i) {
    Academic *ap = dynamic_cast<Academic *>(gameboard[i]);
    if (!ap) {
      Building *bp = dynamic_cast<Building *>(gameboard[i]);
      if (bp && bp->getOwner() == player) cout << *bp;
    } else {
      if (ap->getOwner() == player) cout << *ap;
    }
  }
}

void Game::displayAllAssets() {
  for (int i = 0; i < 8; ++i) {
    if (player[i]) {
      cout << player[i]->getName() << endl;
      displayAssets(player[i]);
      cout << endl;
    }
  }
}

// void Game::displayAssets(Player *player){
//     for (int i = 0; i < 40; ++i) {
//         Academic *ap = dynamic_cast<Academic *>(gameboard[i]);
//         if (ap) {
//             cout << *ap;
//         }
//         else {
//             Building *bp = dynamic_cast<Building *>(gameboard[i]);
//             if (bp) {
//               cout << *bp;
//             }
//         }
//     }
// }

void Game::auctionProperty(Building *building){
  cout << "Auction for " << building->getName() << " start!" << endl;
  int playerLeft = numplayer;
  int highestPrice = 0;
  int current_auction_player = currentplayer;
  int highestPlayer = current_auction_player;
  bool active[8];

  //In the begining of a auction, all the players are active
  for(int i = 0 ; i < 8 ;i ++){
    if(player[i] != nullptr){
      active[i] = true;
    }
    else{
      active[i] = false;
    }
  }

  string command_auction;

  while(playerLeft != 1){

    do {
      current_auction_player = (current_auction_player + 1) % 8;
    } while ( (active[current_auction_player] == false));

    if(test) cout << "auction 1 "  << current_auction_player << endl;
    cout << "It is " << player[current_auction_player]->getName() <<" 's turn" ;
    cout << "The bid is " << highestPrice <<"$ right now by " << player[highestPlayer]->getName() << endl;
    cout << "You can do [bid money]/[withdraw]/[assets]" << endl;

    if(test) cout << "auction 2" << endl;

    while(true){
      cin >> command_auction;
      int auction_number;

      if(command_auction == "bid"){
        cin >> auction_number;
        if(auction_number <= highestPrice){
          cout << "Sorry, you should bid more than the current price, which is "  << highestPrice << endl;
        } else if (auction_number > player[current_auction_player]->getBalance() ){
          cout << "Sorry, you don't have such money" << endl;
        } else if(auction_number > highestPrice){
          highestPrice = auction_number;
          highestPlayer = current_auction_player;
          cout << "Bid successfully, current bid price is " << highestPrice << endl;
          break;
        } else{
          cout << "Reached end of condition" << endl;
        }
      } else if(command_auction == "assets"){
        displayAssets(player[current_auction_player]);
      } else if(command_auction == "withdraw"){
        playerLeft -= 1;
        active[current_auction_player] = false;
        cout << "You withdraw this auction, " << "number of current candidates are " << playerLeft << endl;
        break;
      } else{ 
        cout << "invaild commands, please input [bid money]/[withdraw]/[assets]" << endl;
      }
    }
  }

  player[highestPlayer]->updateBalance(-1 * highestPrice);
  building->setOwner(player[highestPlayer]);
  td->notify(building);
  td->display();

  cout << "Auction is end, " << building->getName() << " is bought by";
  cout << player[highestPlayer]->getName() << " by " << highestPrice << " $. " << endl;
}



int Game::diceroll(){
  string n;
  srand(time(0));
  if (test == false) {
    firstdice = 1+rand()%6;
    seconddice = 1+rand()%6;
  } else {
    cout << "Testing mode: Please enter two numbers between 1 and 6 (inclusive)." << endl;
    cin >> firstdice >> seconddice;
  }
  int sum = firstdice + seconddice;
  cout << "You have rolled a " << sum << "." << endl;
  return sum;
}

bool Game::checkMonopolized(Square *square) {
  return true;
}

void Game::buyImprovement(Square *square, Player *player) {
  int academicIndex = getAcademicIndex(square->getName());

  if (academicIndex == -1) return;
  Academic *academic = static_cast<Academic *>(square);
  Player *owner = academic->getOwner();

  if (player != owner) {
    cout << "You do not own this property." << endl;
    return;
  }

  int ownerBalance = owner->getBalance();
  int impCost = academic->getImpCost();

  if (ownerBalance < impCost) {
    cout << "You do not have enough funds to improve this property." << endl;
    return;
  }

  int impLevel = academic->getImpLevel();

  if (impLevel == 5) {
    cout << "This property cannot be improved further." << endl;
    return;
  }

  academic->setImpLevel(impLevel+1);
  owner->updateBalance(impCost * -1);

  cout << academic->getName() << " now has " << academic->getImpLevel() << " improvements. ";
  cout << "Your balance decreased to " << player->getBalance() << "." << endl;
}


void Game::sellImprovement(Square *square, Player *player) {
  int academicIndex = getAcademicIndex(square->getName());

  if (academicIndex == -1) return;

  Academic *academic = static_cast<Academic *>(square);
  Player *owner = academic->getOwner();

  if (player != owner) {
    cout << "You do not own this property." << endl;
    return;
  }

  int impCost = academic->getImpCost();
  int impLevel = academic->getImpLevel();

  if (impLevel == 0) {
    cout << "This property has no improvements." << endl;
    return;
  }

  academic->setImpLevel(impLevel-1);
  owner->updateBalance(impCost/2);

  cout << academic->getName() << " now has " << academic->getImpLevel() << " improvements. ";
  cout << "Your balance increased to " << player->getBalance() << "." << endl;
}

void Game::mortgageBuilding(Square *square, Player *player) {
  int buildingIndex = getBuildingIndex(square->getName());

  if (buildingIndex == -1) return;
  Building *building = static_cast<Building *>(square);
  Player *owner = building->getOwner();

  if (player != owner) {
    cout << "You do not own this property." << endl;
    return;
  }

  if (building->getImpLevel() == -1) {
    cout << "This property is already mortgaged." << endl;
    return;
  }

  int mortgageValue = building->getCost() / 2;
  owner->updateBalance(mortgageValue);
  building->setImpLevel(-1);

  cout << building->getName() << " has been mortgaged. ";
  cout << "Your balance increased to " << player->getBalance() << "." << endl;
}

void Game::unmortgageBuilding(Square *square, Player *player) {
  int buildingIndex = getBuildingIndex(square->getName());

  if (buildingIndex == -1) return;
  Building *building = static_cast<Building *>(square);
  Player *owner = building->getOwner();

  if (player != owner) {
    cout << "You do not own this property." << endl;
    return;
  }

  if (building->getImpLevel() != -1) {
    cout << "This property is not mortgaged." << endl;
    return;
  }

  int unmortgageCost = building->getCost() * 6 / 10;
  int ownerBalance = owner->getBalance();

  if (ownerBalance < unmortgageCost) {
    cout << "You do not have enough funds to unmortgage this property." << endl;
    return;
  }

  owner->updateBalance(unmortgageCost * -1);
  building->setImpLevel(0);

  cout << building->getName() << " has been unmortgaged. ";
  cout << "Your balance decreased to " << player->getBalance() << "." << endl;
}

void Game::forceBankruptcy(Player *landedPlayer, int fee) {
  int playerBalance = landedPlayer->getBalance();
  cout << "You owe the Bank " << fee << " dollars. " ;
  cout << "You only have " << playerBalance << " dollars. " << endl;
  int bankruptcyValue = 0;

  for (int i = 0; i < 40; ++i) {
    Building *bp = dynamic_cast<Building *>(gameboard[i]);
    if (bp) {   // bp is null if gameboard[i] is not building
      if (bp->getOwner() == landedPlayer) {
        bankruptcyValue += bp->getValue() / 2;
      }
    }
  }

  while (fee > landedPlayer->getBalance()) {
    if (bankruptcyValue < fee) {
      cout<<"improve <property> buy/sell: attempts to buy or sell an improvement for property"<<endl;
      cout<<"mortgage <property>: attempts to mortgage property."<<endl;
      cout<<"bankrupt: player declares bankruptcy."<<endl;
    } else {
      cout<<"improve <property> buy/sell: attempts to buy or sell an improvement for property"<<endl;
      cout<<"mortgage <property>: attempts to mortgage property."<<endl;
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
    }
  }

  cout << "You now have enough funds to pay the bank." << endl;
  landedPlayer->updateBalance(fee * -1);
  cout << "Your new balance is " << landedPlayer->getBalance() << "." << endl;
}


int Game::getAcademicIndex(string square) {
  for (int i = 0; i < 40; ++i) {
    Academic *ap = dynamic_cast<Academic *>(gameboard[i]);
    if (ap) {   // ap is null if gameboard[i] is not Academic
      if (ap->getName() == square) {
        return ap->getIndex();
      }
    }
  }

  cout << "This is not an Academic square." << endl;
  return -1;
}

int Game::getBuildingIndex(string square) {
  for (int i = 0; i < 40; ++i) {
    Building *bp = dynamic_cast<Building *>(gameboard[i]);
    if (bp) {   // bp is null if gameboard[i] is not Building
      if (bp->getName() == square) {
        return bp->getIndex();
      }
    }
  }
  cout << "This is not a Building square." << endl;
  return -1;
}


bool Game::loadGame(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    myfile >> numplayer;

    for (int i = 0; i < numplayer; ++i) { // Read player data
      myfile >> playername[i];

      if (playername[i] == "BANK") {
        cout << "Cannot have player named BANK." << endl;
        return false;
      }

      myfile >> chosensymbol[i];
      int playerNumTimsCups;
      myfile >> playerNumTimsCups;
      int playerBalance;
      myfile >> playerBalance;
      int playerPosition;
      myfile >> playerPosition;
      int isStuckDC = 0;
      int playerDCTurn = -1;

      if (playerPosition == 10) {
        myfile >> isStuckDC;
        if (isStuckDC != 0) myfile >> playerDCTurn;
      }

      player[i] = new Player(chosensymbol[i], playername[i], this, playerNumTimsCups, playerBalance, 
      playerPosition, playerDCTurn);
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
    }

    currentplayer = 0;
    myfile.close();

    for(int i = 0 ; i < 39 ; i++){
      Building *bp = dynamic_cast<Building *>(gameboard[i]);
      if(bp) td->notify(bp);
    }
    
    // td->display();
    return true;
  } else {
    cout << "Unable to open file." << endl;
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
