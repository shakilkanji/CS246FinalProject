#include "game.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <fstream>
#include <sstream>


using namespace std;

Game::Game():numplayer(0),currentplayer(0),rimcup(4),test(false),sumofdice(0),rolled(false),roll_time(0),
firstdeice(0),seconddice(0){
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

}


void Game::normalinit(){
  td->display();

     cout << "Welcome to Watopoly!" << endl;
     cout << "Please enter the number of players in the game [2-8]" << endl;
     int temp_num;
     while (cin >> temp_num) {
      if ( (temp_num <= 8) && (temp_num >= 2) ) {
        numplayer = temp_num;
        break;
      } 
      else {
        cout << "Your input is out of range, please enter a number between 2 and 8 (inclusive) " << endl;
      }
   }

   
   //initial player's name
   for( int current = 0 ; current < numplayer ; current++ ){
       cout << "Hello, player" << current + 1 << " !" <<" Please input your name" << endl;;
        
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
        	cout << "Someone has already chosen this name, please change to another one" << endl;
        }
        else{
        	playername[current] = temp_name;
        	break;
        }
        }


        //initial player's character 
        cout << "Hello! " << playername[current] << ", please choose an character whcih represents you." << endl;
        cout << "You can choose from G(Goose) / B (GRT BUS) / D (Tim Hortons Doughnut)  " <<endl;
        cout << "P (Professor) / S (Student) / $ (Money) / L (Laptop) / T (Pink tie) " << endl;

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
            }

            else{
            	chosensymbol[current] = temp_symbol;
        	    break;
            }
         }       
            else {
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
    
    while(!isWon){
    

    next();


    while(cin >> command){
    if( command == "roll" ){
     
     //if the player has already roll the dice 
     if(rolled == true){
     cout << "You cannot roll the dice anymore in this turn" << endl;   
     }

     //player does not roll
     else{
     int dice_result = diceroll();
     roll_time += 1;
     
     if(dicepair() == true){
      //if the player rolls 3 times, he'll be sent to DC tims line and cannot move
      if(roll_time == 3){
        cout << "You have rolled 3 doubles, as a result, you are moved to DC tims line" << endl;
        rolled = true;
      }
      else{
        cout << "You roll a double and you can roll a dice for another time" << endl;
      }    
     }

     //roll a nondouble dice 
     else{
     cout << "you go to a square" << endl;

     rolled = true;
     }
     }
    }


    else if( command == "trade"){
     cout << "you will do a trade" << endl;
     

    }
    
    else if( command == "improve") {
      cout << "you will do an improve" << endl;  
    }

    else if(command == "mortage") {
      cout << "you will do a mortage" << endl;  
    }
    
    else if(command == "unmortgage") {
      cout << "you will do a unmortgage" << endl;  
    }

    else if(command == "bankrupt") {
      cout << "you will do a bankrupt" << endl;  
    }
 
    else if(command == "assets") {
      cout << "you will do a assets" << endl;  
    }

    else if(command == "all") {
      cout << "you will do a all" << endl;  
    }

    else if(command == "save") {
      cout << "you will do a save" << endl;  
    }

    else if(command == "next") {
      if(rolled == false){
        cout << "You cannot finish this turn, you should roll the dice first" << endl;
      }
      else{
        cout << "you will go to next turn" << endl;  
        
        //find next player 
        do { 
            currentplayer = (currentplayer + 1) % 8;
        }        
        while (player[currentplayer] == nullptr);

        next();
      }
    }

    else if(command == "exit") {
        cout << "You will exit the game in a few seconds" <<endl;
        return;
    }
    }
    }
    cout << "Somebody has won!" << endl;
}

