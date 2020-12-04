/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/

#include <iostream>
#include <fstream>
using namespace std;

class FileProcessor{
  public:
    ifstream Reader;
    ofstream Writer;
    ofstream Appender;

    FileProcessor();
    ~FileProcessor();

    bool OpenReaderFile(string fileName);
    bool OpenWriterFile(string fileName);
    bool OpenAppenderFile(string fileName);

};
