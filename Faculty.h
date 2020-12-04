/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include "Person.h"
#include "DoubleLinkedList.h"

class Faculty : public Person{
  public:
    Faculty();
    Faculty(int Id, string name, string level, string department, DoubleLinkedList<int> *advisees);
    ~Faculty();

    void SetDepartment(string dep);
    string GetDepartment();
    void SetAdvisees(DoubleLinkedList<int> *advisees);
    void AddAdvisee(int newAdvisee);
    DoubleLinkedList<int>* GetAdvisees();

    void myPrint();

  private:
    string DepartmentField;
    DoubleLinkedList<int> *AllAdvisees;
};
