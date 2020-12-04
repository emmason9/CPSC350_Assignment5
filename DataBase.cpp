/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/
#include "DataBase.h"
#include <string> //for stoi/stod
#include <algorithm> //for tolower transform
#include <iostream>
using namespace std;

//constructor
DataBase::DataBase(){
  myFiles = new FileProcessor();
  StudentTable = new BST<Student*>();
  FacultyTable = new BST<Faculty*>();
  AllStudentIDs = new DoubleLinkedList<int>();
  AllFacultyIDs = new DoubleLinkedList<int>();
  studentStack = new GenStack<Student*>(20);
  facultyStack = new GenStack<Faculty*>(20);
  opperationStack = new GenStack<int>(20);
  MaxRollBacks = 0;
  if(!ReadTables()){
    cout<<"Certain tables not found... Those database will start empty."<<endl;
  } else {
    if(!CheckAllIDs()){
      cout<<"Mismatching ID numbers error..."<<endl;
      StartErrorBool = true;
    }
  }
}

//destructor
DataBase::~DataBase(){
  delete myFiles;
  delete StudentTable;
  delete FacultyTable;
  delete AllStudentIDs;
  delete AllFacultyIDs;
  delete studentStack;
  delete facultyStack;
  delete opperationStack;
}

//runs the entire database in main
void DataBase::RunDataBase(){
  if(StartErrorBool){
    cout<<"...Error while processing the data..."<<endl;
    cout<<"...shuting down..."<<endl;
  } else {
    bool exitBool = false;
    cout<<"Welcome to the DataBase."<<endl;
    while(!exitBool){
      cout<<endl;
      cout<<"What would you like to do?"<<endl;
      //MAYBE ADD/DELETE IN THE FIND METHOD??? probably
      cout<<"'Print' all data\n'Find' a member\n'Add' a new member\n'Rollback' to the previous databases\n'Exit'"<<endl;
      string userInput;
      cin>>userInput;
      transform(userInput.begin(), userInput.end(), userInput.begin(), :: tolower);
      if(userInput == "find"){
        cout<<"...finding a member..."<<endl;
        RunFind();
      } else if (userInput == "print"){
        cout<<"...printing all data...\n"<<endl;
        RunPrint();
      } else if (userInput == "add"){
        cout<<"...adding a member..."<<endl;
        RunAdd();
      } else if (userInput == "rollback"){
        cout<<"...rolling back..."<<endl;
        RunRollBack();
      } else if (userInput == "exit"){
        OnExit();
        cout<<"...exiting program...\nThank you! Have a nice day!"<<endl;
        exitBool = true;
        break;
      } else {
        cout<<"Invalid input. Double check that you're spelling the 'quoted' options correctly!"<<endl;
      }
    }//end of exit bool while lopp
  }//end of BIG ELSE
}

//ui for finding a person in the database
void DataBase :: RunFind(){
  bool findBool = false;
  while(!findBool){
    cout<<endl;
    cout<<"What type of member are you looking for?\n'Student' or 'Faculty'"<<endl;
    cout<<"We can also find an 'advisor' with a student ID or 'advisees' through a faculty ID and print out their information."<<endl;
    cout<<"(You may also 'quit')"<<endl;
    string userPerson;
    cin>>userPerson;
    transform(userPerson.begin(), userPerson.end(), userPerson.begin(), :: tolower);
    //finding a student through their ID number
    if(userPerson == "student"){
      bool studentFindbool = false;
      while(!studentFindbool){
        cout<<endl;
        cout<<"Please input the student's ID number\n(You may also 'quit')"<<endl;
        string StudentID;
        int StudentIDint;
        cin>>StudentID;
        //try to change it to int, and if not make them reput it in.
        try{
          StudentIDint = stoi(StudentID);
        } catch (std::exception other){
          //if it can be transformed, it might be a "quit" input
          transform(StudentID.begin(), StudentID.end(), StudentID.begin(), :: tolower);
          if(StudentID == "quit"){
            studentFindbool = true;
            break;
          } else {
            cout<<"Invalid input. Make sure to only input numbers. Try Again..."<<endl;
          }
        }
        Student *tempStudent = FindStudent(StudentIDint);
        if(AllStudentIDs->Find(StudentIDint) != -1){
          cout<<endl;
          tempStudent->myPrint();
          StudentEdit(tempStudent);
        }
      }//end of student find while loop
  //finding a faculty through their ID
    } else if (userPerson == "faculty"){
      bool facultyFindBool = false;
      while(!facultyFindBool){
        cout<<endl;
        cout<<"Please input the faculty's ID number\n(You may also 'quit')"<<endl;
        string FacultyID;
        int FacultyIDint;
        cin>>FacultyID;
        try {
          FacultyIDint = stoi(FacultyID);
        } catch (std::exception other){
          transform(FacultyID.begin(), FacultyID.end(), FacultyID.begin(), :: tolower);
          if(FacultyID == "quit"){
            facultyFindBool = true;
            break;
          } else{
            cout<<"Invalid input. Make sure to only input numbers. Try Again..."<<endl;
          }
        }//end of try catch
        Faculty *tempFaculty = FindFaculty(FacultyIDint);
        if(AllFacultyIDs->Find(FacultyIDint) != -1){
          cout<<endl;
          tempFaculty->myPrint();
          FacultyEdit(tempFaculty);
        }//end of find faculty id int if statment
      }//end of faculty find bool while loop
    } else if (userPerson == "advisor"){
      //just print out advisor given a student ID
      PrintAdvisor();
    } else if (userPerson == "advisees"){
      //print out advisees given a faculty ID
      PrintAdvisees();
    } else if (userPerson == "quit"){
      cout<<"...returning to main menu..."<<endl;
      break;
    } else {
      cout<<"Invalid input. Double check that you're spelling the 'quoted' options correctly!"<<endl;
    }
  }//end of the find bool while loop
//maybe ask what would you like to do next? (add, delete, search again, or quit)
}

