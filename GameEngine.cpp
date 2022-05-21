#include "GameEngine.h"
#include <string>
#include <chrono>

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

// Creates a new game - Initialises players, board, tiles and player hands
void GameEngine::newGame(int playerCount)
{
    std::cout << "Starting a new game" << std::endl
              << std::endl;
    
    // Entering names for players   
    int counter = 0; 
    std::string playerName;        
    do {
        std::cout << "Enter a name for player " << counter+1 << " (uppercase characters only)" << std::endl;
        do{
            std::cout << "> "; 
            std::cin >> playerName;
            if(!validateName(playerName)){
                std::cout << "Invalid input" << "\n";
            }
        }while(!validateName(playerName));
        std::cout << "\n";
        playerVector.push_back(new Player(playerName));
        ++counter;
    } while (playerVector.size() < playerCount && !std::cin.eof());
    std::cin.ignore();
    std::cout << "Let's Play!" << std::endl
              << std::endl;

    // Initialise the tileBag and the board
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    tileBag = new TileBag(seed);
    board = new Board(MAX_ROW, MAX_COL);
    dict = new Dictionary();
    dict->add("corncob_caps.txt");

    // Filling up the players hands with 7 tiles
    for (int i = 0; i < playerCount; ++i)
    {
        drawFullHand(*playerVector[i]);
    }
    // Makes sure each player starts with enough tiles equal to the maximum hand
    // playersHaveEnoughTiles()
    // FIX ME IMPLEMENT METHOD HERE
    if (true)
    {
        // A method used to start the game
        if (!std::cin.eof())
        {
            playTheGame(playerCount);
        }
        else
        {
            std::cout << "\nGoodbye\n"
                      << std::endl;
        }
    }
}
int ValidateLoadFile(std::ifstream &ifs, std::string path)
{
    std::string line = "";
    while (!ifs.good() && !std::cin.eof())
    {
        std::cout << "File does not exist! Please enter an existing file's path" << std::endl;
        std::cin >> path;
        ifs.open("saves/" + path);
    }

    return 1; // dummy value
}

int getTileNumber(Letter letter)
{
    std::ifstream ifs;
    ifs.open("ScrabbleTiles.txt");
    std::string line;
    while (std::getline(ifs, line))
    {
        if (line[0] == letter)
        {
            return std::stoi(line.substr(2));
        }
    }
    return 0;
}

