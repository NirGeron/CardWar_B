#include "card.hpp"
using namespace ariel;
using namespace std;

Card::Card(string num, string name){
    if(num != "Ace"){
    this->number=stoi(num);
    this->name=name;
    int value;
    }
}

string Card::get_card(){
    if(this->value()> 10){
        return this->type_of_card();
    }
    else{
        return (to_string(this->value()) + " of "+ this->type_of_card()); 
    }    
}