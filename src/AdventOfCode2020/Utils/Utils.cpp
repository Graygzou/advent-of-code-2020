// Utils.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

int CreateIntArrayFromInputFile(const char* fileName, int* intArray)
{
    int arrayLength = 0;

    std::string line;
    std::ifstream  myfile;
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

int CreateStringArrayFromInputFile(const char* fileName, std::string* intArray)
{
    int arrayLength = 0;

    std::string line;
    std::ifstream  myfile;
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