//can add, edit, or delete the given student
void DataBase :: StudentEdit(Student *tempStudent){
  bool studentEditBool = false;
  while(!studentEditBool){
    cout<<"\nWhat would you like to do with this student?\n'Delete' the student, 'Change' the advisor, or 'Print' student's information"<<endl;
    cout<<"(You can also 'quit')\n"<<endl;
    string userInput;
    cin>>userInput;
    transform(userInput.begin(), userInput.end(), userInput.begin(), :: tolower);
    if(userInput == "delete"){
      //before any changes made, saving previous tables
      SaveRollback3(tempStudent);
      cout<<"...deleting student..."<<endl;
      DeleteStudent(tempStudent);
      //we will need to break out of the while loop since the student is now deleted
      studentEditBool = true;
    } else if (userInput == "print"){
      tempStudent->myPrint();
      cout<<endl;
    } else if (userInput == "change"){
      //before any changes made, saving previous tables
      ChangeAdvisor(tempStudent);
      cout<<endl;
    } else if (userInput == "quit"){
      studentEditBool = true;
      break;
    } else {
      cout<<"Invalid input. Double check that you're spelling the 'quoted' options correctly!"<<endl;
    }
  }
}

//can add, delete, or edit the given faculty
void DataBase :: FacultyEdit(Faculty *tempFaculty){
  bool facultyEditBool = false;
  while(!facultyEditBool){
    cout<<"\nWhat would you like to do with this faculty?\n'Delete' the faculty, 'Remove' an advisee, or 'Print' faculty's information\n(you may also 'quit')"<<endl;
    cout<<"note: when deleting a faculty member, the advisees' advisor will be replaced randomly. You can reassignment them through the Find option from the main menu."<<endl;
    string userInput;
    cin>>userInput;
    transform(userInput.begin(), userInput.end(), userInput.begin(), :: tolower);
    if(userInput == "delete"){
      //before any changes made, saving previous tables
      SaveRollback4(tempFaculty);
      DeleteFaculty(tempFaculty);
      //we'll have to break out of this since there will be no more faculty member to edit
      facultyEditBool = true;
    } else if (userInput == "remove"){
      //before any changes made, saving previous tables

      RemoveAdvisee(tempFaculty);
    } else if (userInput == "print"){
      tempFaculty->myPrint();
    } else if (userInput == "quit"){
      facultyEditBool = true;
      break;
    } else {
      cout<<"Invalid Input. Double check that you're spelling the 'quoted' options correctly!"<<endl;
    }
  }
}

//all UI for adding a member to DB
void DataBase :: RunAdd(){
  bool AddBool = false;
  while(!AddBool){
    cout<<"What type of member would you like to add?\n'Student' or 'Faculty'\n(you may also 'quit')"<<endl;
    cout<<"Note: please add fauclty members before students in order to assign the correct advisors to the correct advisees smoothly."<<endl;
    string userInput;
    cin>>userInput;
    transform(userInput.begin(), userInput.end(), userInput.begin(), :: tolower);
    if(userInput =="student"){
      //before any changes made, saving previous tables
      cout<<"...adding student..."<<endl;
      Student *StudentToAdd = new Student();
      AddStudent(StudentToAdd);
      SaveRollback1(StudentToAdd);
    } else if (userInput == "faculty"){
      //before any changes made, saving previous tables
      cout<<"...adding faculty..."<<endl;
      Faculty *FacultyToAdd = new Faculty();
      AddFaculty(FacultyToAdd);
      SaveRollback2(FacultyToAdd);
    } else if (userInput == "quit"){
      AddBool = true;
      break;
    } else {
      cout<<"Invalid input. Double check that you're spelling the 'quoted' options correctly!"<<endl;
    }//end of else statement
  }//end of add bool while loop
}

