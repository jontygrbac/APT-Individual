
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   int size();

   Tile* get(int index);
   Tile* get(Tile& data);
   Tile* getFront();
   Tile* getBack();

   void add_front(Tile* data);
   void add_back(Tile* data);

   void remove_front();
   void remove_back();
   void remove(int index);

   void print();

   void clear();

private:
   int size(Node* node); // Recursive
   Node* add_back(Node* node, Tile* data); // Recursive
   Node* remove(Node* node, int index); //Recursive

   Node* head;
   Node* tail;
};

#endif // ASSIGN2_LINKEDLIST_H
