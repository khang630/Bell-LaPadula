#include "object.h"
using namespace std;

Object::Object() //defining default constructor here
{
    name="";
    value=0;
}

Object::Object(string NAME)
{
    name=NAME;
    value=0;
}

void Object::setname(string NAME)
{
    name=NAME; //set Object name
}

void Object::setvalue(int VALUE)
{
    value=VALUE; //set Object value
}

string Object::getname()
{
    return name;
}

int Object::getvalue()
{
    return value;
}
