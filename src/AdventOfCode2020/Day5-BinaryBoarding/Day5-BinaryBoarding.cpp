// Day5-BinaryBoarding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "../Utils/framework.h"

using namespace std;

int ComputeSeatID(string binarySpaceRepart);
int ComputeMissingSeatID(int maxSeatID, int minSeatID, int sumOfSeatID);

int main()
{
    string* lines = new string[850];

    int nbLines = CreateStringArrayFromInputFile("input.txt", lines);

    int maxSeatID = -1;
    int minSeatID = -1;
    int sumOfSeatIDs = 0;

    for (size_t i = 0; i < nbLines; i++)
    {
        int seatID = ComputeSeatID(*lines);

        // Find the max of all the seat ID
        if (maxSeatID == -1 || maxSeatID < seatID)
        {
            maxSeatID = seatID;
        }

        // Find the min of all seat ID
        if (minSeatID == -1 || minSeatID > seatID)
        {
            minSeatID = seatID;
        }

        sumOfSeatIDs += seatID;
        lines++;
    }

    cout << "Resulat of part 1 is " << maxSeatID << endl;

    // We want to include the last seat in our calculation so we substract one.
    minSeatID -= 1;
    int part2Result = ComputeMissingSeatID(maxSeatID, minSeatID, sumOfSeatIDs);
    cout << "Resulat of part 2 is " << part2Result << endl;
}


/// <summary>
/// Find the missing seat ID in the plan which is in the middle of the plan (not in the very front or back of the plane)
/// Used the triangular number formula to solve it
/// </summary>
/// <returns>the missing seat ID</returns>
int ComputeMissingSeatID(int maxSeatID, int minSeatID, int sumOfSeatID)
{

    int sumFromOneToMaxSeatID = ((maxSeatID * (maxSeatID + 1)) / 2);
    int sumFromOneToMinSeatID = ((minSeatID * (minSeatID + 1)) / 2);
    
    int computedSumOfAllSeatIDs = sumFromOneToMaxSeatID - sumFromOneToMinSeatID;
    return computedSumOfAllSeatIDs - sumOfSeatID;
}

// Apply dichotomie
int ComputeRowOrColumn(char lower, char higher, int initialMinBounds, int initialMaxBounds, string subRepartitionString)
{
    int index = 0;
    int minBounds = initialMinBounds;
    int maxBounds = initialMaxBounds;

    do
    {
        int halfBound = (minBounds + maxBounds + 1) / 2;
        if (subRepartitionString[index] == lower)
        {
            maxBounds = halfBound;
        }
        else if (subRepartitionString[index] == higher)
        {
            minBounds = halfBound;
        }

        index++;
    } 
    while (index < subRepartitionString.size() && minBounds != maxBounds);

    return minBounds;
}

/// <summary>
/// Find the highest seat ID on a boarding pass in the plane.
/// Used dichotomie to solve it.
/// 
/// Note: I could translate each string into binary digit and use the base 2 to compute the actual number.
///       Doing this avoid to do a binary search at all. just string replace and base 2 from base 10 computation.
/// </summary>
int ComputeSeatID(string binarySpaceRepart)
{
    // 2^7 (size of the string) = 128 (which fit the min and max bounds)
    string rowRepartition = binarySpaceRepart.substr(0, 7);
    int row = ComputeRowOrColumn('F', 'B', 0, 127, rowRepartition);

    // 2^3 (size of the string) = 8 (which fit the min and max bounds)
    string columnRepartition = binarySpaceRepart.substr(7, 3);
    int column = ComputeRowOrColumn('L', 'R', 0, 7, columnRepartition);

    return row * 8 + column;
}