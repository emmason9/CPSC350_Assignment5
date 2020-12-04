/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include "DataBase.h"

int main (int agrc, char** argv){
  DataBase *myDataBase = new DataBase();

  myDataBase->RunDataBase();

  delete myDataBase;
  return 0;
}
