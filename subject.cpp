#include "subject.h"
using namespace std;

Subject::Subject() //defining default constructor here
{
    name = "";
    value = 0;
}

Subject::Subject(string NAME)
{
    name = NAME;
    value =0;
}

void Subject::setname(string NAME)
{
    name = NAME; //set subject name
}

void Subject::setvalue(int VALUE)
{
    value = VALUE; //set subject value
}


string Subject::getname()
{
    return name;
}

int Subject::getvalue()
{
    return value;
}