//adds a student and askd for all info
int DataBase :: AddStudent(Student* StudentToAdd){
  bool StudentIDBool = false;
  while(!StudentIDBool){
    //add iD number and check if it doesn't exist already!!
    cout<<"\nWhat is the ID number of the student?\n(you can 'quit' at any time to cancel)"<<endl;
    string StudentIDString;
    int StudentIDInt;
    getline(cin, StudentIDString);
    try{
      StudentIDInt = stoi(StudentIDString);
      if(AllStudentIDs->Find(StudentIDInt) != -1){
        cout<<"That ID number already exists. Try Again."<<endl;
        continue;
      } else {
        StudentToAdd->SetID(StudentIDInt);
        StudentIDBool = true;
      }
    } catch (std::exception other){
      transform(StudentIDString.begin(), StudentIDString.end(), StudentIDString.begin(), :: tolower);
      if(StudentIDString == "quit"){
        StudentIDBool = true;
        cout<<"...cancelling adding student..."<<endl;
        return -1;
      } else {
        cout<<"Invalid input. Make sure you're only inputing numbers. Try Again..."<<endl;
      }
    } //end of try catch block
  }//end of student id bool
  //adding name
  cout<<"\nWhat is the name of the student?"<<endl;
  string StudentName;
  getline(cin, StudentName);
  StudentToAdd->SetName(StudentName);
  transform(StudentName.begin(), StudentName.end(), StudentName.begin(), :: tolower);
  if(StudentName == "quit"){
    cout<<"...cancelling adding student..."<<endl;
    return -1; //a way to just exit the program if they decide to cancel adding the student
  }
  //add level
  cout<<"\nWhat year is the student?"<<endl;
  string StudentLevel;
  getline(cin, StudentLevel);
  StudentToAdd->SetLevel(StudentLevel);
//  transform(StudentLevel.begin(), StudentLevel.end(), StudentLevel.begin(), :: tolower);
  if(StudentLevel == "quit"){
    cout<<"...cancelling adding student..."<<endl;
    return -1; //a way to just exit the program if they decide to cancel adding the student
  }
  //add major
  cout<<"\nWhat major is the student in?"<<endl;
  string StudentMajor;
  getline(cin, StudentMajor);
  StudentToAdd->SetMajor(StudentMajor);
//  transform(StudentMajor.begin(), StudentMajor.end(), StudentMajor.begin(), :: tolower);
  if(StudentMajor == "quit"){
    cout<<"...cancelling adding student..."<<endl;
    return -1; //a way to just exit the program if they decide to cancel adding the student
  }
  //add GPA (check for double)
  bool StudentGPABool = false;
  while(!StudentGPABool){
    cout<<"\nWhat's the student's GPA?"<<endl;
    string StudentGPAString;
    double StudentGPADouble;
    cin>>StudentGPAString;
    try{
      StudentGPADouble = stod(StudentGPAString);
      if(StudentGPADouble >= 0.0 && StudentGPADouble <= 5.0){
        StudentToAdd->SetGPA(StudentGPADouble);
        StudentGPABool = true;
      } else {
        cout<<"GPA's must be between 0 and 5.0. Try Again."<<endl;
      }
    } catch (std::exception other){
      transform(StudentGPAString.begin(),StudentGPAString.end(),StudentGPAString.begin(), :: tolower);
      if(StudentGPAString == "quit"){
        cout<<"...cancelling adding student..."<<endl;
        StudentGPABool = true;
        return -1; //a way to just exit the program if they decide to cancel adding the student
      } else {
        cout<<"Invalid input. Make sure the GPA is a decimal! Try Again."<<endl;
      }
    }//end of try catch block
  }//end of student gpa bool
  //add advisor and check if advisor exists and add advisee
  bool AdvisorBool = false;
  while(!AdvisorBool){
    cout<<"\nWhat's the ID number of the student's advisor?"<<endl;
    string AdvisorIDString;
    int AdvisorIDInt;
    cin>>AdvisorIDString;
    try {
      AdvisorIDInt = stoi(AdvisorIDString);
      if(AllFacultyIDs->Find(AdvisorIDInt) != -1){
        //set advisor and add student to advisee
        StudentToAdd->SetAdvisor(AdvisorIDInt);
        (FindFaculty(AdvisorIDInt))->AddAdvisee(StudentToAdd->GetID());
        AdvisorBool = true;
      } else {
        cout<<"Faculty ID not found. Try Again."<<endl;
      }
    } catch (std::exception other){
      transform(AdvisorIDString.begin(),AdvisorIDString.end(),AdvisorIDString.begin(), :: tolower);
      if(AdvisorIDString == "quit"){
        cout<<"...cancelling adding student..."<<endl;
        AdvisorBool = true;
        return -1; //a way to just exit the program if they decide to cancel adding the student
      } else {
        cout<<"Invalid input. Make sure you're only inputing numbers. Try Again..."<<endl;
      }
    }//end of try catch block
  }//end of advisor bool while loop
  //add student to student tables
  cout<<"Adding Student:"<<endl;
  StudentToAdd->myPrint();
  StudentTable->insertNode(StudentToAdd);
  AllStudentIDs->Append(StudentToAdd->GetID());
  cout<<"...returning to main menu..."<<endl;
}

//adds a faculty member and asks for all info
int DataBase :: AddFaculty(Faculty* FacultyToAdd){
  bool FacultyIDBool = false;
  while(!FacultyIDBool){
    //add Id number and check if it doesn't exist already
    cout<<"\nWhat's the faculty's ID number?"<<endl;
    string FacultyIDString;
    int FacultyIDInt;
    getline(cin, FacultyIDString);
    try{
      FacultyIDInt = stoi(FacultyIDString);
      if(AllFacultyIDs->Find(FacultyIDInt) != -1){
        //it exists already
        cout<<"Faculty ID number already exists. Try Again..."<<endl;
      } else {
        //we can create it!
        FacultyToAdd->SetID(FacultyIDInt);
        FacultyIDBool = true;
      }
    } catch (std::exception other){
      transform(FacultyIDString.begin(),FacultyIDString.end(),FacultyIDString.begin(), :: tolower);
      if(FacultyIDString == "quit"){
        FacultyIDBool = true;
        cout<<"...cancelling add faculty..."<<endl;
        return -1;
      } else {
        cout<<"Invalid input. Make sure you're only inputing numbers. Try Again..."<<endl;
      }
    }//end of try catch block
  }//end of faculty ID bool
  //add name
  cout<<"\nWhat's the faculty's name?"<<endl;
  string FacultyName;
  getline(cin, FacultyName);
  FacultyToAdd->SetName(FacultyName);
  transform(FacultyName.begin(), FacultyName.end(), FacultyName.begin(), :: tolower);
  if(FacultyName == "quit"){
    cout<<"...cancelling add faculty..."<<endl;
    return -1;
  }
  //add Level
  cout<<"\nWhat's the faculty's position/level?"<<endl;
  string FacultyLevel;
  getline(cin, FacultyLevel);
  FacultyToAdd->SetLevel(FacultyLevel);
  transform(FacultyLevel.begin(),FacultyLevel.end(),FacultyLevel.begin(), :: tolower);
  if(FacultyLevel == "quit"){
    cout<<"...cancelling add faculty..."<<endl;
    return -1;
  }
  // add department
  cout<<"\nWhat's the faculty's department?"<<endl;
  string FacultyDepartment;
  getline(cin, FacultyDepartment);
  FacultyToAdd->SetDepartment(FacultyDepartment);
  transform(FacultyDepartment.begin(),FacultyDepartment.end(),FacultyDepartment.begin(), :: tolower);
  if(FacultyDepartment == "quit"){
    cout<<"...cancelling add faculty..."<<endl;
    return -1;
  }
  //add advisees (while loop it with a quit)
  bool AdviseeBool = false;
  while (!AdviseeBool){
    cout<<"\nWhat is the ID number of one of their advisees?\n(you can put 'none' if there aren't any yet/any more)"<<endl;
    cout<<"note: if the old advisee has a different advisor currently, this faculty will become their new advisor and the advisee will be removed from their old advisor's advisee list."<<endl;
    string AdviseeIDString;
    int AdviseeIDInt;
    getline(cin, AdviseeIDString);
    try {
      AdviseeIDInt = stoi(AdviseeIDString);
      //must check that they exist
      if(AllStudentIDs->Find(AdviseeIDInt) != -1){
        //it was found, we can add it
        //add new advisee to faculty to add
        FacultyToAdd->AddAdvisee(AdviseeIDInt);
        //get the old advisor id and remove old advisee
        Faculty *oldAdvisor = FindFaculty(FindStudent(AdviseeIDInt)->GetAdvisor());
        //removing from old advisor
        oldAdvisor->GetAdvisees()->RemoveNode(AdviseeIDInt);
        oldAdvisor->myPrint();
        //setting new advisor
        FindStudent(AdviseeIDInt)->SetAdvisor(FacultyToAdd->GetID());
        cout<<AdviseeIDInt<<" was added. Next advisee..."<<endl;
      } else {
        cout<<"Student ID not found. Try Again."<<endl;
      }
    } catch (std::exception other){
      transform(AdviseeIDString.begin(),AdviseeIDString.end(),AdviseeIDString.begin(), :: tolower);
      //can also add "none" and add advisees later !
      if(AdviseeIDString == "none"){
        AdviseeBool = true;
        continue;
      } else if (AdviseeIDString == "quit"){
        cout<<"...cancelling add faculty..."<<endl;
        return -1;
      } else {
        cout<<"Invalid input. Make sure you're only inputing numbers. Try Again..."<<endl;
      }
    }//end of try catch
  }//end of advisee bool while loop
  cout<<"Adding faculty..."<<endl;
  AllFacultyIDs->Append(FacultyToAdd->GetID());
  FacultyTable->insertNode(FacultyToAdd);
  FacultyToAdd->myPrint();
  cout<<"...returning to main menu..."<<endl;
}

