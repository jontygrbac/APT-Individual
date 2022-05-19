#include "Board.h"

Board::Board(int rows, int cols):
//This will be initialized to 15 until milestone 3
rows(rows), cols(cols)
{
    //Initialize vector of vectors
    for (int i = 0; i < rows; ++i){
        std::vector<Tile*> v1(cols);
        board.push_back(v1);
    }
}


Board::Board(Board& other):
rows(other.rows), cols(other.cols)
{
    //adding other's vectors to board
    for (int i = 0; i < other.rows; ++i){
            board.push_back(other.board[i]);
    }
}

Board::~Board(){
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            delete board[i][j];
        }
    }
    return;
}

int Board::getSize(){
    return board.size();
}

bool Board::insert(Tile* t, int row, int col){
    bool success = false;
    if (row >= 0 && col >= 0 && row < rows && col < cols && board[row][col]==nullptr){
        board[row][col] = t;
        success = true;
    }
    return success;
}

Tile* Board::get(int row, int col){
    Tile* tile = nullptr;
    if (row >= 0 && col >= 0 && row < rows && col < cols){
        tile = board[row][col];
    }
    return tile;
}
bool Board::printBoard(){
    //Array representing letters, to allow for easier print of row value
    char numtoletter[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                      'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                      'X', 'Y', 'Z'};
    //Initial spacing for board
    std::cout << "    ";

    //For each col, print the integer value 
    //(special case for double digit numbers, they have one less space)
    for (int i = 0; i < cols; ++i){
        if (i >= 10){
        std::cout << i << "  ";
        }
        else{
        std::cout << i << "   ";
        }
    }
    std::cout << std::endl;

    //Same spacing as initial
    std::cout << "   ";

    //Printing dotted line
    for (int i = 0; i < cols; ++i){
        std::cout << "----";
    }
    std::cout << "-" << std::endl;
    
    //Printing all chars out, check if empty, if empty print a space instead
    //else print the char
    for(int i = 0; i < rows; ++i){
        std::cout << numtoletter[i] << "  |";
        for(int j = 0; j < cols; ++j){
            if (board[i][j] == nullptr){
            std::cout << "   |";    
            }
            else{
            std::cout << " " << board[i][j]->getLetter() << " |";
            }
        }
        std::cout << std::endl;
    }
    //return success
    return true;
}

    int Board::getNumberOfTilesOnBoard(){
        int retCount = 0;
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                if (board[i][j] != nullptr){
                    retCount += 1;
                }
            }
        }
        return retCount;
    }

    std::vector<std::string> Board::getAllTilesOnBoard(){
        char numtoletter[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                        'X', 'Y', 'Z'};

        std::vector<std::string> retVec;

        
        
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                if (board[i][j] != nullptr){
                    Tile* tile = board[i][j];
                    std::string a = "";
                    std::string row = "";
                    
                    std::string col = "";
                    col = std::to_string(j);
                                        
                    row = numtoletter[i];

                    a = a + tile->getLetter() + "@" + row + col;
                    tile = nullptr;
                    retVec.push_back(a);
                }
            }
    }

    return retVec;
    }