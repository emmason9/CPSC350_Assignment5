# CPSC350_Assignment5
Student and Faculty Database

1. IDENTIFYING INFORMATION
a. Full Name: Emilee Mason
b. Student ID: 2321064
c. Chapman Email: emmason@chapman.edu
d. Course Number and Section: CPSC 350-01
e. Assignment or Excercise Number: Assignment 5: Student DB

2. A LIST OF ALL SOURCE FILED SUBMITTED FOR THIS ASSIGNMENT
BST.h			//template class for Binary Search Tree
DataBase.cpp
DataBase.h		//class that implements all of the functionality of the database
DoubleLinkedList.h	//template class for double linked lists
Faculty.cpp
Faculty.h		//faculty class that is derived from the person class
FileProcessor.cpp
FileProcessor.h		//processes fstream files
GenStack.h		//template file for a generic stack
ListADT			//interface for double linked list 
ListNode.h		//template list node class for double linked list 
main.cpp		//main file to run code 
Makefile		//helps compile program/files
Person.cpp
Person.h		//base class for the members of the database 
README			//this :>
Student.cpp
Student.h		//student class that's derived from the person class 
TreeNode.h		//template tree node class for database 


3. A DESCRIPTION OF ANY KNOWN COMPILE OR RUNTIME ERRORS, CODE LIMITATIONS, OR DEVATIONS FROM ASSIGNMENT SPECIFICATIONS (IF APPLICABLE)
I was having a weird issue when the students/faculty were comparing themselves
in the BST. They were comparing their addresses instead of their IDs, and I 
think it has to do with the way I have the pointers all set up and how I
have a BST full of Student/Faculty pointers instead of normal instances. When
I tried to convert them to regular instances, I ran into several issues with the
-> and operators, so instead I just directly compare the ID's in the BST since 
both faculty and students use the same GetID() from the base Person class. 

For some reason at the beginning of adding a person into the database, it'll input a
blank space into the first input, but they program rejects it and makes you try again
to get a proper response. Not super sure why it does that little hiccup but it 
doesn't affect the overall performance. 

Also I only had enough time to implement the rollback feature for undoing insert and 
deletes of people, not changes in advisors/advisees. If a rollback requires a new 
advisor ID or new advisees for the new member they're reinserting or replacing, then
the program will ask the user to input the appropriate information for it.


4. A LIST OF ALL REFERENCES USED TO COMPLETE THE ASSIGNMENT, INCLUDING PEERS (IF APPLICABLE)
https://www.geeksforgeeks.org/inheritance-in-c/
This refreshed my memory on inheritance and how to use it properly for C++.

Natalie Ewing taught me how to override the operators on the last assignment, so
I was able to figure those out from then. Also zybook helpped me figure out the 
bugs that I was coming across in the BST file I had. She also showed me the 
getline(cin, variableName) in order to add all the students and faculty member
info with spaces/whitespace without messing with other cin inputs. As well as
the stod() method... I thought there was only stoi() for the whole project :(
She also helpped me figure out the rollback features when I was having issues!
Natalie showed me the way she handled it and I had to completely rewrite that 
class, and ended up ditching the separate class all together when it was coming
down to the wire. 

https://stackoverflow.com/questions/4847100/c-inheritance-inaccessible-base
I had to make the bases public because I wasn't able to access the variables
that Person class had. This link helpped me figure out that bug.

https://www.geeksforgeeks.org/substring-in-cpp/
I used a lot of substrings for finding all the right information for the 
student and faculty tables and setting up their BST's. 


5. INSTRUCTIONS FOR RUNNING THE ASSIGNMENT
	1) Unzip folder and place the folder into a place docker can access it. 
	2) Open up docker and traverse to this folder in the terminal
	3) "make all"
	4) "./Assignment5"
	6) Follow the instructions the program gives! :> Have Fun!
you can also "make realclean" to clean up the folder!