//ui for printing out all the info in the database
void DataBase :: RunPrint(){
  cout<<"Students: "<<endl;
  StudentTable->printEntireTree();
  cout<<"\n\nFaculty:"<<endl;
  FacultyTable->printEntireTree();
}

//deleting a student in the data base
void DataBase :: DeleteStudent(Student *tempStudent){
  //removing student from the advisors advisee list
  int AdvisorID = tempStudent->GetAdvisor();
  ListNode<int> *currentFacultyID = AllFacultyIDs->front;
  for(int i=0; i<AllFacultyIDs->getSize(); ++i){
    if(currentFacultyID->data == AdvisorID){
      Faculty *tempAdvisor = FindFaculty(currentFacultyID->data);
      tempAdvisor->GetAdvisees()->RemoveNode(tempStudent->GetID());
    }
    currentFacultyID = currentFacultyID->next;
  }
  //removing student from ID list and table
  AllStudentIDs->RemoveNode(tempStudent->GetID());
  StudentTable->deleteNode(tempStudent);
}

//deleting a faculty member in the data base
void DataBase :: DeleteFaculty(Faculty *tempFaculty){
  //removing from all IDs
  AllFacultyIDs->RemoveNode(tempFaculty->GetID());
  //removing fauclty from student's advisors and replacing them with random advisor
  //retrieving random faculty ID number
  srand(time(0));
  cout<<"...removing faculty...\n...replacing advisees with new random advisor..."<<endl;
  int randomAdvisorPosition = rand()%(AllFacultyIDs->getSize());
  ListNode<int> *tempFact = AllFacultyIDs->front;
  for(int i=0; i<randomAdvisorPosition; ++i){
    tempFact = tempFact->next;
  }
  //finding all students with the old ID number and replacing it with the new one
  int NewAdvisorInt = tempFact->data;
  Student *tempStudent;
  Faculty *newAdvisor = FindFaculty(tempFact->data);
  ListNode<int> *tempStudID = AllStudentIDs->front;
  for(int i=0; i<AllStudentIDs->getSize(); ++i){
    tempStudent = FindStudent(tempStudID->data);
    if(tempStudent->GetAdvisor() == tempFaculty->GetID()){
      tempStudent->SetAdvisor(NewAdvisorInt);
      newAdvisor->AddAdvisee(tempStudent->GetID());
    }
    tempStudID = tempStudID->next;
  }
  //removing faculty from table
  FacultyTable->deleteNode(tempFaculty);
}

//asks what new advisor would replace this students current advisor
void DataBase :: ChangeAdvisor(Student *tempStudent){
  bool AdvisorIDbool = false;
  int NewAdvisorInt;
  string NewAdvisorString;
  while(!AdvisorIDbool){
    cout<<"What is the ID for the student's new advisor?\n(You can also 'quit')"<<endl;
    cin>>NewAdvisorString;
    try{
      NewAdvisorInt = stoi(NewAdvisorString);
    } catch (std::exception other){
      transform(NewAdvisorString.begin(), NewAdvisorString.end(), NewAdvisorString.begin(), :: tolower);
      if(NewAdvisorString == "quit"){
        AdvisorIDbool = true;
        break;
      } else {
        cout<<"Invalid input. Make sure to only input numbers. Try Again..."<<endl;
      }
    }//end of try catch
    if(AllFacultyIDs->Find(NewAdvisorInt) != -1){
      AdvisorIDbool = true;
    } else {
      cout<<"Faculty ID not found."<<endl;
    }
  }
  //Remove advisee from old advisor
  int OldAdvisorInt = tempStudent->GetAdvisor();
  Faculty *OldAdvisor = FindFaculty(OldAdvisorInt);
  OldAdvisor->GetAdvisees()->RemoveNode(tempStudent->GetID());
  //put new advisee in new advisor
  Faculty *NewAdvisor = FindFaculty(NewAdvisorInt);
  NewAdvisor->AddAdvisee(tempStudent->GetID());
  //replace old advisor with new advisor
  tempStudent->SetAdvisor(NewAdvisorInt);
}

