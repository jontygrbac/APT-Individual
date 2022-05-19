
#include "LinkedList.h"
#include "GameEngine.h"
#include "Player.h"
#include "Board.h"
#include "TileBag.h"
#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#define EXIT_SUCCESS 0

void menu();
int ValidateLoadFile(std::ifstream &ifs, std::string path);
void ShowCredits();
bool ValidateName(std::string &name);
int getTileNumber(Letter letter);
int main(void)
{
   menu();
   return EXIT_SUCCESS;
}

void menu()
{
   bool valid = true;
   do
   {
      std::cout << "Welcome to Scrabble!" << std::endl;
      std::cout << "------------------" << std::endl;
      char choice = '1';
      std::string name_p1 = "";
      std::string name_p2 = "";
      
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load Game" << std::endl;
      std::cout << "3. Credits (Show student information)" << std::endl;
      std::cout << "4. Quit" << std::endl;
      std::cout << "> "; 
      std::cin >> choice;

      if (choice >= '1' && choice <= '4')
      {

         if (choice == '1')
         {
            std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
            gameEngine->newGame();
         }

         else if (choice == '2')
         {
            std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
            gameEngine->LoadGame();
         }

         if (choice == '4')
         {
            return;
         }
         else if (choice == '3')
         {
            ShowCredits();
            std::cin >> choice;
         }
      }
   
   else
   {
      std::cout << "Invalid input" << std::endl;
      std::cout << "\n";
      valid = false;
   }
}
while (!std::cin.eof() || valid == false);
}



void ShowCredits()
{
   std::cout << "---------------------------------" << std::endl;
   std::cout << "Name: Omar El Eter" << std::endl;
   std::cout << "Student ID: s3888328" << std::endl;
   std::cout << "Email: s3888328@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Jonathan Grbac" << std::endl;
   std::cout << "Student ID: s3659145" << std::endl;
   std::cout << "Email: s3659145@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Nicholas Santosa" << std::endl;
   std::cout << "Student ID: s3844591" << std::endl;
   std::cout << "Email: s3844591@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: James McGregor" << std::endl;
   std::cout << "Student ID: s3787611" << std::endl;
   std::cout << "Email: s3787611@student.rmit.edu.au" << std::endl;
   std::cout << "---------------------------------" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit" << std::endl;
}


