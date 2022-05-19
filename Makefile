.default: all

all: scrabble

clean:
	rm -rf scrabble *.o *.dSYM

scrabble: Tile.o Node.o LinkedList.o Board.o GameEngine.o Player.o TileBag.o scrabble.o Dictionary.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