void Game::next(){
  for (int i = 0 ; i < numplayer; i++) {
    td->notify(player[i]);
  }
  td->display();

    cout << "Hello! it is " << player[currentplayer]->getName() << "'s turn!" << endl;
    cout << endl;
    cout<<"You can choose the following commands:"<<endl;
    cout<<"roll: the player rolls two dice, moves the sum of the two dice and takes action on the square they landed on."<<endl;
    cout<<"next: give the control to the next player. "<<endl;
    cout<<"trade <player> <give> <receive>: having trade with player, offering give and requesting receive."<<endl;
    cout<<"improve <property> buy/sell: attempts to buy or sell an improvement for property"<<endl;
    cout<<"mortgage <property>: attempts to mortgage property."<<endl;
    cout<<"unmortgage <property>: attempts to unmortgage property."<<endl;
    cout<<"bankrupt: player declares bankruptcy."<<endl;
    cout<<"assets: displays the assets of the current player."<<endl;
    cout<<"all: displays the assets of every player.."<<endl;
    cout<<"save <filename>: saves the current state of the game."<<endl<<endl;
    
    rolled = false;
    roll_time = 0;
   
}


// void Game::blockaction(){
    
// }


void Game::asktobuy(Building *building, Player *buyer ) {
   
   if(buyer->getBalance() < building->getCost()){
    cout << "Sorry you don't have enough money to buy this building. " << "You current balance is" << buyer->getBalance();
    cout << "The building will spend " << building->getCost() << endl;
    // cout << "Auctions will begin" << endl;
    auction();
   }
   cout << "Do you want to buy " << building->getName() << "which will spend you " << building->getCost() << "$?" <<endl;
   cout << "[yes/no/assets]" << endl;
   
   string temp_askbuy;
   while( cin >> temp_askbuy){
    if(temp_askbuy == "yes"){
        cout << "You have purchesd " << building->getName() << endl;
        building->setOwner(buyer);
        buyer->updateBalance( -1 * building->getCost() );
        //notify textdisplay 
        break;
    }
    else if (temp_askbuy == "no"){
        cout << "Auctions will begin" << endl;
        break;
    }
    else if( temp_askbuy == "assets" ){
        assets();
        auction();
    }
    else{
        cout << "invaild command, please input yes/no/assets. " <<endl;
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

bool Game::checkmonoimprov(string building){
    int current_index = getPropertyIndex(building);
    Building *current_pointerbuilding = dynamic_cast<Building *>(gameboard[current_index]);
    Academic *current_pointeracademic = dynamic_cast<Academic *>(current_pointerbuilding);
    for( int i = 0 ; i < 40 ; i++) {
       int index =  getPropertyIndex( gameboard[i]->getName());
      if ( ( index  != -1 )||( index != 12 )||( index != 28 )||( index != 28 )||
        ( index != 5 )||( index != 15 )||( index != 25 )||( index != 31 ) ) {
       Building *pointerbuilding = dynamic_cast<Building *>(gameboard[index]);
       Academic *pointeracademic = dynamic_cast<Academic *>(pointerbuilding);
       if(pointeracademic->getMonoBlock() == current_pointeracademic->getMonoBlock()) {
         if(pointeracademic->getImpLevel() != 0 ){
            return true;
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
    return firstdeice+seconddice;
}



bool Game::dicepair(){
    if(firstdeice  != seconddice ){
    	return false;
    }
    else{
    	return true;
    }
    
}


void Game::settest(){
   test = true;
}



int Game::diceroll(){
    string n;
    srand(time(0));
    if(test == false){
    firstdeice = 1+rand()%6;
    seconddice = 1+rand()%6;
    
    }
    else{
    cout << "It is testing mode" << endl;
    cout << "Please enter two numbers between 1 and 6 (inclusive)." << endl;
    cin >> firstdeice >> seconddice;

    }
    cout << "first dice rolls " << firstdeice << endl;
    cout << "second dice rolls " << seconddice << endl;
    cout << "total is " << firstdeice+seconddice << endl;
    cout << "Input any string to countinue" << endl;
    cin >> n;
    
    return firstdeice+seconddice;
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
        if (command == "improve") {
            string property;
            cin >> property;
            int propertyIndex = getPropertyIndex(property);
            if (propertyIndex >= 0) {
                string buySell;
                cin >> buySell;
            }
        }
    }

}

int Game::getPropertyIndex(string property) {
    for (int i = 0; i < 40; ++i) {
        Building *bp = dynamic_cast<Building *>(gameboard[i]);
        if (bp) {   // bp is null if gameboard[i] is not building
            if (bp->getName() == property) {
                return bp->getIndex();
            }
        }
    }
    cout << "Not a valid property." << endl;
    return -1;
}