#include "TileBag.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "time.h"
#include <memory>
#include <algorithm>
#include <array>


TileBag::TileBag(unsigned int seed){
    tiles_list = new LinkedList();
    std::array<Tile*, MAX_TILES> temp;
    std::ifstream ifs("ScrabbleTiles.txt");
    std::string line = "";
    int i = 0;
    while(std::getline(ifs, line)){
        //parse the line to get value and letter
        int value = stoi(line.substr(line.find(" ") + 1, line.length()));
        char letter = line.substr(0, line.find(" ")).at(0);
        //add the tile to a temporary array
        Tile *tile = new Tile(value, letter);
        temp[i] = tile;
        i++;
    }
    std::default_random_engine generator (seed);
    std::shuffle(temp.begin(), temp.end(), generator);

    for(int i =0; i < MAX_TILES; ++i){
        tiles_list->add_back(temp[i]);
    }
    this->size = 98;
 }
TileBag::TileBag(LinkedList & bag){
    tiles_list = &bag;
}
TileBag::~TileBag(){
    for(int i = 0; i < this->tiles_list->size(); i++){
        delete this->tiles_list->get(i);
    }
    delete tiles_list;
}
Tile* TileBag::pop(){
    Tile* tile = new Tile(*tiles_list->get(0));
    tiles_list->remove_front();
    size -= 1;
    return tile;
}
Tile* TileBag::get(int index){
    Tile * tile;
    for(int counter = 0; counter < MAX_TILES; ++counter){
        tile = tiles_list->get(index);
    }
    return tile;
}
void TileBag::add(Tile & tile){
    tiles_list->add_back(&tile);
}
void TileBag::remove(Tile & tile){
    tiles_list->add_back(&tile);
}
Tile* TileBag::getFront(){
    return tiles_list->getFront();
}
Tile* TileBag::getBack(){
    return tiles_list->getFront();
}

/*
 * Draws a tile from the front of the tile bag to return,
 * then deletes it from the tile bag.
 */
Tile* TileBag::drawTile() {
    Tile* returnTile = nullptr;
    if (size > 0) {
        returnTile = new Tile(*get(0));
        pop();
    }
    return returnTile;
}

bool TileBag::isEmpty() {
    bool flag = true;
    if (size != 0) {
        flag = false;
    }
    return flag;
}

int TileBag::getSize(){
    return size;
}