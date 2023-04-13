#include "player.hpp"
#include "card.hpp"
#include "string"
using namespace std;
using namespace ariel;

Player::Player(){};
Player::Player (string player){
    this->player_name=player;
}
int Player::stacksize(){
    int size = this->card_box.size();
    return size;
}
int Player::cardesTaken(){
    int total = this->total_wins;
    return total;
}
Card Player::let_card(){
    if(!this->card_box.empty()){
        Card box_temp=this->card_box.back();
        this->card_box.pop_back();
        return box_temp;
    }else {
        throw std::invalid_argument("the stack is empty");}
    return Card();
}
