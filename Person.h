/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/

#include <iostream>
using namespace std;

class Person{
  public:
    Person();
    Person(int Id, string name, string level);
    ~Person();

    void SetID(int Id);
    int GetID();
    void SetName(string name);
    string GetName();
    void SetLevel(string level);
    string GetLevel();

  protected:
    int IDNumber;
    string Name;
    string LevelField;

};
