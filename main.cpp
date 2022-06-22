#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include "subject.h"
#include "object.h"
#include "RefMon.h"
using namespace std;

int main(int argc, char *argv[])
{
    //vector of objects
    vector<Subject *> SubjectVector; //vector that holds Subject pointer objects
    vector<Object *> ObjectVector;   //vector that holds Object pointer objects

    RefMon ReferenceMonitor; //One Reference monitor object

    //--REGEX--//
    regex ADDSUB("ADDSUB");
    regex ADDOBJ("ADDOBJ");
    regex READ("READ");
    regex WRITE("WRITE");
    regex STATUS("STATUS");

    ifstream fin; //for reading in
    string inputfile;

    if (argv[1] != NULL)
    {
        inputfile = argv[1]; //pass makefile CLI argument to inputfile variable
    }
    else
    {
        cout << "No input file detected." << endl;
        return 0;
    }

    fin.open(inputfile); //opens input.txt file
    if (fin.is_open())
    {
        cout << "Detected input file" << endl;
        //cout<<inputfile<<endl;

        string str;               //current line of the file
        while (getline(fin, str)) //while getline has something to read in
        {

            char myString[str.length() + 1]; //create a char array
            strcpy(myString, str.c_str());   //copy string "str" into char array. The function .c_str() copies all the individual chars in the str and its output is copied into myString char array. We do this so we can use StrTok().

            for (int i = 0; i < str.length(); i++)
            { //makes everything uppercase
                myString[i] = toupper(myString[i]);
            }

            char *token = strtok(myString, " "); //strtok(char* str, char* delimiter) function takes in the char array as the first argument and the delimiter as the second. Strtok() outputs a token string that ends before every delimiter.

            //cout << token << endl;
            if (regex_match(token, ADDSUB))
            {
                string name;
                string securitylevel;
                int argcounter = 0;
                //cout << "ADDSUB matched" << endl;

                while (token) //while token is not null, keep going through the line
                {
                    //cout << "Token: " << token << endl;
                    if (argcounter == 1)
                    {
                        name = token;
                    }
                    else if (argcounter == 2)
                    {

                        securitylevel = token;
                    }
                    argcounter++;

                    token = strtok(NULL, " "); //move to the next token
                }
                //cout << "Arguments: " << argcounter << endl;

                if (argcounter != 3)
                { //if there is not exactly 3 arguments in ADDSUB
                    cout << "Bad Instruction : " << str << endl;
                    argcounter = 0; //reset argcounter
                    continue;       //skips to next line
                }
                else if (argcounter == 3) //if there are a correct number of arguments
                {
                    Subject *subpointer = new Subject(name); //make a new subject object
                    SubjectVector.push_back(subpointer);     //push Subject pointer into vector

                    //also make refmon object
                    ReferenceMonitor.addSubject(name, securitylevel); //add to map
                    cout << "Subject Added : " << str << endl;
                }
                //cout << "end of line -----------------" << endl;
            }
            else if (regex_match(token, ADDOBJ))
            {
                string name;
                string securitylevel;
                int argcounter = 0;
                //cout << "ADDOBJ matched" << endl;

                while (token) //while token is not null, keep going through the line
                {
                    //cout << "Token: " << token << endl;
                    if (argcounter == 1)
                    {
                        name = token;
                    }
                    else if (argcounter == 2)
                    {
                        securitylevel = token;
                    }
                    argcounter++;
                    token = strtok(NULL, " "); //move to the next token
                }
                //cout << "Arguments: " << argcounter << endl;

                if (argcounter != 3)
                { //if there is not exactly 3 arguments in ADDOBJ
                    cout << "Bad Instruction : " << str << endl;
                    argcounter = 0; //reset argcounter
                    continue;       //skips to next line
                }
                else if (argcounter == 3) //if there are a correct number of arguments
                {
                    Object *objpointer = new Object(name); //make a new subject object
                    ObjectVector.push_back(objpointer);    //push Subject pointer into vector

                    //also make refmon object
                    ReferenceMonitor.addObject(name, securitylevel); //add to map
                    cout << "Object Added : " << str << endl;
                }
                //cout << "end of line -----------------" << endl;
            }
            else if (regex_match(token, READ))
            {
                string subname;
                string objname;
                int argcounter = 0;
                //cout << "READ matched" << endl;

                while (token) //while token is not null, keep going through the line
                {
                    //cout << "Token: " << token << endl;
                    if (argcounter == 1)
                    {
                        subname = token;
                    }
                    else if (argcounter == 2)
                    {
                        objname = token;
                    }
                    argcounter++;
                    token = strtok(NULL, " "); //move to the next token
                }
                //cout << "Arguments: " << argcounter << endl;

                if (argcounter != 3)
                { //if there is not exactly 3 arguments in READ
                    cout << "Bad Instruction : " << str << endl;
                    argcounter = 0; //reset argcounter
                    continue;       //skips to next line
                }
                else if (argcounter == 3) //if there are a correct number of arguments
                {
                    bool subexist = false;
                    bool objexist = false;
                    //-------Check to see if subject and object exist----//
                    for (int i = 0; i < SubjectVector.size(); ++i)
                    {
                        if (SubjectVector[i]->getname() == subname)
                        {
                            subexist = true;
                        }
                    }

                    for (int i = 0; i < ObjectVector.size(); ++i)
                    {
                        if (ObjectVector[i]->getname() == objname)
                        {
                            objexist = true;
                        }
                    }

                    if ((subexist == false) || (objexist == false))
                    {
                        cout << "Bad Instruction : " << str << endl;
                        continue;
                    }
                    //-------------//

                    if (ReferenceMonitor.executeRead(subname, objname) == false)
                    {
                        cout << "Access Denied : " << str << endl;
                        continue;
                    }
                    else if (ReferenceMonitor.executeRead(subname, objname) == true)
                    {
                        //temp object pointers
                        Subject *subtemp;
                        Object *objtemp;
                        int val;

                        for (int i = 0; i < SubjectVector.size(); ++i)
                        {
                            if (SubjectVector[i]->getname() == subname)
                            {
                                subtemp = SubjectVector[i];
                            }
                        }

                        for (int i = 0; i < ObjectVector.size(); ++i)
                        {
                            if (ObjectVector[i]->getname() == objname)
                            {
                                objtemp = ObjectVector[i];
                            }
                        }

                        val = objtemp->getvalue();
                        subtemp->setvalue(val);
                        cout << "Access Granted : " << subname << " reads " << objname << endl;
                    }
                }
                //cout << "end of line -----------------" << endl;
            }
            else if (regex_match(token, WRITE))
            {
                string subname;
                string objname;
                int value;
                int argcounter = 0;
                //cout << "WRITE matched" << endl;

                while (token) //while token is not null, keep going through the line
                {
                    //cout << "Token: " << token << endl;
                    if (argcounter == 1)
                    {
                        subname = token;
                    }
                    else if (argcounter == 2)
                    {
                        objname = token;
                    }
                    else if (argcounter == 3)
                    {
                        value = atoi(token);
                    }
                    argcounter++;
                    token = strtok(NULL, " "); //move to the next token
                }
                //cout << "Arguments: " << argcounter << endl;

                if (argcounter != 4)
                { //if there is not exactly 3 arguments in READ
                    cout << "Bad Instruction : " << str << endl;
                    argcounter = 0; //reset argcounter
                    continue;       //skips to next line
                }
                else if (argcounter == 4)
                {
                    bool subexist = false;
                    bool objexist = false;
                    //-------Check to see if subject and object exist----//
                    for (int i = 0; i < SubjectVector.size(); ++i)
                    {
                        if (SubjectVector[i]->getname() == subname)
                        {
                            subexist = true;
                        }
                    }

                    for (int i = 0; i < ObjectVector.size(); ++i)
                    {
                        if (ObjectVector[i]->getname() == objname)
                        {
                            objexist = true;
                        }
                    }

                    if ((subexist == false) || (objexist == false))
                    {
                        cout << "Bad Instruction : " << str << endl;
                        continue;
                    }

                    if (ReferenceMonitor.executeWrite(subname, objname) == false)
                    {
                        cout << "Access Denied : " << str << endl;
                        continue;
                    }
                    else if (ReferenceMonitor.executeWrite(subname, objname) == true)
                    {
                        Object *objtemp;

                        for (int i = 0; i < ObjectVector.size(); ++i)
                        {
                            if (ObjectVector[i]->getname() == objname)
                            {
                                objtemp = ObjectVector[i];
                            }
                        }

                        objtemp->setvalue(value);
                    }

                    cout << "Access Granted : " << subname << " writes value " << value << " to " << objname << endl;
                }
                //cout << "end of line -----------------" << endl;
            }
            else if (regex_match(token, STATUS))
            {
                int argcounter = 0;
                //cout << "STATUS matched" << endl;

                while (token) //while token is not null, keep going through the line
                {
                    //cout << "Token: " << token << endl;
                    argcounter++;
                    token = strtok(NULL, " "); //move to the next token
                }
                //cout << "Arguments: " << argcounter << endl;

                if (argcounter != 1)
                { //if there is not exactly 3 arguments in STATUS
                    cout << "Bad Instruction : " << str << endl;
                    argcounter = 0; //reset argcounter
                    continue;       //skips to next line
                }
                else if (argcounter == 1)
                {
                    cout << "+--------current state--------+" << endl;
                    cout << "|-subject-|--level--|--value--|" << endl;
                    for (int i = 0; i < SubjectVector.size(); ++i)
                    { //check subjectvector
                        cout << " " << setw(13) << left << SubjectVector[i]->getname() << setw(13) << left << ReferenceMonitor.printState(SubjectVector[i]->getname()) << setw(13) << left << SubjectVector[i]->getvalue() << endl;
                    }

                    cout << "|--object-|--level--|--value--|" << endl;
                    for (int i = 0; i < ObjectVector.size(); ++i)
                    { //check subjectvector
                        cout << " " << setw(13) << left << ObjectVector[i]->getname() << setw(13) << left << ReferenceMonitor.printState(ObjectVector[i]->getname()) << setw(13) << left << ObjectVector[i]->getvalue() << endl;
                    }
                    cout << "+-----------------------------+" << endl;
                }
            }
            else
            {
                cout << "Bad Instruction : " << str << endl;
            }
        }
    }
    else
    {
        cout << "No input file detected. Please try again." << endl;
    }
    fin.close();

    //final checking
    cout << "+--------current state--------+" << endl;
    cout << "|-subject-|--level--|--value--|" << endl;
    for (int i = 0; i < SubjectVector.size(); ++i)
    { //check subjectvector
        cout << " " << setw(13) << left << SubjectVector[i]->getname() << setw(13) << left << ReferenceMonitor.printState(SubjectVector[i]->getname()) << setw(13) << left << SubjectVector[i]->getvalue() << endl;
    }

    cout << "|--object-|--level--|--value--|" << endl;
    for (int i = 0; i < ObjectVector.size(); ++i)
    { //check subjectvector
        cout << " " << setw(13) << left << ObjectVector[i]->getname() << setw(13) << left << ReferenceMonitor.printState(ObjectVector[i]->getname()) << setw(13) << left << ObjectVector[i]->getvalue() << endl;
    }
    cout << "+-----------------------------+" << endl;

    return 0;
}