//removes advisee given their ID number
void DataBase :: RemoveAdvisee(Faculty *tempFaculty){
  bool adviseeBool = false;
  int AdviseeInt;
  int newAdvisorInt;
  while(!adviseeBool){
    cout<<"\nWhich advisee would you like to delete?\n(you may also 'quit')"<<endl;
    //print out all advisees
    tempFaculty->GetAdvisees()->PrintAll();
    string AdviseeString;
    cin>>AdviseeString;
    try{
      AdviseeInt = stoi(AdviseeString);
    } catch (std::exception other){
      transform(AdviseeString.begin(), AdviseeString.end(), AdviseeString.begin(), :: tolower);
      if(AdviseeString == "quit"){
        adviseeBool = true;
        break;
      } else {
        cout<<"Invalid input. Make sure to only input numbers. Try Again..."<<endl;
      }
    }//end of try catch block
    //checking if the advisee is present in the list
    if(tempFaculty->GetAdvisees()->Find(AdviseeInt) != -1){
      adviseeBool = true;
    } else {
      cout<<"Advisee not found. Try Again."<<endl;
    }
  }//end of advisee bool while loop
  bool advisorBool = false;
  while(!advisorBool){
    cout<<"\nWhich new advisor would you like advisee ID#"<<AdviseeInt<<" to have?"<<endl;
    string newAdvisorString;
    cin>>newAdvisorString;
    try{
      newAdvisorInt = stoi(newAdvisorString);
    } catch (std::exception other){
      //they cannot quit at this point because they would mess everything up in the system
      cout<<"Invalid input. Make sure to only input numbers. Try Again..."<<endl;
      continue;
    }//end of try catch block
    if(AllFacultyIDs->Find(newAdvisorInt) != -1){
      //we found it, so we can exit loop
      advisorBool = true;
    } else {
      cout<<"Faculty not found. Try Again."<<endl;
    }
  }//end of advisor bool while loop
  cout<<"...deleting "<<AdviseeInt<<"..."<<endl;
  //set new advisor for old advisee
  Student *oldAdvisee = FindStudent(AdviseeInt);
  oldAdvisee->SetAdvisor(newAdvisorInt);
  //added old advisee to new advisor
  Faculty *newFaculty = FindFaculty(newAdvisorInt);
  newFaculty->AddAdvisee(AdviseeInt);
  //removing advisee from list
  tempFaculty->GetAdvisees()->RemoveNode(AdviseeInt);
}

//prints out the advisor info for the student id given
void DataBase :: PrintAdvisor(){
  //print out advisor with student id
  bool printAdvisorBool = false;
  while(!printAdvisorBool){
    cout<<"\nWhat is the student's ID number?"<<endl;
    cout<<"(You can also 'quit')\n"<<endl;
    string StudentIDString;
    int StudentIDInt;
    cin>>StudentIDString;
    try{
      StudentIDInt = stoi(StudentIDString);
      if(AllStudentIDs->Find(StudentIDInt) != -1){
        Student *currentStudent = FindStudent(StudentIDInt);
        Faculty *advisor = FindFaculty(currentStudent->GetAdvisor());
        advisor->myPrint();
      } else {
        cout<<"Student ID not found. Try Again."<<endl;
      }
    } catch (std::exception other){
      transform(StudentIDString.begin(), StudentIDString.end(), StudentIDString.begin(), :: tolower);
      if(StudentIDString == "quit"){
        printAdvisorBool = true;
        break;
      } else {
        cout<<"Invalid input. Make sure you're only inputing numbers. Try Again..."<<endl;
      }
    }//end of try catch
  }//end of while loop
}

//prints the advisees of whatever faculty ID that's given
void DataBase :: PrintAdvisees(){
  //print out advisees with faculty id
  //asked for the advisees faculty's ID
  bool printAdviseesBool = false;
  while(!printAdviseesBool){
    cout<<"\nWhat's the faculty's ID number?"<<endl;
    cout<<"(You can also 'quit')\n"<<endl;
    string FacultyIDString;
    int FacultyIDInt;
    cin>>FacultyIDString;
    try{
      FacultyIDInt = stoi(FacultyIDString);
      //prints out the advisees
      if(AllFacultyIDs->Find(FacultyIDInt) != -1){
        Faculty *currentFaculty = FindFaculty(FacultyIDInt);
        ListNode<int> *currentStudentID = currentFaculty->GetAdvisees()->front;
        for(int i=0; i<currentFaculty->GetAdvisees()->getSize(); ++i){
          FindStudent(currentStudentID->data)->myPrint();
          cout<<endl; //for spacing
          currentStudentID = currentStudentID->next;
        }
      } else {
        cout<<"Faculty ID not found. Try Again."<<endl;
      }
    } catch (std::exception other){
      transform(FacultyIDString.begin(), FacultyIDString.end(), FacultyIDString.begin(), :: tolower);
      if(FacultyIDString == "quit"){
        printAdviseesBool = true;
        break;
      } else {
        cout<<"Invalid input. Make sure you're only inputing numbers. Try Again..."<<endl;
      }
    }//end of try catch block
  }//end of while loop
}

//writes all databases info into text files
void DataBase :: OnExit(){
  WriteToStudent();
  WriteToFaculty();
}

