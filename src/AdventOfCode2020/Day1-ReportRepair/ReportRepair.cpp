// ReportRepair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include "../Utils/Utils.cpp"

using namespace std;

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
    int arrayLength = Utils::CreateIntArrayFromInputFile("input.txt", array);

    cout << "nb lines = " << arrayLength << endl;

    int totalSum = 2020;

    // Part 1
    Part1(arrayLength, totalSum, array);
    Part2(arrayLength, totalSum, array);

    array = NULL;
    delete array;
}
