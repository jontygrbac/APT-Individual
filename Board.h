#ifndef ASSIGN2_BOARD
#define ASSIGN2_BOARD
#include <vector>
#include <iostream>
#include <string>
#include "Tile.h"


class Board {
public:

   /*
   *Constuct a board of int rows and int columns
   */
   Board(int rows, int cols);
   //Copy Constructor
   Board(Board& other);
   //Destructor
   ~Board();
   /*
   * Returns the size of the board vector
   */
   int getSize();
   /*
   * Insert a Tile into the board vector at given row and column
   */
   bool insert(Tile* t, int row, int col);
   /*
   * Return a Tile at given row and column
   */
   Tile* get(int row, int col);
   /*
   * Prints the board vector to standard output and formats it into the game board
   */
   bool printBoard(); 
   /*
   * Returns the number of Tiles in the board vector
   */
   int getNumberOfTilesOnBoard();
   /*
   * Returns a vector of all Tiles in the board vector
   */
   std::vector<std::string> getAllTilesOnBoard();

private:
   /*
   * Stores a list of Tiles and their position (row and column) to be printed on the board
   */
   std::vector<std::vector<Tile*>> board;
   /*
   * Specific row of the game board
   */
   int rows;
   /*
   * Specific column of the game board
   */
   int cols;
};

#endif //ASSIGN2_BOARD