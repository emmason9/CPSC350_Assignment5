/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include <cstddef> //for NULL
#include <iostream>
using namespace std;

template <class Type>
class TreeNode{
  public:
    TreeNode();
    TreeNode(Type key);
    ~TreeNode();

    Type key;
    TreeNode<Type> *left;
    TreeNode<Type> *right;
};

template <class Type>
TreeNode<Type>::TreeNode(){
  left = NULL;
  right = NULL;
}

template <class Type>
TreeNode<Type>::TreeNode(Type newKey){
  key = newKey;
  left = NULL;
  right = NULL;
}

template <class Type>
TreeNode<Type>::~TreeNode(){
  delete right;
  delete left;
}
