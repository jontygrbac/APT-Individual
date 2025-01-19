# Scrabble Command Line Application (2nd Year of University)

## Overview
This is a command line version of Scrabble built using C++. The game allows two players to play Scrabble on a 15x15 board. Players can start a new game, load an existing game, or view credits. The game provides options to place tiles, replace tiles, pass turns, save games, and quit.

## Features
- **Start a New Game**: Enter player names and begin a new game.
- **Load an Existing Game**: Load a previously saved game.
- **Game Interface**: View the current board and player's hand.
- **Player Actions**: Place tiles on the board, replace tiles, pass turns, and save the game.
- **Word Validation**: Words will be validated to ensure they are valid words and placed in correct orientation, connecting to previous words etc.
- **Scoring**: Scoring based on connections with adjacent tiles.
- **Commands**: Type `help` to view a list of available commands.

## How to Run
1. Clone the repository or download the project files.
2. Compile the project using the `make` command.
3. Run the compiled `scrabble` executable.

### Commands to run:
```bash
make scrabble
./scrabble
```

## Gameplay
Upon starting the game, you'll be presented with the following options:
```
Welcome to Scrabble!
New Game: Enter '1'
Load Game: Enter '2'
Credits (Show student information): Enter '3'
Quit: Enter '4'
```
## Example Gameboard
```
    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  
   -------------------------------------------------------------
A  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
B  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
C  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
...
```



