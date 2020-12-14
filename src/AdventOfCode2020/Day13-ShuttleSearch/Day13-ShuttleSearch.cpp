// Day13-ShuttleSearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int FindEarlistedAirportBus(string busSchedule, int earlistDepartPossible, int *waitingTime)
{
    int busID(0);
    int earlistLeavingTimestamp(INT32_MAX);
    string delimiter(",");

    int startingIndex(0);

    while (busSchedule.size() > 0)
    {   
        string busTime("");
        int nextDelimiterIndex = busSchedule.find(delimiter);

        cout << nextDelimiterIndex << endl;
        if (nextDelimiterIndex != string::npos)
        {
            busTime = busSchedule.substr(0, nextDelimiterIndex);
        }
        else
        {
            busTime = busSchedule;
            nextDelimiterIndex = busSchedule.size() - 1;
        }

        if (busTime != "x")
        {
            int currentTime = atoi(busTime.c_str());
            cout << currentTime << endl;

            int totalTimeBeforeNextBus = currentTime - (earlistDepartPossible % currentTime);
            //cout << "Calculation for bus is " << totalTimeBeforeNextBus << endl;
            if (totalTimeBeforeNextBus < earlistLeavingTimestamp)
            {
                busID = currentTime;
                earlistLeavingTimestamp = totalTimeBeforeNextBus;
                *waitingTime = totalTimeBeforeNextBus;
            }

            //cout << "Result is " << earlistLeavingTimestamp << endl;
        }

        // Update evertyhing
        busSchedule = busSchedule.substr(nextDelimiterIndex + 1, busSchedule.size() - 1);
        cout << busSchedule << endl;

        startingIndex = nextDelimiterIndex++;
        nextDelimiterIndex = busSchedule.find(delimiter);
    }

    return busID;
}

long long FindEarliestTimestampForDepartureOffset(string busSchedule)
{
    int timestampFound = 0;

    // This create a simple group since all numbers are prime in inputs.
    vector<int> busIDs;
    vector<int> offsets;
    int maxIDFound = 0;
    int maxIDIndex = 0;

    int currentIndex(0);
    int startingIndex(0);
    string delimiter(",");
    while (busSchedule.size() > 0)
    {
        string busTime("");
        int nextDelimiterIndex = busSchedule.find(delimiter);

        if (nextDelimiterIndex != string::npos)
        {
            busTime = busSchedule.substr(0, nextDelimiterIndex);
        }
        else
        {
            busTime = busSchedule;
            nextDelimiterIndex = busSchedule.size() - 1;
        }

        if (busTime != "x")
        {
            int currentBusID = atoi(busTime.c_str());
            busIDs.push_back(currentBusID);
            offsets.push_back(currentIndex);

            if (maxIDFound < currentBusID)
            {
                maxIDIndex = currentIndex;
                maxIDFound = currentBusID;
            }
        }

        currentIndex++;

        // Update evertyhing
        busSchedule = busSchedule.substr(nextDelimiterIndex + 1, busSchedule.size() - 1);
        cout << busSchedule << endl;

        startingIndex = nextDelimiterIndex++;
        nextDelimiterIndex = busSchedule.find(delimiter);
    }

    /*for (size_t i = 0; i < busIDs.size(); i++)
    {
        cout << busIDs[i] << " / ";
        cout << offsets[i] << ", ";
    }
    cout << endl;*/

    cout << maxIDFound << endl;
    cout << maxIDIndex << endl;


    long long loopCount = 0;
    bool found = false;

    long long currentNumber = 0;
    while (loopCount < 10000000000 && !found /*currentNumber < 1068797*/)
    {
        found = true;
        for (int i = 0; found && i < busIDs.size(); i++)
        {
            //cout << currentNumber % busIDs[i] << " VS " << abs(i - maxIDIndex) << endl;

            int currentBusOffset = currentNumber % busIDs[i];
            int absIndexGap = abs(offsets[i] - maxIDIndex);

            if (i <= maxIDIndex && currentBusOffset != absIndexGap ||
                i > maxIDIndex && currentBusOffset != busIDs[i] - absIndexGap)
            {
                found = false;
                currentNumber += maxIDFound;
            }
        }

        //cout << currentNumber << endl;
        loopCount++;
    }
    
    if (!found)
    {
        cout << currentNumber << endl;
        return -1;
    }

    cout << "RESULTTTTTT " << currentNumber << endl;
    timestampFound = currentNumber - maxIDIndex;
    return timestampFound;
}

int main()
{
    std::cout << "Shuttle Search" << endl;
    int resultPart1(0);
    long long resultPart2(0);

    ifstream file;
    file.open("example1.txt");
    if (file.is_open())
    {
        int earliestTimestamp = -1;

        int index = 1;
        string line("");
        while (getline(file, line))
        {
            if (index == 0)
            {
                earliestTimestamp = atoi(line.c_str());
                cout << earliestTimestamp << endl;
            }
            else
            {
                //int waitingTime = 0;
                //int earliestBusID = FindEarlistedAirportBus(line, earliestTimestamp, &waitingTime);

                resultPart2 = FindEarliestTimestampForDepartureOffset(line);

                //resultPart1 = earliestBusID * waitingTime;
            }
            //cout << "POSITION IS NOW " << positionPart2.first << ", " << positionPart2.second << endl;
            //cout << "DIRECTION IS NOW " << waypoint.first << ", " << waypoint.second << endl;
        }
    }

    std::cout << "Part 1 result " << resultPart1 << endl;
    std::cout << "Part 2 result " << resultPart2 << endl;
}