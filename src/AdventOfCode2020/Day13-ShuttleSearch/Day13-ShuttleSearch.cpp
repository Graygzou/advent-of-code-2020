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

void ExtractDataFromLine(string busSchedule, vector<int> *busIDs, vector<int> *offsets)
{
    int currentIndex(0);
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
            busIDs->push_back(currentBusID);
            offsets->push_back(currentIndex);
        }

        currentIndex++;

        // Update evertyhing
        busSchedule = busSchedule.substr(nextDelimiterIndex + 1, busSchedule.size() - 1);
        cout << busSchedule << endl;

        //startingIndex = nextDelimiterIndex++;
        nextDelimiterIndex = busSchedule.find(delimiter);
    }
}

unsigned long long inverse(unsigned long long number, int mod)
{
    signed long long t = 0;
    signed long long newt = 1;
    signed long long r = mod;
    signed long long newr = number;
    
    while (newr != 0)
    {
        signed long long quotient = r / newr;

        // Update left bezout coef
        signed long long temp = t;
        t = newt;
        newt = temp - quotient * newt;

        // Update remainders
        temp = r;
        r = newr;
        newr = temp - quotient * newr;



        // Update right bezout coef
        //temp = previousRightBezoutCoef;
        //previousRightBezoutCoef = rightBezoutCoef;
        //rightBezoutCoef = temp - quotient * rightBezoutCoef;
    }

    if (r > 1)
    {
        cout << "number " << number << " is not inversible by mod " << mod << endl;
        return 0;
    }

    // We always want a positive answer.
    if (t < 0)
    {
        t += mod;
    }

    return t;

    //cout << "Bezout coefficients:" << leftBezoutCoef << "," << previousRightBezoutCoef << endl;
    //cout << "greatest common divisor:" << previousRemainder << endl;
    //cout << "quotients by the gcd:" << rightBezoutCoef << "," << leftBezoutCoef << endl;

    //return rightBezoutCoef;
}

unsigned long long ComputePart2(string busSchedule)
{
    vector<int> busIDs/*{3, 5, 7}*/;
    vector<int> offsets/*{2,3,2}*/;
    ExtractDataFromLine(busSchedule, &busIDs, &offsets);

    cout << "Offsets " << endl;
    for (size_t i = 0; i < offsets.size(); i++)
    {
        cout << offsets[i] << endl;
    }
    cout << endl;

    cout << "Bus IDS" << endl;

    // Apply the Chinese remainder theorem
    // See https://en.wikipedia.org/wiki/Chinese_remainder_theorem
    unsigned long long productOfMod = 1;
    for (size_t i = 0; i < busIDs.size(); i++)
    {
        cout << busIDs[i] << endl;
        productOfMod *= busIDs[i];
    }
    cout << "sumOfMod: " << productOfMod << endl;

    unsigned long long result = 0;
    for (size_t i = 0; i < busIDs.size(); i++)
    {
        unsigned long long n1 = busIDs[i];
        unsigned long long n1hat = productOfMod / busIDs[i];
        unsigned long long currentE = inverse(n1hat, n1) * n1hat;

        int rangedOffset = offsets[i];
        if (rangedOffset > n1)
        {
            rangedOffset = offsets[i] % n1;
        }

        unsigned long long realOffset = rangedOffset == 0 ? rangedOffset : n1 - rangedOffset;

        cout << "n1: " << n1 << endl;
        cout << "n1hat: " << n1hat << endl;
        cout << "inverse: " << inverse(n1hat, n1) << endl;
        cout << "offsets: " << realOffset << endl;
        cout << "currentE: " << currentE << endl;
        cout << realOffset * currentE << endl;
        result += static_cast<unsigned long long>(realOffset * currentE);
        cout << "result" << result << endl;
    }

    result %= productOfMod;

    // Check if it's true
    cout << "==========================" << endl;
    for (size_t i = 0; i < busIDs.size(); i++)
    {
        cout << "Bus ID " << busIDs[i] << endl;
        cout << "result is " << result % busIDs[i] << endl;
        cout << "offset is " << busIDs[i] - offsets[i] << endl;
    }
    cout << "==========================" << endl;

    // We want the smallest answer so apply the modulo directly.
    return result;
}

int main()
{
    string fileName = "input.txt";
    std::cout << "Shuttle Search" << endl;
    int resultPart1(0);
    unsigned long long resultPart2(0);

    ifstream file;
    file.open(fileName);
    if (file.is_open())
    {
        int earliestTimestamp = -1;

        int index = 0;
        string line("");
        while (getline(file, line))
        {
            if (index == 0)
            {
                earliestTimestamp = atoi(line.c_str());
                index++;
            }
            else
            {
                //int waitingTime = 0;
                //int earliestBusID = FindEarlistedAirportBus(line, earliestTimestamp, &waitingTime);
                //resultPart1 = earliestBusID * waitingTime;

                resultPart2 = ComputePart2(line);
            }
        }
    }

    std::cout << "Part 1 result " << resultPart1 << endl;
    std::cout << "Part 2 result " << resultPart2 << endl;
}