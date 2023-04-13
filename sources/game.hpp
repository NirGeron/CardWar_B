#ifndef GAME_H
#define GAME_H
#pragma once
#include <vector>
#include <iostream>
#include "player.hpp"
namespace ariel{
    
class Game {
   private:
    Player &p1;
    Player &p2;
    string res="draw";
    vector<Card> cards;
    vector<string> final_res;

public:
    Game(Player& play1, Player& play2);
    vector<Card> mydeck(){return this->cards;}
    void mixcards(vector<Card>& cards);
    void deal_cards();
    void printWiner(){cout<<"winner:"+this->res<<endl;}
    void playTurnafterdraw(int draws);
    void printLog();
    void printStats();
    void playTurn();
    void printLastTurn();
    void playAll(); 
};
}
#endif