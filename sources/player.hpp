#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "card.hpp"
#include <vector>
using namespace std;

namespace ariel{
    
class Player {
    string player_name;
    vector<string> win_card;
    vector<string> draw_card;
    int total_wins=0;
    int total_draws=0;
    vector<Card> card_box;
    
        public:
            Player();
            Player (string player);
            string name(){return this->player_name;} 
            int stacksize();
            int cardesTaken();
            void won(int draw=0){this->total_wins=this->total_wins+2+draw*2;} 
            void lastdraw(){this->total_wins=this->total_wins-2;}
            int wins()const{return this->total_wins;}
            void draw(int n=0){this->total_draws=this->total_wins+n;}
            int draw_amount()const{return this->total_draws;}
            Card let_card();
            vector<string> draw_stats(){return this->draw_card;}
            vector<string> win_stats(){return this->win_card;}
            void push_card(Card& card){this->card_box.push_back(card);}
            void wins_stats(string const &turn){this->win_card.push_back(turn);}
            void stat_draw(string const &turn){this->draw_card.push_back(turn);}
        }; 
}

#endif
