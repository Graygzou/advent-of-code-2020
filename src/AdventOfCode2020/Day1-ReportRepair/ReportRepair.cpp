// ReportRepair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include "../Utils/Utils.cpp"

using namespace std;

pair<int, int> FindTwoEntryThatSumToValue(int arrayLength, int totalSum, int* array);
int* FindThreeEntryThatSumToValue(int arrayLength, int totalSum, int* array);

int main()
{
    cout << "Report Repair" << endl;

    int* array = new int[256];
    int arrayLength = Utils::CreateIntArrayFromInputFile("input.txt", array);

    // Part 1
    int totalSum = 2020;
    pair<int, int> twoEntries = FindTwoEntryThatSumToValue(arrayLength, totalSum, array);
    cout << "result for part 1 is = " << twoEntries.first * twoEntries.second << endl;

    // Part 2
    int *threeEntries = FindThreeEntryThatSumToValue(arrayLength, totalSum, array);
    if (threeEntries != nullptr)
    {
        cout << "result for part 2 is = " << threeEntries[0] * threeEntries[1] * threeEntries[2] << endl;
    }

    array = NULL;
    delete array;
}

/// <summary>
/// Find the two entries that sum to the given number (equals to 2020 fro part 1)
/// </summary>
pair<int, int> FindTwoEntryThatSumToValue(int arrayLength, int totalSum, int* array)
{
    pair<int, int> result = make_pair(0, 0);

    for (size_t i = 0; i < arrayLength; i++)
    {
        int currentValue = totalSum - array[i];
        for (size_t j = i+1; j < arrayLength; j++)
        {
            if (array[j] == currentValue)
            {
                result = make_pair(array[i], array[j]);
            }
        }
    }

    return result;
}

/// <summary>
/// Find the three entries that sum to the given number (equals to 2020 fro part 1)
/// </summary>
int* FindThreeEntryThatSumToValue(int arrayLength, int totalSum, int* array)
{
    int* result = nullptr;

    for (size_t i = 0; i < arrayLength; i++)
    {
        int currentValue = totalSum - array[i];
        for (size_t j = i+1; j < arrayLength; j++)
        {
            for (size_t k = j+1; k < arrayLength; k++)
            {
                if (array[j] + array[k] == currentValue)
                {
                    result = new int[] { array[i], array[j], array[k] };
                }
            }
        }
    }

    return result;
}