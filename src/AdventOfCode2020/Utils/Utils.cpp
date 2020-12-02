#include "Utils.h"

using namespace std;

int Utils::CreateIntArrayFromInputFile(const char* fileName, int* intArray)
{
    int arrayLength = 0;

    string line;
    ifstream  myfile;
    myfile.open(fileName);
    if (myfile.is_open())
    {
        int inputNumber = 0;
        while (getline(myfile, line))
        {
            inputNumber = atoi(line.c_str());
            *intArray = inputNumber;
            intArray++;
            arrayLength++;
        }
    }
    myfile.close();

    return arrayLength;
}

int Utils::CreateStringArrayFromInputFile(const char* fileName, string* intArray)
{
    int arrayLength = 0;

    string line;
    ifstream  myfile;
    myfile.open(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            *intArray = line.c_str();
            intArray++;
            arrayLength++;
        }
    }
    myfile.close();

    return arrayLength;
}