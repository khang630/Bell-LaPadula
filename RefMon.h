#ifndef REFMON_H
#define REFMON_H

#include <iostream>
#include <map>
using namespace std;

class RefMon{
    public:
    RefMon(); //default constructor
    void addSubject(string NAME, string SECURITYLEVEL); //add a subject to the dictionary
    void addObject(string NAME, string SECURITYLEVEL); //add an object to the dictionary
    bool executeRead(string SUBNAME, string OBJNAME); //allow subject to read the object
    bool executeWrite(string SUBNAME, string OBJNAME); //allow subject to write to an object
    string printState(string NAME); //print the state of all subjects and objects. We pass the subject or objects name and it returns its security level

    void check();

    private:
};

#endif