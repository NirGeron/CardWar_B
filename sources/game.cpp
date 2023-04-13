#include <algorithm>
#include <random>
#include <chrono>
#include "game.hpp"
#include "player.hpp"
#include "card.hpp"

using namespace ariel;

Game::Game(Player& play1, Player& play2): p1(play1), p2(play2)
{
    // generating cards box
    string type[4] = {"club", "diamond", "spade", "heart"};
    string value[13] = {"13", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1"};
      for (int j = 0; j < 13; j++) {
          for (int i = 0; i < 4; i++) {
              Card card_(value[j], type[i]);
              this->cards.push_back(card_);
          }
      }
      this->mixcards(this->cards);

    // deal cards between 2 players
      for (size_t j = 0; j < this->cards.size(); j++){
         if( j%2 != 1 ){
            this->p1.push_card(this->cards[j]);
         }else{
            this->p2.push_card(this->cards[j]);
         }
  }
   };
   
void Game::playTurn(){
   
   if(this->p2.stacksize()!=0 && &(this->p1) != &(this->p2) && this->p1.stacksize()!=0){
      Card card_p2=this->p2.let_card();
      Card card_p1=this->p1.let_card();

      if(card_p2.value() < card_p1.value()){
         this->final_res.push_back(this->p1.name() + card_p1.get_card() + this->p2.name() + card_p2.get_card() +". "+ this->p1.name() + " won" );
         this->p1.wins_stats(card_p1.get_card());
         this->p1.won();  

      }else if(card_p2.value()!=2 && card_p1.value()==2 ){
         this->final_res.push_back(this->p1.name() + card_p1.type_of_card() + this->p2.name() + card_p2.get_card()+ this->p1.name()+" won");
         this->p1.wins_stats(card_p1.type_of_card());
         this->p1.won();   

      }else if(card_p2.value()==2 && card_p1.value()!=2 ){
         this->final_res.push_back(this->p2.name() + card_p2.type_of_card()+ this->p1.name() + card_p1.get_card()+". " + this->p2.name()+ " won" );
         this->p2.wins_stats(card_p2.type_of_card());
         this->p2.won();

      }else if (card_p1.value() == card_p2.value()){
         this->final_res.push_back(this->p1.name() + card_p1.get_card() +  this->p2.name() + card_p2.get_card()+ "draw" );
         this->p2.stat_draw( card_p2.get_card());
         this->p1.stat_draw( card_p1.get_card());
         Game::playTurnafterdraw(1);

      }else if(card_p2.value() > card_p1.value()){
         this->final_res.push_back(this->p2.name() + card_p2.get_card() + this->p1.name() + card_p1.get_card() +". "+ this->p2.name() + " won" );
         this->p2.wins_stats(card_p2.get_card()); 
         this->p2.won();  
      }
      if(this->p1.wins()==this->p2.wins()){
         this->res="draw";
      }else if(this->p1.wins()<this->p2.wins()){
         this->res=this->p2.name();
      }else if(this->p1.wins()>this->p2.wins()){
         this->res=this->p1.name(); 
      }else{
         this->res="error";
      }
   }else if(this->p1.stacksize()==0 && this->p2.stacksize()==0){
      throw std:: __throw_out_of_range;
   }
   
   else {throw std::__throw_logic_error;}
  
};

void Game::playTurnafterdraw(int draws=0){
   if(this->p2.stacksize()!=0 && this->p1.stacksize()!=0 ){
      Card card_p2=this->p2.let_card();
      Card card_p1=this->p1.let_card();

      if(card_p2.value()!=2 && card_p1.value()==2){
         this->final_res.push_back(this->p1.name()  + card_p1.type_of_card() + this->p2.name() + card_p2.get_card()+ this->p1.name()+" won");
         this->p1.wins_stats( card_p1.type_of_card());
         this->p1.won(draws);

      }else if(card_p1.value()> card_p2.value()){
         this->final_res.push_back(this->p1.name() +  card_p1.get_card() + this->p2.name() + card_p2.get_card() + this->p1.name() + " won" );
         this->p1.wins_stats(card_p1.get_card());
         this->p1.won(draws);


      }else if(card_p1.value() < card_p2.value()){
         this->final_res.push_back(this->p2.name() + card_p2.get_card() + this->p1.name() + card_p1.get_card() + this->p2.name() + " won" );
         this->p2.wins_stats(card_p2.get_card());
         this->p2.won(draws);

      }else if((this->p1.stacksize() + this->p2.stacksize()) ==0){
      this->p2.won(((draws)/2));
      this->p2.lastdraw();   
      this->p1.won(((draws)/2));
      this->p1.lastdraw();

      }else if (card_p2.value() == card_p1.value()){
         this->final_res.push_back(this->p1.name() + card_p1.get_card() + this->p2.name() + card_p2.get_card()+ "draw" );
         this->p1.stat_draw( card_p1.get_card());
         this->p2.stat_draw( card_p2.get_card());
         Game::playTurnafterdraw(draws+1);

      }else if(card_p2.value()==2 && card_p1.value()!=2 ){
         this->final_res.push_back(this->p2.name() + card_p2.type_of_card()+this->p1.name() + card_p1.get_card()+this->p2.name()+ " won" );
         this->p2.wins_stats(card_p2.type_of_card());
         this->p2.won(draws);      

      }
        
   }
   else {
      throw std::__throw_logic_error;}

   if(this->p1.wins()==this->p2.wins()){
         this->res="draw";
      }else if(this->p1.wins()<this->p2.wins()){
         this->res=this->p2.name();
      }else if(this->p1.wins()>this->p2.wins()){
         this->res=this->p1.name();
      }else{
         this->res="error";
      }

}

void Game::printLastTurn(){
   if(this->final_res.empty()){
      cout << "game dont start yet..."<< endl;
   }else {
      cout<< final_res.back()<< endl;}

};

//playing turns
void Game::playAll(){
   while(this->p1.stacksize()!=0 && this->p2.stacksize()!=0){
      Game::playTurn();
   }
   
};

//printing for final log
void Game::printLog(){
   for(string i:this->final_res){ 
      cout<< i <<endl;
   }
   
};

void Game::mixcards(vector<Card>& cards) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}

void Game::printStats(){
      double draw_precent=100 * (this->p1.draw_stats().size()/(this->p1.draw_stats().size()+this->p1.win_stats().size()+this->p2.win_stats().size()));
      cout<< "draws%:" << draw_precent<<endl;
      double win_precent=100 * (this->p1.win_stats().size()/(this->p1.draw_stats().size()+this->p1.win_stats().size()+this->p2.win_stats().size()));
      cout<< "wins%" << win_precent<<endl;
      cout<< "results of "<<this->p1.name()+ ": "<<endl;
      cout<< "draws "<<this->p1.draw_stats().size()<<endl;
      cout<< "wins:" << this->p1.win_stats().size()<<endl;

      double draw_precent2=100 * (this->p2.draw_stats().size()/(this->p2.draw_stats().size()+this->p2.win_stats().size()+ this->p1.win_stats().size()));
      cout<< "draws%" << draw_precent2<<endl;
      double win_precent2=100 * (this->p2.win_stats().size()/(this->p2.draw_stats().size()+this->p2.win_stats().size()+ this->p1.win_stats().size()));
      cout<< "wins%" << win_precent2<<endl;
      cout<< "results of"<<this->p2.name()+ ": "<<endl;
      cout<< "draws"<<this->p2.draw_stats().size()<<endl;
      cout<< "wins" << this->p2.win_stats().size()<<endl;
   
};