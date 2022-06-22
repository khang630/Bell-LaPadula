#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;

class Object{

    public:
    Object(); //default constructor
    Object(string NAME); //paramterized constructor

    void setname(string NAME); //set object name
    void setvalue(int VALUE); //set object value
    string getname(); //get object name
    int getvalue(); //get  object value

    private:
    string name; //object name
    int value; //object value
};

#endif