void GameEngine::LoadGame()
{
    std::string path = "";
    std::cout << "Enter the filename to load a game" << std::endl;
    std::cin >> path;
    std::string line = "";
    std::ifstream ifs;
    LinkedList hand1;
    LinkedList hand2;
    LinkedList hand3;
    LinkedList hand4;
    ifs.open("saves/" + path);
    ValidateLoadFile(ifs, path);
    std::getline(ifs, line);
    std::string c = std::string(1, line[0]);
    int count = std::stoi(c);
    //store players names
    std::string names[count];
    //store players scores
    int scores[count];
    std::vector<Player *> playerVector;
    TileBag *tileBag = new TileBag(0);
    Board *board = new Board(MAX_ROW, MAX_COL);

    int i = 0;
    int counter = 0;
    while (std::getline(ifs, line))
    {
        if (count == 2){
        //line 0 and 3 contain players names
        if (i == 0 || i == 3){
            names[counter] = line;
        }
        //lines 1 and 4 contain players scores
        else if (i == 1 || i == 4)
        {
            scores[counter] = std::stoi(line);
            counter++;
        }
        else if (i == 2)
        {
            //line 2 contains a player's hand
            int start = 0;
            std::string del = " ";
            int end = line.find(del);
            while (end != -1)
            {
                std::string token = line.substr(start, end - start);
                Tile *tile = new Tile(std::stoi(token.substr(token.find('-') + 1)), token[0]);
                hand1.add_back(tile);
                start = end + del.size();
                end = line.find(del, start);
            }
        }
          //line 5 contains a player's hand
        else if (i == 5)
        {
            int pointer = 0;
            for (int i = 0; i < (int)line.size(); ++i)
            {
                if (line[i] == ' ')
                {
                    int b = i - pointer;
                    hand2.add_back(new Tile(std::stoi(line.substr(pointer + 2, b)), line.substr(pointer, b)[0]));
                    pointer = i + 1;
                }
            }
        }
        //line 6 contains tiles placed on board and their coordinates
        else if (i == 6)
        {   if (line.length() != 0){
            Tile *tile;
            int start = 0;
            char numtoletter[LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                                    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                                    'X', 'Y', 'Z'};
            std::string del = " ";
            int row = 0;
            int col = 0;
            int end = line.find(del);
            std::string token = "";
            while (end != -1)
            {
                row = 0;
                col = 0;
                token = line.substr(start, end - start);
                tile = new Tile(getTileNumber(token[0]), token[0]);

                for (int i = 0; i < LETTERS; ++i)
                {
                    if (token[token.find('@') + 1] == numtoletter[i])
                    {
                        row = i;
                    }
                }
                col = std::stoi(token.substr(token.find('@') + 2));
                board->insert(tile, row, col);

                start = end + del.size();
                end = line.find(del, start);
            }
        }
            /* token = line.substr(start);
            tile = new Tile(getTileNumber(token[0]), token[0]);
            row = 0;
            col = 0;
            for (int i = 0; i < 26; ++i)
            {
                if (token[token.find('@') + 1] == numtoletter[i])
                {
                    row = i;
                }
            }
            col = std::stoi(token.substr(token.find('@') + 2));
            board->insert(tile, row, col); */
        }
        //line 7 has the tiles in a tilebag
        else if (i == 7)
        {
            int start = 0;
            std::string del = " ";
            int end = line.find(del);
            while (end != -1)
            {
                std::string token = line.substr(start, end - start);
                tileBag->add(*(new Tile(std::stoi(token.substr(token.find('-') + 1)), token[0])));
                start = end + del.size();
                end = line.find(del, start);
            }
        }
        //line 8 contains the current player's turn
        else if (i == 8)
        {
            //if current player's name is the first in the names array
            if (line == names[0])
            {
                //add it first to the player's vector so that game resumes on their turn
                playerVector.push_back(new Player(names[0]));
                playerVector[0]->setScore(scores[0]);
                playerVector.push_back(new Player(names[1]));
                playerVector[1]->setScore(scores[1]);
                //add tiles to players hands
                for (int i = 0; i < hand1.size(); ++i)
                {
                    playerVector[0]->addToHand(*(hand1.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[1]->addToHand(*(hand2.get(i)));
                }
            }
            else
            {
                playerVector.push_back(new Player(names[1]));
                playerVector[0]->setScore(scores[1]);
                playerVector.push_back(new Player(names[0]));
                playerVector[1]->setScore(scores[0]);
                for (int i = 0; i < hand1.size(); ++i)
                {
                    playerVector[1]->addToHand(*(hand1.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[0]->addToHand(*(hand2.get(i)));
                }
            }
        }

        i++;
        }

        else if (count == 3){
        //line 0 and 3 contain players names
        if (i == 0 || i == 3 || i == 6){
            names[counter] = line;
        }
        //lines 1 and 4 contain players scores
        else if (i == 1 || i == 4 || i == 7)
        {
            scores[counter] = std::stoi(line);
            counter++;
        }
        else if (i == 2)
        {
            //line 2 contains a player's hand
            int start = 0;
            std::string del = " ";
            int end = line.find(del);
            while (end != -1)
            {
                std::string token = line.substr(start, end - start);
                Tile *tile = new Tile(std::stoi(token.substr(token.find('-') + 1)), token[0]);
                hand1.add_back(tile);
                start = end + del.size();
                end = line.find(del, start);
            }
        }
          //line 5 contains a player's hand
        else if (i == 5)
        {
            int pointer = 0;
            for (int i = 0; i < (int)line.size(); ++i)
            {
                if (line[i] == ' ')
                {
                    int b = i - pointer;
                    hand2.add_back(new Tile(std::stoi(line.substr(pointer + 2, b)), line.substr(pointer, b)[0]));
                    pointer = i + 1;
                }
            }
        }
        else if (i == 8)
        {
            int pointer = 0;
            for (int i = 0; i < (int)line.size(); ++i)
            {
                if (line[i] == ' ')
                {
                    int b = i - pointer;
                    hand3.add_back(new Tile(std::stoi(line.substr(pointer + 2, b)), line.substr(pointer, b)[0]));
                    pointer = i + 1;
                }
            }
        }

        //line 6 contains tiles placed on board and their coordinates
        else if (i == 9)
        {   if (line.length() != 0){
            Tile *tile;
            int start = 0;
            char numtoletter[LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                                    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                                    'X', 'Y', 'Z'};
            std::string del = " ";
            int row = 0;
            int col = 0;
            int end = line.find(del);
            std::string token = "";
            while (end != -1)
            {
                row = 0;
                col = 0;
                token = line.substr(start, end - start);
                tile = new Tile(getTileNumber(token[0]), token[0]);

                for (int i = 0; i < LETTERS; ++i)
                {
                    if (token[token.find('@') + 1] == numtoletter[i])
                    {
                        row = i;
                    }
                }
                col = std::stoi(token.substr(token.find('@') + 2));
                board->insert(tile, row, col);

                start = end + del.size();
                end = line.find(del, start);
            }
        }
            /* token = line.substr(start);
            tile = new Tile(getTileNumber(token[0]), token[0]);
            row = 0;
            col = 0;
            for (int i = 0; i < 26; ++i)
            {
                if (token[token.find('@') + 1] == numtoletter[i])
                {
                    row = i;
                }
            }
            col = std::stoi(token.substr(token.find('@') + 2));
            board->insert(tile, row, col); */
        }
        //line 7 has the tiles in a tilebag
        else if (i == 10)
        {
            int start = 0;
            std::string del = " ";
            int end = line.find(del);
            while (end != -1)
            {
                std::string token = line.substr(start, end - start);
                tileBag->add(*(new Tile(std::stoi(token.substr(token.find('-') + 1)), token[0])));
                start = end + del.size();
                end = line.find(del, start);
            }
        }
        //line 8 contains the current player's turn
        else if (i == 11)
        {
            //if current player's name is the first in the names array
            if (line == names[0])
            {
                //add it first to the player's vector so that game resumes on their turn
                playerVector.push_back(new Player(names[0]));
                playerVector[0]->setScore(scores[0]);
                playerVector.push_back(new Player(names[1]));
                playerVector[1]->setScore(scores[1]);
                playerVector.push_back(new Player(names[2]));
                playerVector[2]->setScore(scores[2]);
                //add tiles to players hands
                for (int i = 0; i < hand1.size(); ++i)
                {
                    playerVector[0]->addToHand(*(hand1.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[1]->addToHand(*(hand2.get(i)));
                }
                for (int i = 0; i < hand3.size(); ++i)
                {
                    playerVector[2]->addToHand(*(hand3.get(i)));
                }
            }
            else if (line == names[1])
            {
                playerVector.push_back(new Player(names[1]));
                playerVector[0]->setScore(scores[1]);
                playerVector.push_back(new Player(names[0]));
                playerVector[1]->setScore(scores[0]);
                playerVector.push_back(new Player(names[2]));
                playerVector[2]->setScore(scores[2]);
                for (int i = 0; i < hand1.size(); ++i)
                {
                    playerVector[1]->addToHand(*(hand1.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[0]->addToHand(*(hand2.get(i)));
                }
                for (int i = 0; i < hand3.size(); ++i)
                {
                    playerVector[2]->addToHand(*(hand3.get(i)));
                }
            }
            else{
                playerVector.push_back(new Player(names[2]));
                playerVector[0]->setScore(scores[2]);
                playerVector.push_back(new Player(names[1]));
                playerVector[1]->setScore(scores[1]);
                playerVector.push_back(new Player(names[0]));
                playerVector[2]->setScore(scores[0]);
                for (int i = 0; i < hand1.size(); ++i)
                {
                    playerVector[0]->addToHand(*(hand3.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[2]->addToHand(*(hand1.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[1]->addToHand(*(hand2.get(i)));
                }
            }
        }

        i++;
        }
        else if (count == 4){
        //line 0 and 3 contain players names
        if (i == 0 || i == 3 || i == 6 || i == 9){
            names[counter] = line;
        }
        //lines 1 and 4 contain players scores
        else if (i == 1 || i == 4 || i == 7 || i ==10)
        {
            scores[counter] = std::stoi(line);
            counter++;
        }
        else if (i == 2)
        {
            //line 2 contains a player's hand
            int start = 0;
            std::string del = " ";
            int end = line.find(del);
            while (end != -1)
            {
                std::string token = line.substr(start, end - start);
                Tile *tile = new Tile(std::stoi(token.substr(token.find('-') + 1)), token[0]);
                hand1.add_back(tile);
                start = end + del.size();
                end = line.find(del, start);
            }
        }
          //line 5 contains a player's hand
        else if (i == 5)
        {
            int pointer = 0;
            for (int i = 0; i < (int)line.size(); ++i)
            {
                if (line[i] == ' ')
                {
                    int b = i - pointer;
                    hand2.add_back(new Tile(std::stoi(line.substr(pointer + 2, b)), line.substr(pointer, b)[0]));
                    pointer = i + 1;
                }
            }
        }
        else if (i == 8)
        {
            int pointer = 0;
            for (int i = 0; i < (int)line.size(); ++i)
            {
                if (line[i] == ' ')
                {
                    int b = i - pointer;
                    hand3.add_back(new Tile(std::stoi(line.substr(pointer + 2, b)), line.substr(pointer, b)[0]));
                    pointer = i + 1;
                }
            }
        }
        else if (i == 11)
        {
            int pointer = 0;
            for (int i = 0; i < (int)line.size(); ++i)
            {
                if (line[i] == ' ')
                {
                    int b = i - pointer;
                    hand4.add_back(new Tile(std::stoi(line.substr(pointer + 2, b)), line.substr(pointer, b)[0]));
                    pointer = i + 1;
                }
            }
        }

        //line 6 contains tiles placed on board and their coordinates
        else if (i == 12)
        {   if (line.length() != 0){
            Tile *tile;
            int start = 0;
            char numtoletter[LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                                    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                                    'X', 'Y', 'Z'};
            std::string del = " ";
            int row = 0;
            int col = 0;
            int end = line.find(del);
            std::string token = "";
            while (end != -1)
            {
                row = 0;
                col = 0;
                token = line.substr(start, end - start);
                tile = new Tile(getTileNumber(token[0]), token[0]);

                for (int i = 0; i < LETTERS; ++i)
                {
                    if (token[token.find('@') + 1] == numtoletter[i])
                    {
                        row = i;
                    }
                }
                col = std::stoi(token.substr(token.find('@') + 2));
                board->insert(tile, row, col);

                start = end + del.size();
                end = line.find(del, start);
            }
        }
        }

        else if (i == 13)
        {
            int start = 0;
            std::string del = " ";
            int end = line.find(del);
            while (end != -1)
            {
                std::string token = line.substr(start, end - start);
                tileBag->add(*(new Tile(std::stoi(token.substr(token.find('-') + 1)), token[0])));
                start = end + del.size();
                end = line.find(del, start);
            }
        }

        else if (i == 14)
        {
            //if current player's name is the first in the names array
            if (line == names[0])
            {
                //add it first to the player's vector so that game resumes on their turn
                playerVector.push_back(new Player(names[0]));
                playerVector[0]->setScore(scores[0]);
                playerVector.push_back(new Player(names[1]));
                playerVector[1]->setScore(scores[1]);
                playerVector.push_back(new Player(names[2]));
                playerVector[2]->setScore(scores[2]);
                playerVector.push_back(new Player(names[3]));
                playerVector[3]->setScore(scores[3]);
                //add tiles to players hands
                for (int i = 0; i < hand1.size(); ++i)
                {
                    playerVector[0]->addToHand(*(hand1.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[1]->addToHand(*(hand2.get(i)));
                }
                for (int i = 0; i < hand3.size(); ++i)
                {
                    playerVector[2]->addToHand(*(hand3.get(i)));
                }
                for (int i = 0; i < hand4.size(); ++i)
                {
                    playerVector[3]->addToHand(*(hand4.get(i)));
                }
            }
            else if (line == names[1])
            {
                playerVector.push_back(new Player(names[1]));
                playerVector[0]->setScore(scores[1]);
                playerVector.push_back(new Player(names[0]));
                playerVector[1]->setScore(scores[0]);
                playerVector.push_back(new Player(names[2]));
                playerVector[2]->setScore(scores[2]);
                playerVector.push_back(new Player(names[3]));
                playerVector[3]->setScore(scores[3]);
                for (int i = 0; i < hand1.size(); ++i)
                {
                    playerVector[1]->addToHand(*(hand1.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[0]->addToHand(*(hand2.get(i)));
                }
                for (int i = 0; i < hand3.size(); ++i)
                {
                    playerVector[2]->addToHand(*(hand3.get(i)));
                }
                for (int i = 0; i < hand4.size(); ++i)
                {
                    playerVector[3]->addToHand(*(hand4.get(i)));
                }
            }
            else if (line == names[2]){
                playerVector.push_back(new Player(names[2]));
                playerVector[0]->setScore(scores[2]);
                playerVector.push_back(new Player(names[1]));
                playerVector[1]->setScore(scores[1]);
                playerVector.push_back(new Player(names[0]));
                playerVector[2]->setScore(scores[0]);
                playerVector.push_back(new Player(names[3]));
                playerVector[3]->setScore(scores[3]);
                for (int i = 0; i < hand3.size(); ++i)
                {
                    playerVector[0]->addToHand(*(hand3.get(i)));
                }
                for (int i = 0; i < hand1.size(); ++i)
                {
                    playerVector[2]->addToHand(*(hand1.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[1]->addToHand(*(hand2.get(i)));
                }
                for (int i = 0; i < hand4.size(); ++i)
                {
                    playerVector[3]->addToHand(*(hand4.get(i)));
                }
            }
                else {
                playerVector.push_back(new Player(names[3]));
                playerVector[0]->setScore(scores[3]);
                playerVector.push_back(new Player(names[2]));
                playerVector[1]->setScore(scores[2]);
                playerVector.push_back(new Player(names[1]));
                playerVector[2]->setScore(scores[1]);
                playerVector.push_back(new Player(names[0]));
                playerVector[3]->setScore(scores[0]);
                for (int i = 0; i < hand4.size(); ++i)
                {
                    playerVector[0]->addToHand(*(hand4.get(i)));
                }
                for (int i = 0; i < hand3.size(); ++i)
                {
                    playerVector[1]->addToHand(*(hand3.get(i)));
                }
                for (int i = 0; i < hand1.size(); ++i)
                {
                    playerVector[3]->addToHand(*(hand1.get(i)));
                }
                for (int i = 0; i < hand2.size(); ++i)
                {
                    playerVector[2]->addToHand(*(hand2.get(i)));
                }
            }
        }

        i++;
        }
    }
    this->playerVector = playerVector;
    this->tileBag = tileBag;
    this->board = board;
    dict = new Dictionary();
    dict->add("corncob_caps.txt");

    playTheGame(count);
}

bool GameEngine::validateName(const std::string name) const
{
    bool flag = true;
    char notAllowed[] = "qwertyuiopasdfghjklzxcvbnm1234567890!@#$%^&*()`~-_=+[{]};:<,>.?/|'";

    // Checks if the player entered doesn't already exist
    /* for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (playerVector[i]->getName() != "") {
                if (playerVector[i]->getName() == (std::string(name))) {
                    flag = false;
                }
        }
    }   */
    /* Looping through the name and notAllowed character arrays to
     * find if they match
     */
    for (int i = 0; (name[i] != '\0'); ++i)
    {
        for (int j = 0; (notAllowed[j] != '\0'); ++j)
        {
            if (name[i] == notAllowed[j])
            {
                flag = false;
            }
        }
    }
    return flag;
}

// Refills the player's hand by drawing a tile from the tile bag
void GameEngine::drawFullHand(Player &player)
{
    while (player.getHand()->size() < MAX_HAND)
    {
        if (tileBag->getSize() > 0)
        {
            player.addToHand(*tileBag->pop());
        }
    }
}
bool GameEngine::playRound(int counter)
{
    // Basic output for starting round
    std::cout << playerVector[counter]->getName() << ", it's your turn" << std::endl;
    std::cout << "Score for " << playerVector[counter]->getName() << ": " << playerVector[counter]->getScore() << std::endl;

    //Output scores for all players
    for (int i = 0; i < int(playerVector.size()); ++i){
        if (i != counter){
            std::cout << "Score for " << playerVector[i]->getName() << ": " << playerVector[i]->getScore() << std::endl;
        }
    }

    board->printBoard();

    std::cout << std::endl;

    // display current hand
    std::cout << "Your hand is" << std::endl;

    for (int i = 0; i < playerVector[counter]->getHand()->size(); ++i)
    {
        if (i != playerVector[counter]->getHand()->size() - 1)
        {
            LinkedList *li = playerVector[counter]->getHand();
            std::cout << li->get(i)->getLetter() << "-" << li->get(i)->getValue() << ", ";
        }
        else
        {
            LinkedList *li = playerVector[counter]->getHand();
            std::cout << li->get(i)->getLetter() << "-" << li->get(i)->getValue() << std::endl;
        }
    }

    std::string choice = "";
    char numtoletter[LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
                            'X', 'Y', 'Z'};
    int count = 0;
    bool validation = false;
    // placement loop
    int boardcheck = board->getNumberOfTilesOnBoard();

    

    while (validation == false){
    std::vector<int> rowplacement;
    std::vector<int> colplacement; 
    choice = "";
    //placement loop
    while (choice != DONE){
        std::string line = "";
        // std::cin.ignore();
        std::getline(std::cin, line);
        //terminate if EOF
        if(std::cin.eof()){
           return true;
       }
        const char delim = ' ';
        std::vector<std::string> splitline;

        int pointer = 0;

        for (int i = 0; i < (int)line.length(); ++i)
        {
            
            if (char(line[i]) == delim)
            {
                int b = i - pointer;
                splitline.push_back(line.substr(pointer, (b)));
                pointer = i + 1;
            }
        }
        
       
        splitline.push_back(line.substr(pointer, (line.size()-pointer)));
        
        if(splitline[0] == PLACE) {
            choice = splitline[1];
            if(splitline[1] == DONE){
            choice = DONE;
            validation = true;
        }
        }
        
        
        else if(splitline[0] == REPLACE) {
            std::string tileToReplace = splitline[1];

            bool inHand = false;

            int index = 0;
            for (int i = 0; i < playerVector[counter]->getHand()->size(); ++i){
                if (playerVector[counter]->getHand()->get(i)->getLetter() == tileToReplace[0]){
                    inHand = true;
                    index = i+1;
                }
            }
            if (inHand){
                playerVector[counter]->getHand()->remove(index);
            }
            validation = true;
            choice = DONE;
        }
        else if(splitline[0] == PASS) {
            choice = DONE;
            validation = true;
        }
        else if(splitline[0] == SAVE) {
            std::string fileName = "unnamed_save_file.txt";

            fileName = splitline[1] + SAVE_EXTENSION;
            createSaveFile(fileName, playerVector, board, tileBag, counter);
        }
        else if(splitline[0] == EXIT) {
            // gameOverPrint();
            return true;
            validation = true;
        }
        else if(splitline[0] == HELP){
            std::cout << "---------------------------------------------------------" << std::endl;
            std::cout << "Place tile: \"place <tile e.g A> at <coordinate e.g C2>\"" << std::endl;
            std::cout << "Finish placing tiles: \"place Done\"" << std::endl;
            std::cout << "Replace tile: \"replace <tile e.g C>\"" << std::endl;
            std::cout << "Exit game: \"exit\"" << std::endl;
            std::cout << "Save game: \"save <filename>\"" << std::endl;
            std::cout << "Pass turn: \"pass>\"" << std::endl;
            std::cout << "---------------------------------------------------------" << std::endl;
        }
        else{
            std::cout << "Invalid input" << std::endl;
        }
        
        //if done isn't chosen start the placement process
        if (choice != DONE){
            if (splitline.size() == 4){

                bool inHand = false;
                Tile *tile = nullptr;
                int index = 0;
                for (int i = 0; i < playerVector[counter]->getHand()->size(); ++i)
                {
                    if (playerVector[counter]->getHand()->get(i)->getLetter() == choice[0])
                    {
                        inHand = true;
                        index = i+1;
                        tile = playerVector[counter]->getHand()->get(i);
                    }
                }
                if (inHand)
                {
                    int row = 0;
                    bool uppercase = false;
                    for (int i = 0; i < LETTERS; ++i)
                    {
                        if (char(splitline[3][0]) == numtoletter[i])
                        {
                            row = i;
                            uppercase = true;
                        }
                    }
                    if (uppercase == false){
                        std::cout << "Invalid input" << std::endl;
                    }
                    else{
                    // Join the last two numbers and convert them to an integer
                    if (splitline[3].size() == 1){
                        std::cout << "Invalid input" << std::endl;    
                    }
                    else{
                    std::string column = std::string(1, splitline[3][1]) + splitline[3][2];

                    int col = std::stoi(column);

                    bool check = board->insert(tile, row, col);
                    rowplacement.push_back(row);
                    colplacement.push_back(col);
                    if (check){
                    // playerVector[counter]->addScore(tile->getValue());
                    playerVector[counter]->getHand()->remove(index);
                    }
                    else{
                        std::cout << "Incorrect placement" << "\n";
                    }
                    tile = nullptr;
                    count += 1;
                    }
                    }
                }
            }
        }
    }
    ///0 for horizontal, 1 for vertical, 2 for invalid, 3 if it is single tile placed
    if (count > 0){
    int orientation = validatePlacement(rowplacement, colplacement);

    
    //invalid Input
    if (orientation == 2){
        std::cout << "Invalid input, tiles must be horizontal or vertically placed" << std::endl;
        for (int i = 0; i < int(rowplacement.size()); ++i){
            playerVector[counter]->addToHand(*board->get(rowplacement[i], colplacement[i]));
            board->removeTile(rowplacement[i], colplacement[i]);
        }
        validation = false;
    }
    else if (orientation == 4){
        std::cout << "Invalid input, tiles must have interlinking tiles! Cannot be isolated" << std::endl;
        for (int i = 0; i < int(rowplacement.size()); ++i){
            playerVector[counter]->addToHand(*board->get(rowplacement[i], colplacement[i]));
            board->removeTile(rowplacement[i], colplacement[i]);
        }
        validation = false;
    }
    //Valid input/orientation
    else{
        bool result = scoring(rowplacement, colplacement, playerVector[counter], orientation, boardcheck);
        if (result){
        validation = true;
        }
        else {
        std::cout << "Invalid Word or Input" << std::endl;
        std::cout << "Place a valid english word and ensure it has an adjacent tile" <<std::endl;
        for (int i = 0; i < int(rowplacement.size()); ++i){
            playerVector[counter]->addToHand(*board->get(rowplacement[i], colplacement[i]));
            board->removeTile(rowplacement[i], colplacement[i]);
        }
        validation = false;
        }
    }
    }

    }

    if (count >= 7){
        std::cout << "BINGO!!!" << std::endl;
        std::cout << std::endl;
        playerVector[counter]->addScore(50);
    }
    // refill hand after loop has been completed
    drawFullHand(*playerVector[counter]);

    return false;
}

bool GameEngine::scoring(std::vector<int> rowplacement, std::vector<int>colplacement, Player* player, int orientation, int boardcheck){
    
    std::vector<std::vector<Tile*> > words;
    //Horizontal placement
    if (orientation == 0){
        int count = -1;
        Tile* tile = nullptr;
        tile = board->get(rowplacement[0], colplacement[0]+count);
        if (tile!=nullptr){
            while (tile != nullptr){
                --count;
                tile = board->get(rowplacement[0], colplacement[0]+count);
            }
            ++count;
            std::vector<Tile*> word;            
            tile = board->get(rowplacement[0], colplacement[0]+count);
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[0], colplacement[0]+count);
            }
            words.push_back(word);
        }
        else{
            ++count;
            tile = board->get(rowplacement[0], colplacement[0]+count);
            std::vector<Tile*> word;
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[0], colplacement[0]+count);
            }
            words.push_back(word);            
        }
    //Loop vertical options for each tile
    for (int i = 0; i < int(rowplacement.size()); ++i){
        int count = -1;
        Tile* tile = nullptr;
        tile = board->get(rowplacement[i]+count, colplacement[i]);
        if (tile!=nullptr){
            while (tile != nullptr){
                --count;
                tile = board->get(rowplacement[i]+count, colplacement[i]);
            }
            ++count;
            std::vector<Tile*> word;            
            tile = board->get(rowplacement[i]+count, colplacement[i]);
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[i]+count, colplacement[i]);
            }
            words.push_back(word);
        }
        else{
            ++count;
            tile = board->get(rowplacement[i]+count, colplacement[i]);
            std::vector<Tile*> word;
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[i]+count, colplacement[i]);
            }
            words.push_back(word);            
    }
    }
    int scoretracker = 0;
    int tiletotal = 0;
    //If words on board
    if (boardcheck > 0){
        for (int i = 0; i < int(words.size()); ++i){
            for (int j = 0; j < int(words[i].size()); ++j){
                if (int(words[i].size()) != 1){
                    scoretracker += words[i][j]->getValue();
                }
            }
        }
    //Calculate the total value of tiles placed
    for (int i = 0; i < int(rowplacement.size()); ++i){
            tiletotal += board->get(rowplacement[i], colplacement[i])->getValue();
        }
    //If tiletotal, value of each tile placed is the same as the score added
    //Then tiles placed are not adjacent to any other
    //Score is null and placement must be reattempted
    bool wordValidation = validateWords(words);

    if (wordValidation==false){
        return false;
    }
    if (tiletotal == scoretracker){
        return false;
    }
    else {
        player->addScore(scoretracker);
        return true;
    }
    }
    //Else just take score of tiles placed 
    else{
    bool wordValidation = validateWords(words);

    if (wordValidation==false){
        return false;
    }
        for (int i = 0; i < int(words[0].size()); ++i){
            player->addScore(words[0][i]->getValue());
        }
        return true;
    }
    }


    //Vertical placement
    else if (orientation == 1){
        int count = -1;
        Tile* tile = nullptr;
        tile = board->get(rowplacement[0]+count, colplacement[0]);
        if (tile!=nullptr){
            while (tile != nullptr){
                --count;
                tile = board->get(rowplacement[0]+count, colplacement[0]);
            }
            ++count;
            std::vector<Tile*> word;            
            tile = board->get(rowplacement[0]+count, colplacement[0]);
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[0]+count, colplacement[0]);
            }
            words.push_back(word);
        }
        else{
            ++count;
            tile = board->get(rowplacement[0]+count, colplacement[0]);
            std::vector<Tile*> word;
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[0]+count, colplacement[0]);
            }
            words.push_back(word);            
    }
    //Horizontal search loop
    for (int i = 0; i < int(rowplacement.size()); ++i){
        int count = -1;
        Tile* tile = nullptr;
        tile = board->get(rowplacement[i], colplacement[i]+count);
        if (tile!=nullptr){
            while (tile != nullptr){
                --count;
                tile = board->get(rowplacement[i], colplacement[i]+count);
            }
            ++count;
            std::vector<Tile*> word;            
            tile = board->get(rowplacement[i], colplacement[i]+count);
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[i], colplacement[i]+count);
            }
            words.push_back(word);
        }
        else{
            ++count;
            tile = board->get(rowplacement[i], colplacement[i]+count);
            std::vector<Tile*> word;
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[i], colplacement[i]+count);
            }
            words.push_back(word);            
        }
    }
    //if tiles on board
    int scoretracker = 0;
    int tiletotal = 0;
    if (boardcheck > 0){
        for (int i = 0; i < int(words.size()); ++i){
            for (int j = 0; j < int(words[i].size()); ++j){
                    if (int(words[i].size()) != 1){
                    scoretracker += words[i][j]->getValue();
                    }
            }
        }
    //Calculate the total value of tiles placed
    for (int i = 0; i < int(rowplacement.size()); ++i){
            tiletotal += board->get(rowplacement[i], colplacement[i])->getValue();
        }
    //If tiletotal, value of each tile placed is the same as the score added
    //Then tiles placed are not adjacent to any other
    //Score is null and placement must be reattempted

    bool wordValidation = validateWords(words);

    if (wordValidation==false){
        return false;
    }
    if (tiletotal == scoretracker){
        return false;
    }
    else {
        player->addScore(scoretracker);
        return true;
    }
    }
    //Else just take score of tiles placed 
    else{
    bool wordValidation = validateWords(words);

    if (wordValidation==false){
        return false;
    }
        for (int i = 0; i < int(words[0].size()); ++i){
            player->addScore(words[0][i]->getValue());
        }
    }
    return true;
    }


    //Single tile
    else {
        int count = -1;
        Tile* tile = nullptr;
        tile = board->get(rowplacement[0], colplacement[0]+count);
        if (tile!=nullptr){
            while (tile != nullptr){
                --count;
                tile = board->get(rowplacement[0], colplacement[0]+count);
            }
            ++count;
            std::vector<Tile*> word;            
            tile = board->get(rowplacement[0], colplacement[0]+count);
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[0], colplacement[0]+count);
            }
            words.push_back(word);
        }
        else{
            ++count;
            tile = board->get(rowplacement[0], colplacement[0]+count);
            std::vector<Tile*> word;
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[0], colplacement[0]+count);
            }
            words.push_back(word);            
        }
        count = -1;
        tile = nullptr;
        tile = board->get(rowplacement[0]+count, colplacement[0]);
        if (tile!=nullptr){
            while (tile != nullptr){
                --count;
                tile = board->get(rowplacement[0]+count, colplacement[0]);
            }
            ++count;
            std::vector<Tile*> word;            
            tile = board->get(rowplacement[0]+count, colplacement[0]);
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[0]+count, colplacement[0]);
            }
            words.push_back(word);
        }
        else{
            ++count;
            tile = board->get(rowplacement[0]+count, colplacement[0]);
            std::vector<Tile*> word;
            while (tile!= nullptr){
                ++count;
                word.push_back(tile);
                tile = board->get(rowplacement[0]+count, colplacement[0]);
            }
            words.push_back(word);            
    }
    //CALCULATE SCORING IF, WORDS[I].SIZE == 1, unless both are equal to 1
    //if num tiles on board = 0, and size == 1 overall. return and say that tile must be placed adjacent
    if (boardcheck > 0){
        //if single tile has been placed and there is nothing adjacent, despite tiles on the board. Return false and request input
        if (int(words[0].size()) == 1 && int(words[1].size()) == 1){
            return false;
        }
        else{
        //calculate score for words greater than 1
        for (int i = 0; i < int(words.size()); ++i){
            for (int j = 0; j < int(words[i].size()); ++j){
                    if (int(words[i].size()) != 1){
                    player->addScore(words[i][j]->getValue());
                    }
            }
        }
        bool wordValidation = validateWords(words);

    if (wordValidation==false){
        return false;
        }
    else{
        return true;
    }
    }
    }
    else {
        bool wordValidation = validateWords(words);
        if (wordValidation==false){
        return false;
        }
        else{
        //If nothing on board, just calculate the value of tile
        player->addScore(words[0][0]->getValue());
        return true;
        }
    }

    }
}

