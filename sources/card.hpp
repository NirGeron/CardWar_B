#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std; 

namespace ariel {
class Card {
    string name;
    int number;

public:
    Card();
    Card(string num , string name);
    int value ()const{return this->number;}
    string type_of_card(){return this->name;}
    string get_card();
    };
}

#endif