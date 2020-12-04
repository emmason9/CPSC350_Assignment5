/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include "Person.h"

Person :: Person(){
  IDNumber = -1;
  Name = "NA";
  LevelField = "NA";
}

Person :: Person(int Id, string name, string level){
  IDNumber = Id;
  Name = name;
  LevelField = level;
}

Person :: ~Person(){
  //nothing important to delete
}

void Person::SetID(int Id){
  IDNumber = Id;
}

int Person::GetID(){
  return IDNumber;
}

void Person::SetName(string name){
  Name = name;
}

string Person::GetName(){
  return Name;
}

void Person :: SetLevel(string level){
  LevelField = level;
}

string Person:: GetLevel(){
  return LevelField;
}