//writes all students info into text file
void DataBase :: WriteToStudent(){
  //will always rewrite the entire file, so just open writer
  if(myFiles->OpenWriterFile("studentTable.txt")){
    Student *currentStudent;
    ListNode<int> *currentID = AllStudentIDs->front;
    while(currentID != NULL){
      currentStudent = FindStudent(currentID->data);
      myFiles->Writer << currentStudent->GetID() << ",";
      myFiles->Writer << currentStudent->GetName()<<",";
      myFiles->Writer << currentStudent->GetLevel()<<",";
      myFiles->Writer << currentStudent->GetMajor()<<",";
      myFiles->Writer << currentStudent->GetGPA()<<",";
      myFiles->Writer << currentStudent->GetAdvisor()<<endl;
      currentID = currentID->next;
    }
    myFiles->Writer.close();
  } else {
    cout<<"...error writing to studentTable.txt file...\nStudent Database will revert back to original state."<<endl;
  }
}

//writes all faculty info into text file
void DataBase :: WriteToFaculty(){
  if(myFiles->OpenWriterFile("facultyTable.txt")){
    Faculty *currentFaculty;
    ListNode<int> *currentID = AllFacultyIDs->front;
    while(currentID != NULL){
      currentFaculty = FindFaculty(currentID->data);
      myFiles->Writer << currentFaculty->GetID() << ",";
      myFiles->Writer << currentFaculty->GetName() << ",";
      myFiles->Writer << currentFaculty->GetLevel() <<",";
      myFiles->Writer << currentFaculty->GetDepartment() <<",";
      //we need to iterate through the linked list to get all advisees printed correctly
      ListNode<int> *currentAdvisee = currentFaculty->GetAdvisees()->front;
      int AdviseesSize = currentFaculty->GetAdvisees()->getSize();
      for(int i=0; i<AdviseesSize; ++i){
        if(i == (AdviseesSize - 1)){
          myFiles->Writer << currentAdvisee->data<<endl;
        } else {
          myFiles->Writer << currentAdvisee->data << ",";
          currentAdvisee = currentAdvisee->next;
        }
      }//end of for loop
      currentID = currentID->next;
    }//end of while loop
    myFiles->Writer.close();
  } else {
    cout<<"...error writing to facultyTable.txt file...\nFaculty Database will revert back to original state."<<endl;
  }
}

//reads the text files and inputs all the data in while checking if the IDs are correct
bool DataBase::ReadTables(){
  bool Students = FillOutStudents();
  bool Faculty = FillOutFaculty();
  return (Students && Faculty);
}

//reads from the studentTable.txt file and gets all info from file
bool DataBase::FillOutStudents(){
  if(!myFiles->OpenReaderFile("studentTable.txt")){
    cout<<"Unable to find 'studentTable.txt'..."<<endl;
    return false;
  } else {
    string currentStudent;
    char comma = ',';
    int commaCounter;
    int previousComma; //position of last comma
    Student *studentToAdd;
    while(getline(myFiles->Reader, currentStudent)){
      studentToAdd = new Student();
      commaCounter=0;
      previousComma=0;
      for(int i=0; i<currentStudent.length(); ++i){
        if(currentStudent[i] == comma){
          //depending on how many commas have been counted, the chars inbetween are for the next inputs
          if(commaCounter == 0){
            //getting ID
            string IDString = currentStudent.substr(previousComma,i);
            studentToAdd->SetID(stoi(IDString));
            AllStudentIDs->Append(stoi(IDString));
            previousComma = i;
            commaCounter++;
          } else if(commaCounter == 1){
            //getting Name
            string NameString = currentStudent.substr(previousComma+1, (i-(previousComma+1)));
            studentToAdd->SetName(NameString);
            previousComma = i;
            commaCounter++;
          } else if(commaCounter == 2){
            //getting level
            string LevelString = currentStudent.substr(previousComma+1, (i-(previousComma+1)));
            studentToAdd->SetLevel(LevelString);
            previousComma = i;
            commaCounter++;
          } else if(commaCounter == 3){
            //getting major
            string MajorString = currentStudent.substr(previousComma+1, (i-(previousComma+1)));
            studentToAdd->SetMajor(MajorString);
            previousComma = i;
            commaCounter++;
          } else if(commaCounter == 4){
            //getting gpa
            string GPAString = currentStudent.substr(previousComma+1, (i-(previousComma+1)));
            studentToAdd->SetGPA(atof(GPAString.c_str()));
            previousComma = i;
            commaCounter++;
            //getting advisor id (since it's the last one we don't need another if statement)
            string AdvisorString = currentStudent.substr(previousComma+1,(currentStudent.length()-previousComma+1));
            studentToAdd->SetAdvisor(stoi(AdvisorString));
            previousComma = i;
            commaCounter++;
          }//end of else if statments
        }//end of comma if statement
      }//end of for loop
      StudentTable->insertNode(studentToAdd);
    }//end of while loop
    //close the reader so we can open it for a different file later
    myFiles->Reader.close();
    return true;
  }//end of reader if statment
}

