// Day4-PassportProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

static const int NB_FIELDS = 8;
static const string PASSPORTS_FIELDS[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };

bool IsFieldValid(const char* field, string currentField)
{
    cmatch cm;
    regex e("([a-z]*)\:(\#?[0-9|a-f]*|[a-z]{3})(cm|in)?");
    regex_match(currentField.c_str(), cm, e);

    string fieldName = cm[1];
    string value = cm[2];
    string unit = cm[3];

    bool isValid = false;
    // byr
    if (fieldName == PASSPORTS_FIELDS[0])
    {
        int number = atoi(value.c_str());
        isValid = number >= 1920 && number <= 2002;
    }
    // iyr
    else if (fieldName == PASSPORTS_FIELDS[1])
    {
        int number = atoi(value.c_str());
        isValid = number >= 2010 && number <= 2020;
    }
    // eyr
    else if (fieldName == PASSPORTS_FIELDS[2])
    {
        int number = atoi(value.c_str());
        isValid = number >= 2020 && number <= 2030;
    }
    // hgt
    else if (fieldName == PASSPORTS_FIELDS[3])
    {
        int index = -1;
        int max = 0;
        int min = 0;
        if (unit == "cm")
        {
            min = 150;
            max = 193;
        }
        else if (unit == "in")
        {
            min = 59;
            max = 76;
        }

        int number = atoi(value.c_str());
        isValid = max > 0 && min > 0 && number >= min && number <= max;
    }
    // hcl
    else if (fieldName == PASSPORTS_FIELDS[4])
    {
        smatch m;
        e = "\^\#([0-9]|[a-f]){6}$";
        isValid = regex_search(value, m, e);
    }
    // ecl
    else if (fieldName == PASSPORTS_FIELDS[5])
    {
        smatch m;
        e = "\^(amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)$";
        isValid = regex_search(value, m, e);
    }
    // pid
    else if (fieldName == PASSPORTS_FIELDS[6])
    {
        smatch m;
        e = "\^[0-9]{9}$";
        isValid = regex_search(value, m, e);
    }
    // cid
    else if (fieldName == PASSPORTS_FIELDS[7])
    {
        // Nothing yet.
        isValid = true;
    }

    return isValid;
}


bool IsPassportValid(bool checks[])
{
    bool isValid = true;
    for (size_t i = 0; i < NB_FIELDS; i++)
    {
        isValid &= checks[i] || PASSPORTS_FIELDS[i] == PASSPORTS_FIELDS[7];
    }

    return isValid;
}

bool IsCurrentPassportValid(ifstream* file, string line, bool isDataValidationEnable)
{
    bool fieldsValidationState[NB_FIELDS] = { false };

    do
    {
        for (size_t i = 0; i < NB_FIELDS; i++)
        {
            int indexOfField = -1;
            if ((indexOfField = line.find(PASSPORTS_FIELDS[i])) != string::npos)
            {
                int indexOfNextSpace = line.substr(indexOfField).find(" ");
                if (isDataValidationEnable == false || IsFieldValid(PASSPORTS_FIELDS[i].c_str(), line.substr(indexOfField, indexOfNextSpace)))
                {
                    //cout << "Found " << PASSPORTS_FIELDS[i] << " / ";
                    fieldsValidationState[i] = true;
                }
            }
        }

        line = "";
        if (!file->eof())
        {
            getline(*file, line);
        }

    } while (!line.empty());

    //cout << endl << "Passport is valid = " << (IsPassportValid(fieldsValidationState) ? "true" : "False") << endl;
    return IsPassportValid(fieldsValidationState);
}

void Part1()
{
    int nbPassportsValid = 0;

    string line;
    ifstream  myfile;
    myfile.open("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (IsCurrentPassportValid(&myfile, line, false))
            {
                nbPassportsValid++;
            }
        }
    }
    myfile.close();

    cout << "Result for Part 1 : " << nbPassportsValid << endl;
}

void Part2()
{
    int nbPassportsValid = 0;

    string line;
    ifstream  myfile;
    myfile.open("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (IsCurrentPassportValid(&myfile, line, true))
            {
                nbPassportsValid++;
            }
        }
    }
    myfile.close();

    cout << "Result for Part 2 : " << nbPassportsValid << endl;
}

int main()
{
    cout << "Passport Processing" << endl;

    Part1();
    Part2();
}