bool GameEngine::validateWords(std::vector<std::vector<Tile*> > words){
    std::vector<std::string> strWord; 
    for (int i = 0; i < int(words.size()); ++i){
        std::string word = "";
        for (int j = 0; j < int(words[i].size()); ++j){
            word += words[i][j]->getLetter();
        }
        strWord.push_back(word);
    }

    for (int i = 0; i < int(strWord.size()); ++i){
        if (strWord[i].size() > 1){
            std::cout << strWord[i] <<std::endl;
            if (dict->get(strWord[i])==false){
                return false;
            }
        }

    }
    return true;
}

int GameEngine::validatePlacement(std::vector<int> rowplacement, std::vector<int>colplacement){
    bool rowcheck = true;
    bool colcheck = true;
    int returnVal = 2;
    //check to see if it is vertical
    for (int i = 0; i < int(rowplacement.size()); ++i){
        if (rowplacement[0] != rowplacement[i]){
            rowcheck = false;
        }
    }
    //check to see if it is horizontal
    for (int i = 0; i < int(colplacement.size()); ++i){
        if (colplacement[0] != colplacement[i]){
            colcheck = false;
        }
    }
    
    //Ensure that there isn't a stray tile placement. E.G |A|?|B|C| 
    bool stray = false;
    if (board->getNumberOfTilesOnBoard() != 1 && int(rowplacement.size()) != 1){
    int checker = 1;
    
    for (int i = 0; i < int(rowplacement.size()); ++i){
        if (board->get(rowplacement[i]+checker, colplacement[i]) == nullptr){
            if (board->get(rowplacement[i]-checker, colplacement[i]) == nullptr){
                if (board->get(rowplacement[i], colplacement[i]+checker) == nullptr){
                    if (board->get(rowplacement[i], colplacement[i]-checker) == nullptr){
                        stray = true;
            }
            }
            }
        }
    }
    }

    //check results of above loop
    if (stray == true) {
        returnVal = 4;
    }
    //Vertical
    else if (rowcheck == true && colcheck ==false){
        returnVal = 0;
    }    
    //Horizontal
    else if (rowcheck == false && colcheck ==true){
        returnVal = 1;
    }    
    //If only one tile is played
    else if (rowcheck == true && colcheck == true){
        returnVal = 3;
    }
    //Invalid input
    else {
        returnVal = 2;
    }

    return returnVal;    
}

