#ifndef SUBJECT_H
#define SUBJECT_H

#include <iostream>
using namespace std;

class Subject
{

public:
    Subject();                          //default constructor
    Subject(string NAME); //paramterized constructor

    void setname(string NAME);           //set subject name
    void setvalue(int VALUE);            //set subject value

    string getname();                    //get subject name
    int getvalue();                      //get  subject value


private:
    string name;       //subject name
    int value;         //subject value

};

#endif