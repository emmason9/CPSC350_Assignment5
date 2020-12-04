/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include "Student.h"

Student:: Student(){
  IDNumber = -1;
  Name = "NA";
  LevelField = "NA";
  MajorField = "NA";
  GPAField = -1.0;
  AdvisorID = -1;
}

Student :: Student(int Id, string name, string level, string major, double gpa, int advisor){
  IDNumber = Id;
  Name = name;
  LevelField = level;
  MajorField = major;
  GPAField = gpa;
  AdvisorID = advisor;
}

Student:: ~Student(){
  //nothing to delete really
}

void Student:: SetMajor(string major){
  MajorField = major;
}

string Student:: GetMajor(){
  return MajorField;
}

void Student::SetGPA(double gpa){
  GPAField = gpa;
}

double Student:: GetGPA(){
  return GPAField;
}

void Student:: SetAdvisor(int id){
  AdvisorID = id;
}

int Student:: GetAdvisor(){
  return AdvisorID;
}

void Student :: myPrint(){
  cout<<"ID# "<<IDNumber<<endl;
  cout<<"Name: "<<Name<<endl;
  cout<<"Level: "<<LevelField<<endl;
  cout<<"Major: "<<MajorField<<endl;
  cout<<"GPA: "<<GPAField<<endl;
  cout<<"Advisor ID# "<<AdvisorID<<endl;
}

bool Student:: operator==(Student otherStudent){

  return (GetID() == otherStudent.GetID());
}

bool Student:: operator!=(Student otherStudent){
  return (GetID() != otherStudent.GetID());
}

bool Student:: operator<(Student otherStudent){
  cout<<"GetID():"<<GetID()<<endl;
  cout<<"other stud: "<<otherStudent.GetID()<<endl;
  return (GetID() < otherStudent.GetID());
}

bool Student:: operator>(Student otherStudent){
  cout<<"GetID():"<<GetID()<<endl;
  cout<<"other stud: "<<otherStudent.GetID()<<endl;
  return (GetID() > otherStudent.GetID());
}
