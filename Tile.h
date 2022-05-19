#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// Define a Letter type
typedef char Letter;

// Define a Value type
typedef int Value;

class Tile {
public: 
   Tile();
   Tile(Value value, Letter letter);
   ~Tile();
   Value getValue();
   Letter getLetter();
private:
   Letter letter;
   Value  value;
};


#endif // ASSIGN2_TILE_H
