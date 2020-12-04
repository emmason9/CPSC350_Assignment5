/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include "FileProcessor.h"
#include "BST.h"
#include "GenStack.h"
#include "Student.h"

class DataBase{
  public:
    DataBase();
    ~DataBase();

    void RunDataBase();

  private:
    FileProcessor *myFiles;
    BST<Student*> *StudentTable;
    BST<Faculty*> *FacultyTable;
    bool StartErrorBool; //checks to see if any errors while setting up the tables

    int MaxRollBacks;

    DoubleLinkedList<int> *AllStudentIDs;
    DoubleLinkedList<int> *AllFacultyIDs;

    bool ReadTables();
    bool FillOutStudents();
    bool FillOutFaculty();
    bool CheckAllIDs();
    bool CheckAdvisorIDs();
    bool CheckAdviseeIDs();

    Student* FindStudent(int IDint);
    Faculty* FindFaculty(int IDint);

    void RunFind();
    void StudentEdit(Student* tempStud);
    void FacultyEdit(Faculty* tempFact);

    void RunAdd();
    int AddStudent(Student* tempStud); //return ints just so it's an easy way to escape the process
    int AddFaculty(Faculty* tempFact);

    void DeleteStudent(Student* tempStud);
    void DeleteFaculty(Faculty* tempFact);

    void ChangeAdvisor(Student* tempStud);
    void RemoveAdvisee(Faculty* tempFact);

    void PrintAdvisor();
    void PrintAdvisees();

    void RunPrint();

    void OnExit();
    void WriteToStudent();
    void WriteToFaculty();

//rollback opperations
    void RunRollBack();
    //if 1, added a student
    //if 2, added a faculty
    //if 3, deleted a student
    //if 4, deleted a faculty
    void SaveRollback1(Student* student);
    void SaveRollback2(Faculty* faculty);
    void SaveRollback3(Student* student);
    void SaveRollback4(Faculty* faculty);

    GenStack<Student*> *studentStack;
    GenStack<Faculty*> *facultyStack;
    GenStack<int> *opperationStack;
};
