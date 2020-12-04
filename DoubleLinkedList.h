/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#ifndef LISTNODE_H
#define LISTNODE_H
#include "ListNode.h"
#ifndef LISTADT_H
#define LISTADT_H
#include "ListADT.h"

template <class Type>
class DoubleLinkedList : public ListADT<Type>{
  public:
    ListNode<Type> *front;
    ListNode<Type> *back;
    unsigned int size;

    DoubleLinkedList();
    ~DoubleLinkedList();

    void Append(Type d);
    void Prepend(Type d);
    Type Peek();
    Type RemoveFront();
    Type RemoveBack();
    Type RemoveNode(Type value);

    int Find(Type value);
    bool isEmpty();
    unsigned int getSize();
    void PrintAll();

#endif
#endif
};

template <class Type>
DoubleLinkedList<Type> :: DoubleLinkedList(){
  front = NULL;
  back = NULL;
  size = 0;
}

//uses the one of the remove functions to empty the list completely
template <class Type>
DoubleLinkedList<Type> :: ~DoubleLinkedList(){
  while(size != 0){
    RemoveFront();
  }
}

//adds a node to the end of the list
template <class Type>
void DoubleLinkedList<Type> :: Append(Type data){
  ListNode<Type> *newNode = new ListNode<Type>(data);
  if(front == NULL){
    front = newNode;
    back = newNode;
  } else {
    back->next = newNode;
    newNode->previous = back;
    back = newNode;
  }
  size++;
}

//add a node to the beginning of the list
template <class Type>
void DoubleLinkedList<Type> :: Prepend(Type data){
  ListNode<Type> *newNode = new ListNode<Type>(data);
  if(front == NULL){
    front == newNode;
    back == newNode;
  } else {
    newNode->next = front;
    front->previous = newNode;
    front = newNode;
  }
}

//shows what's at the beginning of the list
template <class Type>
Type DoubleLinkedList<Type> :: Peek(){
  return front->data;
}

//removes whats at the front of the list and returns the data
template <class Type>
Type DoubleLinkedList<Type> :: RemoveFront(){
  //check if empty
  if(isEmpty()){
    cout << "List is empty!" << endl;
  //otherwise, perform removal
  } else {
    //grabbing data to return
    Type temp = front->data;
    ListNode<Type> *frontTemp = front;
    //checking if the front is the only element in the list
    if(front->next == NULL){
      back == NULL;
    } else {
      front->next->previous == NULL;
    }
    front = front->next;
    frontTemp->next = NULL;
    --size;
    return temp;
  }
}

//removes what's at the end of the list and returns the data
template <class Type>
Type DoubleLinkedList<Type> :: RemoveBack(){
  if(isEmpty()){
    cout << "List is empty!" << endl;
  //only one node to remove
  } else {
    ListNode<Type> *temp = back;
    Type tempData = temp->data;
    if (front == back){ //there's only one node
      front = NULL;
    } else { //more than one node
      temp->previous->next = NULL;
    }
    back = back->previous;
    temp->previous = NULL;
    --size;
    return tempData;
  }
}

template <class Type>
Type DoubleLinkedList<Type> :: RemoveNode(Type value){
  ListNode<Type> *current = front;
  if(isEmpty()){
    cout<<"List is empty!" <<endl;
  } else {
    //loop through list to find key/value
    while(current->data != value){
      current = current->next;
      if(current == NULL){
        return -1;
      }
    }
    //if we find it, we want to delete it
    if (current == front && current == back){
      front = current->next;
    } else if(current == front){
      front = current->next;
      front->previous = NULL;
    } else if (current == back){
      back = current->previous;
      back->next = NULL;
    } else {
      current->previous->next = current->next;
      current->next->previous = current->previous;
      current->next = NULL;
      current->previous = NULL;
    }
    current->next = NULL;
    current->previous= NULL;
    size--;
    Type nodeData = current->data;
    //delete current;
    return nodeData;
  }
}

//returns the position where the value exists, if it doesn't exists, returns -1
template <class Type>
int DoubleLinkedList<Type> :: Find(Type value){
  int position = -1;
  ListNode<Type> *current = front;
  while (current != NULL){
      ++position;
    if(current->data == value){
      break;
    }
    current = current->next;
  }
  if(current == NULL){ //did not find the value
    return -1;
  }
  return position;
}

//checks if the list is empty
template <class Type>
bool DoubleLinkedList<Type> :: isEmpty(){
  return (size == 0);
}

//returns the amount of items in the list
template <class Type>
unsigned int DoubleLinkedList<Type> :: getSize(){
  return size;
}

template <class Type>
void DoubleLinkedList<Type> :: PrintAll(){
  ListNode<Type> *current = front;
  while(current != NULL){
    cout<<current->data<<endl;
    current = current->next;
  }
}
