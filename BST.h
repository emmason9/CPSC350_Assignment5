/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include "TreeNode.h"

template <class Type>
class BST{
  private:
    TreeNode<Type> *root;
    int size;

  public:
    BST();
    ~BST();

    void DeleteAll(TreeNode<Type> *node);
    Type searchNode(Type value); //our key is value in this example, will return node
    void insertNode(Type value);
    bool deleteNode(Type value);

    bool isEmpty();
    int getSize();
    //int getMin();
    //int getMax();
    void recPrint(TreeNode<Type> *node);
    void printEntireTree();
    TreeNode<Type>* getSuccessor(TreeNode<Type> *currNode);

};

template <class Type>
BST<Type>:: BST(){
  root = NULL;
  size = 0;
}

template <class Type>
BST<Type>:: ~BST(){
  TreeNode<Type> *current = root;
  DeleteAll(current);
}

template <class Type>
void BST<Type>:: DeleteAll(TreeNode<Type> *node){
  if(node != NULL){
    DeleteAll(node->left);
    DeleteAll(node->right);
    deleteNode(node->key);
  }
}

template <class Type>
void BST<Type>:: recPrint(TreeNode<Type> *node){
  if(node != NULL){
    recPrint(node->left);
    node->key->myPrint();
    cout<<endl; //buffer between each print
    //cout<< "["<<node->key<<"]" <<endl; //could replace key with value, in this example key is the value
    recPrint(node->right);
  }
}

template <class Type>
void BST<Type>::printEntireTree(){
  recPrint(root);
}

/*
template <class Type>
int BST<Type>:: getMax(){
  TreeNode<Type> *current = root;
  if(isEmpty()){
    return -1;
  }
  while(current->right != NULL){
    current = current->right;
  }
  return current->key;
}


template <class Type>
int BST<Type>:: getMin(){
  TreeNode *current = root;
  if(isEmpty()){
    return -1;
  }
  while (current->left != NULL){
    current = current->left;
  }
  return current->key;
}*/

template <class Type>
int BST<Type> :: getSize(){
  return size;
}

template <class Type>
bool BST<Type> :: isEmpty(){
  return (size <= 0);
}
template <class Type>
void BST<Type>::insertNode(Type value){
  TreeNode<Type> *newNode = new TreeNode<Type>(value); //initializes value into key
  if(isEmpty()){
    root = newNode;
    ++size;
  } else {
    //tree is not empty
    TreeNode<Type> *current = root;
    TreeNode<Type> *parent = NULL;
    while(true){
      parent = current;
      if(value->GetID() < current->key->GetID()){
        current = current->left;
        if(current == NULL){
          //found insertion point
          parent->left = newNode;
          ++size;
          break;
        }
      } else {
        //we go right
        current = current->right;
        if(current == NULL){
          //found insertion
          parent->right = newNode;
          ++size;
          break;
        }
      }
    }
  }
}

template <class Type>
Type BST<Type>:: searchNode(Type value){
  if(isEmpty()){ //or root == NULL
    cout<<"This tree is empty."<<endl;
  } else { //tree is not empty, lets find it
    TreeNode<Type> *current = root;
    while(current->key->GetID() != value->GetID()){
      if(current->key->GetID() > value->GetID()){
        current = current->left;
      } else {
        current = current->right;
      }
      if(current == NULL){
        cout<<"Unable to find node."<<endl;
      }
    }
    return current->key;
  }
}

template <class Type>
bool BST<Type> :: deleteNode(Type value){
  //check isEmpty
  if(isEmpty()){
    return false;
  }
    //can leverage search to determine whether value before proceeding
    //probably use the search function ?
  TreeNode<Type> *current = root;
  TreeNode<Type> *parent = root;
  bool isLeftChild = true;
  //usual code to find a tree newNode
  while(current->key->GetID() != value->GetID()){
    parent = current;
    if(value->GetID() < current->key->GetID()){
      //go left
      isLeftChild = true;
      current = current->left;
    } else {
      //go right
      isLeftChild = false;
      current = current->right;
    }
    if(current == NULL){
      return false; //did not find value
    }
  }
//if we make it here, we found the node/key
//lets delete it

  //checking if leaf node/ has no children
  if(current->left == NULL && current->right == NULL){
    //check if root
    if(current == root){
      root = NULL;
    } else if(isLeftChild){
      //check if left children
      parent->left = NULL;
    } else {
      //check if right child
      parent->right = NULL;
    }
  }else if(current->right == NULL){   //node has one child, need to determine which node is the child (left/right)
    //node has one child and it's left, not right child
    if(current == root){
      root = current->left;
    } else if (isLeftChild){ //left
      parent->left = current->left;
    } else { //right
      parent->right = current->left;
    }
  }else if(current->left == NULL){
    //node has one child and it's right, not left child
    if(current == root){
      root = current->right;
    } else if (isLeftChild){ //left
      parent->left = current->right;
    } else { //right
      parent->right = current->right;
    }
  } else { //node to be deleteed has two children !! :c
    TreeNode<Type> *successor = getSuccessor(current);
    if(current == root){
      root = successor;
    } else if(isLeftChild){
      parent->left = successor;
    } else {
      parent->right = successor;
    }
    //link successors of left node
    successor->left = current->left;
  }
  size--;
  return true;
}

template <class Type>
TreeNode<Type>* BST<Type>::getSuccessor(TreeNode<Type> *node){ //node is the node we gonna delete in the delete method
  TreeNode<Type> *successorParent = node;
  TreeNode<Type> *successor = node;
  TreeNode<Type> *current = node->right;

  while(current!=NULL){
    successorParent = successor;
    successor = current;
    current = current->left;
  }
  //once we exit this while loop, pointers should be in correct positions
  //we need to check whether or not successor is descendant of right child
  if(successor != node->right){
    successorParent->left = successor->right;
    successor->right = node->right;
  }
  return successor;
}
