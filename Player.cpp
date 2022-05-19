#include "Player.h"

Player::Player(std::string name){
    this->name = name;
    this->score = 0;
    this->hand = new LinkedList();
}
Player::~Player(){
    hand = nullptr;
}
std::string Player::getName() const{
    return name;
}
int Player::getScore() const{
    return score;
}
Tile* Player::getTileByCharacter(const char character) const{
    Tile * handTile = nullptr;
    bool found = false;
    for(int index = 0; index < MAX_HAND; ++index){
        if(hand->get(index)->getLetter() == character && !found){
         handTile = hand->get(index);
         found = true;
        }
    }
    return handTile;
}
void Player::setName(std::string name){
    this->name = name;
}
void Player::addScore(int points){
    score += points;
}
void Player::setHand(LinkedList hand){
    this->hand = &hand;
}
void Player::setScore(int score){
    this->score = score;
}
void Player::addToHand(Tile& tile){
    hand->add_back(&tile);
    // bag.remove(*tile);
}
void Player::removeFromHand(Tile& tile){
    for(int counter = 0; counter < MAX_HAND; ++counter){
        if(hand->get(counter) == &tile){
            hand->remove(counter);
        }
    }
}
LinkedList* Player::getHand() const{
    return hand;
}