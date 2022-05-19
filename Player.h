#ifndef ASSIGN2_PLAYER
#define ASSIGN2_PLAYER
#include <string>
#include "Tile.h"
#include "LinkedList.h"
#include "TileBag.h"
#include <memory>
#include <iostream>
#define MAX_HAND 7

class Player{
    public:
    Player(std::string name);
    ~Player();
    std::string getName() const;
    int getScore() const;
    Tile* getTileByCharacter(const char character) const;
    void setName(std::string name);
    void addScore(int points);
    void setHand(LinkedList hand);
    void setScore(int score);
    void addToHand(Tile& tile);
    void removeFromHand(Tile& tile);
    LinkedList* getHand() const;


    private:
        std::string name;
        int score;
        LinkedList * hand;

};

#endif //ASSIGN2_PLAYER