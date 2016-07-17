#include "game.h"
#include <string>
#include <iostream>
#include <cstdlib>
// #include <ctime>
#include <locale>
#include <fstream>
#include <sstream>


using namespace std;

Game::Game():numplayer(0),currentplayer(0),rimcup(4),test(false),seed(0),rolled(false),
firstdeice(0),seconddice(0){
    // for(int i = 0 ; i < 8 ; i++){
    //     player[i] = nullptr;
    // }

}

Game::~Game(){

}


void Game::normalinit(){
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

   
   //initial name
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
        	cout << endl;
        	break;
        }
        }

        //initial character 
        cout << "Hello! " << playername[current] << ", please choose an character whcih represents you." << endl;
        cout << "You can choose from G(Goose), B(GRT BUS), D(Tim Hortons Doughnut), P(Professor) " <<endl;
        cout << "S(Student), $ (Money), L (Laptop), T (Pink tie) " << endl;

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
            	cout << endl;
        	    break;
            }

         }
          
            else {
            	cout << "Please enter a valid character. " << endl;
            }

        }

       }

       
       for(int i = 0 ; i < numplayer ; i++){
        player[i] = new Player(chosensymbol[i], playername[i], 0, 0, 1500 , 0 , 0 , this);
       	// cout << chosensymbol[i] << " " << playername[i] << endl;
       }

       for(int i = 0 ; i < numplayer ; i++){
        
        cout << player[i]->getSymbol() << " " << player[i]->getName() << endl;
       }

   }

   
// void Game::run(){
// 	string command;
    
//     while(true){
//     cout << "Hello! it is " << player[current]->getName(); << "'s turn" << endl;


//     while(cin >> command){
//     if( command == "roll"){
//      int dice_result = diceroll();


//     }





//     }


    
    



//     }

// }


// void Game::blockaction(){
    
// }





















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
    srand(seed);
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
    return firstdeice+seconddice;
}