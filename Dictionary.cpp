#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"
#include <algorithm>

#include <iostream>
typedef std::string File;

    Dictionary::Dictionary(){
        this->size = 0;

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
                std::string str = entry.substr(0,entry.size()-1);
                dictionary.push_back(str);
                ++size;
            }
        }
    }

    int Dictionary::getSize(){
        return size;
    }
    /*Get a string by searching for a specific word from the vector
    */
    bool Dictionary::get(std::string word){
        bool retValue = false;
        std::string value;
        
        for (int i = 0; i < getSize(); ++i){
            if (word == dictionary[i]){
                std::cout << "Found" << std::endl;
                retValue = true;
            }
        }
        
        return retValue;
    }