void GameEngine::playTheGame(int playerCount)
{
    bool gameOver = false;
    /*
     * First turn is kept track because on the first turn,
     * there will be no tile validation for nearby tiles.
     * They are free to place it anywhere on the board as long as it
     * is within the board's confines
     */

    firstTurn = false;
    if (board->getNumberOfTilesOnBoard() == 0)
    {
        firstTurn = true;
    }
    bool quit = false;

    // Initates game loop
    int counter = 0;
    while (!gameOver && !quit && !std::cin.eof())
    {
        // FIX ME: IF (playerTurns[counter] == true)
        gameOver = playRound(counter);
        // End of game condition
        if (playerNoLongerHasTiles())
        {
            gameOver = true;
        }

        ++counter;

        // Resets counter after the last player's turn
        if (counter >= playerCount)
        {
            counter = 0;
        }

        // If user prematurely quits the game
        if (quit)
        {
            std::cout << "Goodbye\n"
                      << std::endl;
        }

        // Game over statements
        if (gameOver)
        {
            // createSaveFile(playerVector[0], playerVector[1], board, tileBag, counter);
            gameOverPrint();
            delete board;
            delete tileBag;
            delete dict;
            for (int i = 0; i < int(playerVector.size()); ++i){
                delete playerVector[i];
            }
        }
    }
}

