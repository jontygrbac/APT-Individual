#include "Tile.h"

Tile::Tile(){

}
Tile::Tile(Value value, Letter letter){
    this->value = value;
    this->letter = letter;
};
Tile::~Tile(){
    
};
Value Tile::getValue(){
    return value;
};
Letter Tile::getLetter(){
    return letter;
};

