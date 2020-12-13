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

int FindEarliestTimestampForDepartureOffset(string busSchedule)
{
    vector<int> times;

}

int main()
{
    std::cout << "Shuttle Search" << endl;
    int resultPart1(0);

    ifstream file;
    file.open("input.txt");
    if (file.is_open())
    {
        int earliestTimestamp = -1;

        int index = 0;
        string line("");
        while (getline(file, line))
        {
            if (earliestTimestamp == -1)
            {
                earliestTimestamp = atoi(line.c_str());
                cout << earliestTimestamp << endl;
            }
            else
            {
                int waitingTime = 0;
                int earliestBusID = FindEarlistedAirportBus(line, earliestTimestamp, &waitingTime);

                int resultPart2 = FindEarliestTimestampForDepartureOffset(line);

                resultPart1 = earliestBusID * waitingTime;
            }
            //cout << "POSITION IS NOW " << positionPart2.first << ", " << positionPart2.second << endl;
            //cout << "DIRECTION IS NOW " << waypoint.first << ", " << waypoint.second << endl;
        }
    }

    std::cout << "Part 1 result " << resultPart1 << endl;
}