// Helper method checking if players have 0 tiles in their hand
bool GameEngine::playerNoLongerHasTiles()
{
    bool playerNoLongerHasTiles = false;
    for (int i = 0; i < int(playerVector.size()); ++i)
    {
        if (playerVector[i]->getHand()->size() == 0)
        {
            playerNoLongerHasTiles = true;
        }
    }

    return playerNoLongerHasTiles;
}

void GameEngine::gameOverPrint() const
{
    std::cout << "Game over" << std::endl;

    for (int i = 0; i < int(playerVector.size()); ++i)
    {
        std::cout << "Score for " << playerVector[i]->getName() << " : " << playerVector[i]->getScore() << std::endl;
    }

    // Keeping track of all the points of players
    int pointsArray[int(playerVector.size())];
    for (int i = 0; i < int(playerVector.size()); ++i)
    {
        pointsArray[i] = playerVector[i]->getScore();
    }

    // Find the highest score
    int highestScore = -1;
    int winningPlayer = -1;
    for (int i = 0; i < int(playerVector.size()); ++i)
    {
        if (pointsArray[i] > highestScore)
        {
            highestScore = pointsArray[i];
            winningPlayer = i;
        }
    }

    // Determining if a draw has occurred where more than one player has the highest score
    bool draw = false;
    for (int i = 0; i < 2; ++i)
    {
        if (highestScore == pointsArray[i] && i != winningPlayer)
        {
            draw = true;
        }
    }

    if (!draw)
    {
        std::cout << "Player " << playerVector[winningPlayer]->getName() << " won the game!" << std::endl;
    }
    else
    {
        std::cout << "DRAW! No one wins!" << std::endl;
    }

    std::cout << "\nGoodbye\n"
              << std::endl;
}


