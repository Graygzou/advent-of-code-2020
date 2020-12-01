// ReportRepair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

int CreateArrayFromInputFile(const char* fileName, int* intArray)
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

void Part1(int arrayLength, int totalSum, int* array)
{
    for (size_t i = 0; i < arrayLength; i++)
    {
        int currentValue = abs(array[i] - totalSum);
        for (size_t j = i+1; j < arrayLength; j++)
        {
            if (array[j] == currentValue)
            {
                cout << "found match for = " << array[i] << " + " << array[j] << " = " << totalSum << endl;
                cout << "result is = " << array[i] * array[j] << endl;
            }
        }
    }
}

void Part2(int arrayLength, int totalSum, int* array)
{
    for (size_t i = 0; i < arrayLength; i++)
    {
        int currentValue = abs(array[i] - totalSum);
        for (size_t j = i+1; j < arrayLength; j++)
        {
            for (size_t k = j+1; k < arrayLength; k++)
            {
                if (array[j] + array[k] == currentValue)
                {
                    cout << "found match for = " << array[i] << " + " << array[j] << " + " << array[k] << " = " << totalSum << endl;
                    cout << "result is = " << array[i] * array[j] * array[k] << endl;
                }
            }
        }
    }
}

int main()
{
    cout << "Report Repair" << endl;

    int* array = new int[256];
    int arrayLength = CreateArrayFromInputFile("input.txt", array);

    cout << "nb lines = " << arrayLength << endl;

    int totalSum = 2020;

    // Part 1
    Part1(arrayLength, totalSum, array);
    Part2(arrayLength, totalSum, array);

    array = NULL;
    delete array;
}
