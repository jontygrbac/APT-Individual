#ifndef DICTIONARY
#define DICTIONARY

#include <fstream>
#include <vector>
#include <string>
typedef std::string File;

class Dictionary{
    public:
        /*
        * Initalise an emptry dictionary
        */
        Dictionary();
        ~Dictionary();
        /*
        * From file, add string to dictionary vector
        * It is assumed that the file contents are all string type with letters only
        * and that all letters are lowercase
        */
        void add(File fileName);
        /*Return a string by searching for a specific word from the dictionary vector
        */
        std::string get(std::string word);

    private:
        std::ifstream input;
        std::vector<std::string> dictionary;
};
#endif