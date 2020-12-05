// Day5-BinaryBoarding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "../Utils/Utils.h"
#include "../Utils/Utils.cpp"

using namespace std;


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

int ComputeSeatID(string binarySpaceRepart)
{
    string rowRepartition = binarySpaceRepart.substr(0, 7);
    //cout << rowRepartition << endl;
    int row = ComputeRowOrColumn('F', 'B', 0, 127, rowRepartition);

    string columnRepartition = binarySpaceRepart.substr(7, 3);
    //cout << columnRepartition << endl;
    int column = ComputeRowOrColumn('L', 'R', 0, 7, columnRepartition);

    return row * 8 + column;
}


int main()
{
    string* lines = new string[850];

    int nbLines = Utils::CreateStringArrayFromInputFile("input.txt", lines);
    cout << nbLines << endl;

    int maxSeatIDFound = -1;
    int minSeatIDFound = -1;
    int sumOfSeatID = 0;

    for (size_t i = 0; i < nbLines; i++)
    {
        int seatID = ComputeSeatID(*lines);

        // Find the max for part 1 and 2
        if (maxSeatIDFound == -1 || maxSeatIDFound < seatID)
        {
            maxSeatIDFound = seatID;
        }

        // Find the min for part 2
        if (minSeatIDFound == -1 || minSeatIDFound > seatID)
        {
            minSeatIDFound = seatID;
        }

        sumOfSeatID += seatID;

        lines++;
    }

    cout << "Resulat of part 1 is " << maxSeatIDFound << endl;

    // We want to include the last seat in our calculation so we substract one.
    minSeatIDFound -= 1;

    // Use the triangular number to solve part 2
    int computedSumOfAllSeatIDs = ((maxSeatIDFound*(maxSeatIDFound+1))/2) - ((minSeatIDFound*(minSeatIDFound+1))/2);
    int part2Result = computedSumOfAllSeatIDs - sumOfSeatID;
    cout << "Resulat of part 2 is " << part2Result << endl;
}