//reads from the facultyTable.txt file and gets all info from file
bool DataBase::FillOutFaculty(){
  //same as student but change fields
  if(!myFiles->OpenReaderFile("facultyTable.txt")){
    cout<<"Unable to find 'facultyTable.txt'..."<<endl;
    return false;
  } else {
    string currentFaculty;
    char comma = ',';
    int commaCounter;
    int previousComma; //position of last comma
    Faculty *facultyToAdd;
    while(getline(myFiles->Reader, currentFaculty)){
      facultyToAdd = new Faculty();
      commaCounter = 0;
      previousComma = 0;
      for(int i=0; i<currentFaculty.length(); ++i){
        if(currentFaculty[i] == comma){
          if(commaCounter == 0){
            //getting ID
            string IDString = currentFaculty.substr(previousComma, i);
            facultyToAdd->SetID(stoi(IDString));
            AllFacultyIDs->Append(stoi(IDString));
            commaCounter++;
            previousComma = i;
          } else if (commaCounter == 1){
            //getting name
            string NameString = currentFaculty.substr(previousComma+1, (i-(previousComma+1)));
            facultyToAdd->SetName(NameString);
            commaCounter++;
            previousComma = i;
          } else if (commaCounter == 2){
            //getting level
            string LevelString = currentFaculty.substr(previousComma+1, (i-(previousComma+1)));
            facultyToAdd->SetLevel(LevelString);
            commaCounter++;
            previousComma = i;
          } else if (commaCounter == 3){
            //getting department
            string DepartmentString = currentFaculty.substr(previousComma+1, (i-(previousComma+1)));
            facultyToAdd->SetDepartment(DepartmentString);
            commaCounter++;
            previousComma = i;
            //getting all the rest of the advisees
            string givenAdvisees = currentFaculty.substr(previousComma+1,(currentFaculty.length()-(previousComma+1)));
            int adviseesCommaCounter = 0;
            previousComma = 0;
            for(int j=0; j<givenAdvisees.length(); ++j){
              if(givenAdvisees[j] == comma){
                if(previousComma == 0){
                  string firstAdvisee = givenAdvisees.substr(previousComma, j);
                  facultyToAdd->AddAdvisee(stoi(firstAdvisee));
                  adviseesCommaCounter++;
                  previousComma = j;
                } else {
                  string nextAdvisees = givenAdvisees.substr(previousComma+1, (j-(previousComma+1)));
                  facultyToAdd->AddAdvisee(stoi(nextAdvisees));
                  adviseesCommaCounter++;
                  previousComma = j;
                }
              } else if (j == (givenAdvisees.length()-1) && previousComma == 0){ //there's only one advisee ID
                facultyToAdd->AddAdvisee(stoi(givenAdvisees));
              } else if (j == (givenAdvisees.length()-1)){ //grabbing the last advisee in the line
                string lastAdvisee = givenAdvisees.substr(previousComma+1, (givenAdvisees.length()-(previousComma+1)));
                facultyToAdd->AddAdvisee(stoi(lastAdvisee));
              }//end of if else advisees
            }//end of advisees for loop
          } //end of else ifs comma counter
        } // end of comma if
      }//end of for loop
      FacultyTable->insertNode(facultyToAdd);
    }//end of while loop
    //close reader for the next file
    myFiles->Reader.close();
    return true;
  }
}

//checks if all the IDs written for each advisee/advisor are present
bool DataBase::CheckAllIDs(){
  return (CheckAdvisorIDs() && CheckAdviseeIDs());
}

//checks if all the advisors the students have are actually present
bool DataBase::CheckAdvisorIDs(){
  //so we can look at the id of the found student
  Student *tempStudent;
  //so we can save the advisor of the temp student
  int tempAdvisorID;
  //so we can iterate through the list
  ListNode<int> *currentStudentID = AllStudentIDs->front;
  //iterate through the entire table of students
  for(int i=0; i<AllStudentIDs->getSize(); ++i){
    tempStudent = FindStudent(currentStudentID->data);
    tempAdvisorID = tempStudent->GetAdvisor();
    //if the find method returns -1, then it's not found
    if (AllFacultyIDs->Find(tempAdvisorID) == -1){
      cout<<"Missing Advisor ID!"<<endl;
      return false;
    }
    //move on to next student
    currentStudentID = currentStudentID->next;
  }
  return true;
}

//checks if all the advisees in the advisor lists are actually present
bool DataBase::CheckAdviseeIDs(){
  //so we can look at the id of the found faculty
  Faculty *tempFaculty;
  //so we can look at all the advisees of the temp faculty
  DoubleLinkedList<int> *tempAdvisees;
  //to iterate through the faculty list
  ListNode<int> *currentFacultyID = AllFacultyIDs->front;
  //for picking up specific advisee ids in the doublelinked lists of advisees
  ListNode<int> *currentAdvisee;
  //iterating through the entire table of faculty
  for(int i=0; i<AllFacultyIDs->getSize(); ++i){
    tempFaculty = FindFaculty(currentFacultyID->data);
    tempAdvisees = tempFaculty->GetAdvisees();
    currentAdvisee = tempAdvisees->front;
    for(int j=0; j<tempAdvisees->getSize(); ++j){
      if(AllStudentIDs->Find(currentAdvisee->data) == -1){
        cout<<"Missing Advisee ID!"<<endl;
        return false;
      }
      currentAdvisee = currentAdvisee->next;
    }
    currentFacultyID = currentFacultyID->next;
  }
  return true;
}

//find the student given the id number in the student table
Student* DataBase::FindStudent(int IDint){
  if(AllStudentIDs->Find(IDint) == -1){
    cout<<"Student ID not found."<<endl;
  } else {
    Student *tempStudent = new Student();
    tempStudent->SetID(IDint);
    Student *returnStudent = StudentTable->searchNode(tempStudent);
    return returnStudent;
  }
}

//finds the faculty given the id number in the faculty table
Faculty* DataBase::FindFaculty(int IDint){
  if(AllFacultyIDs->Find(IDint) == -1){
    cout<<"Faculty ID not found."<<endl;
  } else {
    Faculty *tempFaculty = new Faculty();
    tempFaculty->SetID(IDint);
    Faculty *returnFaculty = FacultyTable->searchNode(tempFaculty);
    return returnFaculty;
  }
}


