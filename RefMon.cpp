#include <regex>
#include <string>
#include "RefMon.h"

//REGEX
regex LOW("LOW");
regex MEDIUM("MEDIUM");
regex HIGH("HIGH");

map<string, int> SubMap; //referece monitor map for subjects and their security levels
map<string, int> ObjMap; //referece monitor map for objects and their security levels

RefMon::RefMon()
{
}

void RefMon::addSubject(string NAME, string SECURITYLEVEL)
{

    if (regex_match(SECURITYLEVEL, LOW))
    {
        SubMap[NAME] = 1; //security level
    }
    else if (regex_match(SECURITYLEVEL, MEDIUM))
    {
        SubMap[NAME] = 2; //security level
    }
    else if (regex_match(SECURITYLEVEL, HIGH))
    {
        SubMap[NAME] = 3; //security level
    }
}

void RefMon::addObject(string NAME, string SECURITYLEVEL)
{

    if (regex_match(SECURITYLEVEL, LOW))
    {
        ObjMap[NAME] = 1; //security level
    }
    else if (regex_match(SECURITYLEVEL, MEDIUM))
    {
        ObjMap[NAME] = 2; //security level
    }
    else if (regex_match(SECURITYLEVEL, HIGH))
    {
        ObjMap[NAME] = 3; //security level
    }
}

bool RefMon::executeRead(string SUBNAME, string OBJNAME) //check security level
{
    string subsecurity;
    string objsecurity;
    for (auto it = SubMap.begin(); it != SubMap.end(); ++it) //find subject and its security level
    {
        if (it->first == SUBNAME)
        {                             //if subject name matches, get its security level to compare
            subsecurity = it->second; //store to compare
        }
    }

    for (auto it = ObjMap.begin(); it != ObjMap.end(); ++it)
    {
        if (it->first == OBJNAME)
        {                             //if subject name matches, get its security level to compare
            objsecurity = it->second; //store to compare
        }
    }

    if (subsecurity >= objsecurity)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool RefMon::executeWrite(string SUBNAME, string OBJNAME) //check security level
{
    string subsecurity;
    string objsecurity;
    for (auto it = SubMap.begin(); it != SubMap.end(); ++it) //find subject and its security level
    {
        if (it->first == SUBNAME)
        {                             //if subject name matches, get its security level to compare
            subsecurity = it->second; //store to compare
        }
    }

    for (auto it = ObjMap.begin(); it != ObjMap.end(); ++it)
    {
        if (it->first == OBJNAME)
        {                             //if subject name matches, get its security level to compare
            objsecurity = it->second; //store to compare
        }
    }

    if (subsecurity <= objsecurity)
    {
        return true;
    }
    else if (subsecurity>objsecurity)
    {
        return false;
    }
}

string RefMon::printState(string NAME)
{
    string temp;
    for (auto it = SubMap.begin(); it != SubMap.end(); ++it) //find subject and its security level
    {
        if (it->first == NAME)
        { //if subject name matches, get its security level to compare
            if (it->second == 1)
            {
                return "LOW";
            }
            else if (it->second == 2)
            {
                temp = "MEDIUM";
                return temp;
            }
            else if (it->second == 3)
            {
                temp = "HIGH"; 
                return temp;
            }
        }
    }

    for (auto it = ObjMap.begin(); it != ObjMap.end(); ++it)
    {
        if (it->first == NAME)
        { //if subject name matches, get its security level to compare
            if (it->second == 1)
            {
                temp = "LOW";
                return temp;
            }
            else if (it->second == 2)
            {
                temp = "MEDIUM";
                return temp;
            }
            else if (it->second == 3)
            {
                temp = "HIGH"; 
                return temp;
            }
        }
    }
}

void RefMon::check()
{
    cout << "SubMap Check -----------------------" << endl;
    for (auto it = SubMap.begin(); it != SubMap.end(); ++it)
    {
        std::cout << it->first // string (key)
                  << ':'
                  << it->second // string's value
                  << std::endl;
    }

    cout << "ObjMap Check -----------------------" << endl;
    for (auto it = ObjMap.begin(); it != ObjMap.end(); ++it)
    {
        std::cout << it->first // string (key)
                  << ':'
                  << it->second // string's value
                  << std::endl;
    }
}
