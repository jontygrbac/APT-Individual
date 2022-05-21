#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include "Tile.h"
#include "LinkedList.h"
#include <random>
#define MAX_TILES 98
class TileBag {
public: 
   //TileBag(std::ifstream ifs);
   TileBag(unsigned int);
   TileBag(LinkedList & bag);
   TileBag();
   ~TileBag();
   Tile* pop();
   Tile* get(int index);
   Tile* getFront();
   Tile* getBack();
   void add(Tile & tile);
   void remove(Tile & tile);
   
   Tile* drawTile();
   bool isEmpty();
   int getSize();
private:
   LinkedList* tiles_list;
   int size;
};


#endif // ASSIGN2_TILE_H
