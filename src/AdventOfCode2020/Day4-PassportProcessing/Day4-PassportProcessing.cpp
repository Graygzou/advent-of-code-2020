// Day4-PassportProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

static const int NB_FIELDS = 8;

// Turn is into an enum
static const string PASSWORDS_FIELDS[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };


bool IsFieldValid(const char* field, string currentField)
{
    cout << "Field is = " << currentField << endl;

    cmatch cm;
    regex e("([a-z]*)\:(\#?[0-9|a-f]*|[a-z]{3})(cm|in)?");
    regex_match(currentField.c_str(), cm, e);

    string fieldName = cm[1];
    string value = cm[2];
    string unit = cm[3];

    /*cout << "FieldName == " << fieldName << endl;
    cout << "Value == " << value << endl;
    cout << "Unit == " << unit << endl;*/

    bool isValid = false;
    // byr
    if (fieldName == PASSWORDS_FIELDS[0])
    {
        int number = atoi(value.c_str());
        //cout << "number is = " << number << endl;
        isValid = number >= 1920 && number <= 2002;
    }
    // iyr
    else if (fieldName == PASSWORDS_FIELDS[1])
    {
        int number = atoi(value.c_str());
        isValid = number >= 2010 && number <= 2020;
    }
    // eyr
    else if (fieldName == PASSWORDS_FIELDS[2])
    {
        int number = atoi(value.c_str());
        //cout << number << endl;
        isValid = number >= 2020 && number <= 2030;
    }
    // hgt
    else if (fieldName == PASSWORDS_FIELDS[3])
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
        /*cout << max << endl;
        cout << min << endl;
        cout << number << endl;*/
        isValid = max > 0 && min > 0 && number >= min && number <= max;
    }
    // hcl
    else if (fieldName == PASSWORDS_FIELDS[4])
    {
        smatch m;
        e = "\^\#([0-9]|[a-f]){6}$";
        isValid = regex_search(value, m, e);
    }
    // ecl
    else if (fieldName == PASSWORDS_FIELDS[5])
    {
        smatch m;
        e = "\^(amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)$";
        isValid = regex_search(value, m, e);
    }
    // pid
    else if (fieldName == PASSWORDS_FIELDS[6])
    {
        smatch m;
        e = "\^[0-9]{9}$";
        isValid = regex_search(value, m, e);
    }
    // cid
    else if (fieldName == PASSWORDS_FIELDS[7])
    {
        // Nothing yet.
        isValid = true;
    }

    cout << "Is field valid = " << isValid << endl;

    return isValid;
}


bool IsPassportValid(bool checks[])
{
    bool isValid = true;
    for (size_t i = 0; i < NB_FIELDS; i++)
    {
        isValid &= checks[i] || PASSWORDS_FIELDS[i] == "cid";
    }

    return isValid;
}

bool IsCurrentPassportValid(ifstream* file, string line)
{
    bool checks[NB_FIELDS] = { false };

    cout << line << endl;
    do
    {
        for (size_t i = 0; i < NB_FIELDS; i++)
        {
            int indexOfField = -1;
            if ((indexOfField = line.find(PASSWORDS_FIELDS[i])) != string::npos)
            {
                int indexOfNextSpace = line.substr(indexOfField).find(" ");
                if (IsFieldValid(PASSWORDS_FIELDS[i].c_str(), line.substr(indexOfField, indexOfNextSpace)))
                {
                    cout << "Found " << PASSWORDS_FIELDS[i] << endl;
                    checks[i] = true;
                }
            }
        }

        line = "";
        if (!file->eof())
        {
            getline(*file, line);
        }

    } while (!line.empty());

    cout << IsPassportValid(checks) << endl;

    return IsPassportValid(checks);
}

int main()
{
    int nbPassportsValid = 0;

    string line;
    ifstream  myfile;
    myfile.open("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (IsCurrentPassportValid(&myfile, line))
            {
                nbPassportsValid++;
            }
        }
    }
    myfile.close();

    cout << "Result is : " << nbPassportsValid << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
