
#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
   this->head = nullptr;
   this->tail = nullptr;

   // TODO
}

LinkedList::~LinkedList() {
   clear();
}

// Returns size of linked list
int LinkedList::size() {
   // Calls recursive method
   return size(head);
}

// Recursive
int LinkedList::size(Node* node){
    int retVal = 0;

   // Adds 1 to retVal until the node is a nullptr
    if(node == nullptr) {
        retVal = 0;
    } else {
        retVal = 1 + size(node->next);
    }

    return retVal;
}

// Returns the tile of a node in the linked list at index
Tile* LinkedList::get(int index) {
   Node* currentNode = head;
   int x = 0;
   Tile* retVal = nullptr;

   // Loop to find the index
   while (currentNode != nullptr) {
      if (x == index) {
         retVal = currentNode->tile;
      }
      currentNode = currentNode->next;
      ++x;
    }

   return retVal;
}
Tile* LinkedList::getFront(){
   return get(0);
}

Tile* LinkedList::getBack(){
   return get(size());
}

// Adds new node to the front of the linked list
void LinkedList::add_front(Tile* data) {
   // Creating new node with the new tile
   Node* newNode = new Node(data, nullptr);
   newNode->next = head;

   if (head != nullptr) {
      head->prev = newNode;
   } else {
      tail = newNode;
   }

   head = newNode;
}

// Adds new node to the back of the linked list
void LinkedList::add_back(Tile* data) {
   // Calls recursive method
   head = add_back(head, data);
}

// Recursive
Node* LinkedList::add_back(Node* node, Tile* data) {
   Node* retVal = nullptr;

   if(node == nullptr) {
      // empty list (sublist)
      retVal = new Node(data, nullptr);
   } else {
      Node* tempNode = add_back(node->next, data);
      node->next = tempNode;
      retVal = node;
   }

   return retVal;
}

// Remove the first node in the linked list and moves the rest forward
 void LinkedList::remove_front() {
    //Iterative Version
      if (head == nullptr)
        return;
 
    // Move the head pointer to the next node
    Node* temp = head;
    head = head->next;
   
    free(temp);
 //Prev code
   // if (head != nullptr) {
   //    Node* deleteNode = head;
   //    head = head->next;

   //    if (head != nullptr) {
   //       head->prev = nullptr;

   //    } else {
   //       tail = nullptr;
   //    }

   //    delete deleteNode;
   //    deleteNode = nullptr;
   // }
}



// Iterates through the linked list and removes the last node
void LinkedList::remove_back() {
   if (tail != nullptr) {
      Node* deleteNode = tail;
      tail = tail->prev;

      if (tail != nullptr) {
         tail->next = nullptr;
      } else {
         head = nullptr;
      }
      delete deleteNode;
      deleteNode = nullptr;
   }
}

// Removes a node at index in the linked list
void LinkedList::remove(int index) {
   //Iterative version
     //1. check if the position is > 0
   std::cout << index << std::endl;
  if(index < 1) {
    remove_front();
  } else if (index == 1 && head != nullptr) {
      
    //2. if the position is 1 and head is not null, make
    //   head next as head and delete previous head 
    Node* nodeToDelete = head;
    head = head->next;
    free(nodeToDelete);
  } else {
    
    //3. Else, make a temp node and traverse to the 
    //   node previous to the position
    Node* temp = head;
    for(int i = 1; i < index-1; i++) {
      if(temp != NULL) {
        temp = temp->next;
      }
    }
 
    //4. If the previous node and next of the previous  
    //   is not null, adjust links 
    if(temp != nullptr && temp->next != nullptr) {
        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        free(nodeToDelete); 
    } else {

    }       
  }
  // Called recursive method
   // remove(head, index);
} 



// Recursive
Node* LinkedList::remove(Node* node, int index) {
   if(index < 1) {
      return node;
   }
   // If linked list is empty
   else if(node == nullptr) {
      return nullptr;
   }
   // Base case (node needs to be deleted)
   else if (index == 1) {
      Node *res = node->next;
      delete(node);
      return res;
   }
     
   node->next = remove(node->next, index-1);
   return node;
}

// Prints the linked list as LetterValue e.g. A1
void LinkedList::print() {
   Node* current = head;
   if (current != nullptr && current->next != nullptr) {
      while (current->next!= nullptr) {
         std::cout << current->tile->getLetter() << current->tile->getValue() << ",";
         current = current->next;
      }
      std::cout << current->tile->getLetter() << current->tile->getValue() << std::endl;
   } else if (current != nullptr) {
      std::cout << current->tile->getLetter() << current->tile->getValue() << std::endl;
   }
}

// Clears the linked list calls remove_front method until linked list is empty
void LinkedList::clear() {
   while (head != nullptr) {
      remove_front();
   }
}