//rollback methods that were going to be a separate class but i didn't have enough time
//if 1, added a student
//if 2, added a faculty
//if 3, deleted a student
//if 4, deleted a faculty
//runs the actions for a rollback given the situation
void DataBase :: RunRollBack(){
  if(MaxRollBacks >= 5){
    cout<<"Reached max limit for rollbacks."<<endl;
  } else{
    MaxRollBacks++;
    int opperationNum = opperationStack->pop();
    if(opperationNum == 1){
      //we will want to delete the given student
      Student *addedStudent = studentStack->pop();
      //remove from advisee
      Faculty *advisor = FindFaculty(addedStudent->GetAdvisor());
      advisor->GetAdvisees()->RemoveNode(addedStudent->GetID());
      //deleting student from list and table
      AllStudentIDs->RemoveNode(addedStudent->GetID());
      StudentTable->deleteNode(addedStudent);


    } else if(opperationNum == 2){
      //will delete the given faculty memeber
      Faculty *addedFaculty = facultyStack->pop();
      //and ask which advisor do you want the advisees
      bool newAdvisorBool = false;
      while(!newAdvisorBool){
        cout<<"\nWhat would you like the advisees' new advisor of the old faculty member to be?"<<endl;
        string AdvisorIDString;
        int AdvisorIDInt;
        cin>>AdvisorIDString;
        try {
          AdvisorIDInt = stoi(AdvisorIDString);
          if(AllFacultyIDs->Find(AdvisorIDInt) != -1){
            //found the id, implement it!
            ListNode<int> *currAdvisee = addedFaculty->GetAdvisees()->front;
            Faculty *newAdvisor = FindFaculty(AdvisorIDInt);
            while(currAdvisee != NULL){
              //grab the student advisee and set new advisor
              FindStudent(currAdvisee->data)->SetAdvisor(AdvisorIDInt);
              newAdvisor->AddAdvisee(currAdvisee->data);
              currAdvisee = currAdvisee->next;
            }
            newAdvisorBool = true;
          } else {
            cout<<"Faculty ID not found. Try Again."<<endl;
            continue;
          }
        } catch (std::exception other){
          cout<<"Invalid input. Make sure you're only inputing numbers. Try Again..."<<endl;
        } //end of try catch block
      }//end of while loop
      //delete from list and table
      AllFacultyIDs->RemoveNode(addedFaculty->GetID());
      FacultyTable->deleteNode(addedFaculty);


    } else if(opperationNum == 3){
      //add the given student
      Student *deletedStudent = studentStack->pop();
      //and ask which advisor you want
      bool AdvisorIDbool = false;
      int NewAdvisorInt;
      string NewAdvisorString;
      while(!AdvisorIDbool){
        cout<<"What is the ID for the student's advisor?"<<endl;
        cin>>NewAdvisorString;
        try{
          NewAdvisorInt = stoi(NewAdvisorString);
        } catch (std::exception other){
            cout<<"Invalid input. Make sure to only input numbers. Try Again..."<<endl;
        }//end of try catch
        if(AllFacultyIDs->Find(NewAdvisorInt) != -1){
          //the id number exists and we can add it in
          AdvisorIDbool = true;
          break;
        } else {
          cout<<"Faculty ID not found."<<endl;
        }
      }//end of while loop
      //set new advisor to student and add advisee
      deletedStudent->SetAdvisor(NewAdvisorInt);
      Faculty *newAdvisor = FindFaculty(NewAdvisorInt);
      newAdvisor->AddAdvisee(deletedStudent->GetID());
      StudentTable->insertNode(deletedStudent);
      AllStudentIDs->Append(deletedStudent->GetID());


    } else if(opperationNum == 4){
      //add the given faculty memeber
      Faculty *deletedFaculty = facultyStack->pop();
      //and ask which advisees you want
      bool AdviseeBool = false;
      while (!AdviseeBool){
        cout<<"\nWhat is the ID number of one of their advisees?\n(you can put 'none' if there aren't any yet/any more)"<<endl;
        cout<<"note: if the old advisee has a different advisor currently, this faculty will become their new advisor and the advisee will be removed from their old advisor's advisee list."<<endl;
        string AdviseeIDString;
        int AdviseeIDInt;
        getline(cin, AdviseeIDString);
        try {
          AdviseeIDInt = stoi(AdviseeIDString);
          //must check that they exist
          if(AllStudentIDs->Find(AdviseeIDInt) != -1){
            //it was found, we can add it
            //add new advisee to faculty to add
            deletedFaculty->AddAdvisee(AdviseeIDInt);
            //get the old advisor id and remove old advisee
            Faculty *oldAdvisor = FindFaculty(FindStudent(AdviseeIDInt)->GetAdvisor());
            //removing from old advisor
            oldAdvisor->GetAdvisees()->RemoveNode(AdviseeIDInt);
            oldAdvisor->myPrint();
            //setting new advisor
            FindStudent(AdviseeIDInt)->SetAdvisor(deletedFaculty->GetID());
            cout<<AdviseeIDInt<<" was added. Next advisee..."<<endl;
          } else {
            cout<<"Student ID not found. Try Again."<<endl;
          }
        } catch (std::exception other){
          //can also add "none" and add advisees later !
          if(AdviseeIDString == "none"){
            AdviseeBool = true;
            continue;
          } else {
            cout<<"Invalid input. Make sure you're only inputing numbers. Try Again..."<<endl;
          }
        }//end of try catch
      }//end of advisee bool while loop
      FacultyTable->insertNode(deletedFaculty);
      AllFacultyIDs->Append(deletedFaculty->GetID());


    }
  }//end of max rollback if
}

//saves the student that was added
void DataBase::SaveRollback1(Student* student){
  opperationStack->push(1);
  studentStack->push(student);
  if(MaxRollBacks > 0){
    MaxRollBacks--;
  }
}

//saves the faculty that was added
void DataBase::SaveRollback2(Faculty* faculty){
  opperationStack->push(2);
  facultyStack->push(faculty);
  if(MaxRollBacks > 0){
    MaxRollBacks--;
  }
}

//saves the student that was deleted
void DataBase::SaveRollback3(Student* student){
  opperationStack->push(3);
  studentStack->push(student);
  if(MaxRollBacks > 0){
    MaxRollBacks--;
  }
}

//saves the faculty that was deleted
void DataBase::SaveRollback4(Faculty* faculty){
  opperationStack->push(4);
  facultyStack->push(faculty);
  if(MaxRollBacks > 0){
    MaxRollBacks--;
  }
}
