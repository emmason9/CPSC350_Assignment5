/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include "Faculty.h"

Faculty::Faculty(){
  IDNumber = -1;
  Name = "NA";
  LevelField = "NA";
  DepartmentField = "NA";
  AllAdvisees = new DoubleLinkedList<int>();
}

Faculty::Faculty(int id, string name, string level, string department, DoubleLinkedList<int> *advisees){
  IDNumber = id;
  Name = name;
  LevelField = level;
  DepartmentField = department;
  AllAdvisees = advisees;
}

Faculty::~Faculty(){
  delete AllAdvisees;
}

void Faculty::SetDepartment(string dep){
  DepartmentField = dep;
}

string Faculty::GetDepartment(){
  return DepartmentField;
}

void Faculty::SetAdvisees(DoubleLinkedList<int> *advisees){
  AllAdvisees = advisees;
}

void Faculty::AddAdvisee(int newAd){
  AllAdvisees->Append(newAd);
}

DoubleLinkedList<int>* Faculty::GetAdvisees(){
  return AllAdvisees;
}

void Faculty :: myPrint(){
  cout<<"ID# "<<IDNumber<<endl;
  cout<<"Name: "<<Name<<endl;
  cout<<"Level: "<<LevelField<<endl;
  cout<<"Department: "<<DepartmentField<<endl;
  cout<<"Advisees: "<<endl;
  AllAdvisees->PrintAll();
}
