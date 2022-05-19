#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"
#include <algorithm>

#include <iostream>
typedef std::string File;

    Dictionary::Dictionary(){

    }
    Dictionary::~Dictionary(){
        input.close();
    }
    /*From file, add string to dictionary vector
    * It is assumed that the file contents are all string type with letters only
    * and that all letters are lowercase
    */
    void Dictionary::add(File fileName){
        input.open(fileName, std::ifstream::in);
        if(input.good()){
            while(!input.eof()){
                std::string entry;
                std::getline(input, entry);
                dictionary.push_back(entry);
            }
        }
    }
    /*Get a string by searching for a specific word from the vector
    */
    std::string Dictionary::get(std::string word){
        std::string retValue = "";
        std::string value;
        std::cout << word.size() << "\n";
        if(!dictionary.empty()){
            for(std::vector<std::string>::iterator it = dictionary.begin(); it != dictionary.end();
             ++it){
                value = *it;
                if(word.compare(value) == 0){
                    retValue = value;
                }
                else{
                    //retValue = "None found";
                }
            }
        }
        return retValue;
    }