bool GameEngine::createSaveFile(std::string fileName, std::vector<Player*> playerVector, Board* board, TileBag* tilebag, int counter){
    std::cout << "Saving Game..." << std::endl;

   std::ofstream file("saves/" + fileName);
   file << int(playerVector.size()) << std::endl;

   //add player 1 name, score and hand to savefile
   for (int i = 0; i < int(playerVector.size()); ++i){
   std::cout << "Saving player " << i+1 << "..." << std::endl;
   file << playerVector[i]->getName() << std::endl;
   file << playerVector[i]->getScore() << std::endl;
   for (int j = 0; j < playerVector[i]->getHand()->size(); ++j){
      file << playerVector[i]->getHand()->get(j)->getLetter() << "-" << playerVector[i]->getHand()->get(j)->getValue() << " ";
   }
   file << std::endl;
   }
   
   //adds all tile coordinates
   std::cout << "Saving Tiles on Board..." << std::endl;
   std::vector<std::string> tilesOnBoard = board->getAllTilesOnBoard();

   for (int i = 0; i < int(tilesOnBoard.size()); ++i){
      file << tilesOnBoard[i] << " ";
   }

   file << std::endl;

   //add tilebag contents
   std::cout << "Saving TileBag..." << std::endl;
   for (int i = 0; i < tilebag->getSize(); ++i){
      file << tilebag->get(i)->getLetter() << "-"  << tilebag->get(i)->getValue() << " ";
   }
   file << std::endl;
   //add current player name
   std::cout << "Saving current players turn..." << std::endl;
    file << playerVector[counter]->getName() << std::endl;

   std::cout << "Save Complete" << std::endl;
   return true;
}
void GameEngine::replaceHandTile(Player &player, const char character)
{
    // Add back to the tile bag
    // player.
}
