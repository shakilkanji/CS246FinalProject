#include "dice.h"

using namespace std;

Dice::Dice():firstdeice(0),seconddice(0),test(false),seed(0){}

Dice::~Dice(){
    std::cout<<"dice is deletd"<<std::endl;
}

bool Dice::pair(){
    if(dice1 !=dice2 ){
    	return false;
    }
    else{
    	return true;
    }
    
}

void Dice::settest(){
   test = true;
}


int Dice::roll(){
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