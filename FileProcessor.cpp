/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 5: Student DB
*/

#include "FileProcessor.h"

//deafult constuctor
  FileProcessor::FileProcessor(){
    //all files already declared in header
  }

//making sure all the fstream objects get closed at the end
  FileProcessor :: ~FileProcessor(){
    if(Reader.is_open()){
      Reader.close();
    }
    if(Writer.is_open()){
      Writer.close();
    }
    if(Appender.is_open()){
      Appender.close();
    }
  }

//opens ifstream file that reads given file name
  bool FileProcessor::OpenReaderFile(string FileName){
    Reader.open(FileName);
    if (!Reader.is_open()){
      return false;
    }
    return true;
  }

//opens ofstream file that writes to given file name
  bool FileProcessor::OpenWriterFile(string FileName){
    Writer.open(FileName);
    if (!Writer.is_open()){
      return false;
    }
    return true;
  }

//opens ofstream file that appends to given file name
  bool FileProcessor::OpenAppenderFile(string FileName){
    Appender.open(FileName, ios::app);
    if (!Appender.is_open()){
      return false;
    }
    return true;
  }
