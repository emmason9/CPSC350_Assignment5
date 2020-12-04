/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/

#include <iostream>
using namespace std;

template <class Type>
class GenStack{
  public:
    GenStack();
    GenStack(int maxSize);
    ~GenStack();

    void push(Type input);
    Type pop();
    Type peek();

    bool isFull();
    bool isEmpty();
    int getSize();

    int top;
    int maxSize;

    Type *myArray;

}; //end of normal header class

//default constructor
template <class Type>
GenStack<Type> :: GenStack(){
  top = -1;
  maxSize = 128;
  myArray = new Type[128];
}

//overloaded constructor
template <class Type>
GenStack<Type> :: GenStack(int newMaxSize){
  top = -1;
  maxSize = newMaxSize;
  myArray = new Type[newMaxSize];
}

//destructor
template <class Type>
GenStack<Type> :: ~GenStack(){
  delete myArray;
}

//inserts a new obj to the top of the stack
template <class Type>
void GenStack<Type> :: push(Type letter){
  if (isFull()){
    //saving all old info
    int oldMax = maxSize;
    maxSize *= 2;
    //creating new array with more space
    Type *newArray = new Type[maxSize];
    //adding all elements into new array
    for(int i = 0; i < oldMax; ++i){
      newArray[i] = myArray[i];
    }
    //reassignment new array
    myArray = newArray;
    //adding new push
    myArray[++top] = letter;
  } else {
    myArray[++top] = letter;
  }
}

//removes what's at the top of the stack and returns it
template <class Type>
Type GenStack<Type> :: pop(){
  if (isEmpty()){
    cout << "Stack is empty!" << endl;
    return '\0'; //  \0 means that theres no characer
  } else {
    return myArray[top--];
  }
}

//shows what's at the top of the stack
template <class Type>
Type GenStack<Type> :: peek(){
  if (isEmpty()){
    cout << "Stack is empty!" << endl;
  } else {
    return myArray[top];
  }
}

//tells whether stack is full or not
template <class Type>
 bool GenStack<Type> :: isFull(){
   return (top == (maxSize-1));
 }

//tells whether stack is empty or not
template <class Type>
 bool GenStack<Type> :: isEmpty(){
   return (top == -1);
 }

//tells how many items in stack
template <class Type>
 int GenStack<Type> :: getSize(){
   return (top+1); //top++ would update top
 }
