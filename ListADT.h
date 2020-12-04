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
class ListADT{
  public:
    virtual void Append(Type d) = 0;
    virtual void Prepend(Type d) = 0;
    virtual Type Peek() = 0;
    virtual Type RemoveFront() = 0;
    virtual Type RemoveBack() = 0;
    virtual Type RemoveNode(Type value) = 0;
    virtual int Find(Type value) = 0;
    virtual bool isEmpty() = 0;
    virtual unsigned int getSize() = 0;
    virtual void PrintAll() = 0;

};
