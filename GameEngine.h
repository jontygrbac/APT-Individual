#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#define MAX_ROW 15
#define MAX_COL 15
#define ASCI 48
#define MAX_PLAYERS 2
#define LETTERS 26

#define PLACE "place"
#define REPLACE "replace"
#define SAVE "save"
#define EXIT "exit"
#define PASS "pass"
#define DONE "Done"
#define SAVE_EXTENSION ".txt"
#define HELP "help"


#include <iostream>
#include <memory>
#include <fstream>
#include "Player.h"
#include "TileBag.h"
#include "Board.h"
#include "Dictionary.h"

class GameEngine {
public:
    /*
    * Initialise the game engine
    */
    GameEngine();

    /*
    * Destructs playerVector, tileBag and board
    */
    ~GameEngine();

    /*
    * Initialise a new game by creating players, populating the playerVector vector,'
    * initialise the tilebag and game board
    */
    void newGame();
    /*
    * Changes and keeps track of turns between players and allows the ability to
    * place, replace tiles and skip a players turn. Ends when requirements for the game to end
    * are met.
    */
    void playTheGame();
    void LoadGame();
private:
    /*
    * Draws Tiles to a Player's hand up to the maxium Tiles a hand can hold
    */
    void drawFullHand(Player & player);
    /*
    * Validates that a Player name is correctly formatted
    */
    bool validateName(const std::string name) const;
    /*
    * Initiates a round of scrabble and checks for a gameover or if a Player quits
    */
    bool playRound(int counter);
    bool playerNoLongerHasTiles();
    /*
    * Prints to console the game over message
    */
    void gameOverPrint() const;
    /*
    * Saves the current Scrabble game to a formatted file
    */
    bool createSaveFile(std::string fileName, Player* player1, Player* player2, Board* board, TileBag* tilebag, int counter);
    /*
    * Checks the game board for a word when the Player places seven tiles in one turn
    */
    void bingo();
    /*
    * Replaces a specific hand tile from the Player's hand from the TileBag
    */
    void replaceHandTile(Player& player, const char character);

    /*
    * Ensure tile placement is correct orientation, returns orientation type
    * 0 = Horizontal placement
    * 1 = Vertical placement
    * 2 = Invalid placement
    */
    int validatePlacement(std::vector<int> rowplacement, std::vector<int>colplacement);
    /*
    * Validate if it is an actual word
    */
    bool validateWords(std::vector<std::vector<Tile*> > words);
    /*
    * Process for scoring
    */
    bool scoring(std::vector<int> rowplacement, std::vector<int>colplacement, Player* player, int orientation, int boardcheck);
    /*
    * Stores number of Players playing
    */
    std::vector<Player*> playerVector;
    /*
    * LinkedList of Tiles for the current game
    */
    TileBag* tileBag;
    /*
    * Game board for the current game
    */
    Board* board;
    /*
    * Dictionary for current game
    */
    Dictionary* dict;

    bool firstTurn;
};

#endif // GAMEENGINE_H