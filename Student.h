/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include "Faculty.h"

class Student : public Person{
  public:
    Student();
    Student(int Id, string name, string level, string major, double gpa, int advisor);
    ~Student();

    void SetMajor(string major);
    string GetMajor();
    void SetGPA(double gpa);
    double GetGPA();
    void SetAdvisor(int id);
    int GetAdvisor();

    void myPrint();
    bool operator==(Student otherStud);
    bool operator!=(Student otherStud);
    bool operator<(Student otherStud);
    bool operator>(Student otherStud);

  private:
    string MajorField;
    double GPAField;
    int AdvisorID;

};
