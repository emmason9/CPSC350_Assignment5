/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include <cstddef> //for the NULL ref
#include <iostream>
using namespace std;

template <class Type>
class ListNode{
  public:
    ListNode(Type d);
    ~ListNode();

    Type data;
    ListNode<Type> *next;
    ListNode<Type> *previous;

};

template <class Type>
ListNode<Type> :: ListNode(Type d){
  data = d;
  next = NULL;
  previous = NULL;
}

template <class Type>
ListNode<Type> :: ~ListNode(){
  next = NULL;
  previous = NULL;
  delete data; //just in case
}
