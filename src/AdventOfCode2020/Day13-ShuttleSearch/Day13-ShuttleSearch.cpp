// Day13-ShuttleSearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

pair<int, int> FindEarlistedAirportBus(string busSchedule, int earlistDepartPossible);
unsigned long long SolveEquationWithChineseRemainderTheoreme(string busSchedule);

int main()
{
    std::cout << "Day 13 - Shuttle Search" << endl;

    ifstream file;
    file.open("input.txt");
    if (file.is_open())
    {
        int earliestTimestamp = -1;

        int lineNumber = 0;
        string line("");
        while (getline(file, line))
        {
            if (lineNumber == 0)
            {
                earliestTimestamp = atoi(line.c_str());
                lineNumber++;
            }
            else
            {
                pair<int, int> earliestBusIDAndWaitingTime = FindEarlistedAirportBus(line, earliestTimestamp);
                int resultPart1 = earliestBusIDAndWaitingTime.first * earliestBusIDAndWaitingTime.second;
                std::cout << "Part 1 result = " << resultPart1 << endl;

                unsigned long long resultPart2 = SolveEquationWithChineseRemainderTheoreme(line);
                std::cout << "Part 2 result = " << resultPart2 << endl;
            }
        }
    }
}

pair<int, int> FindEarlistedAirportBus(string busSchedule, int earlistDepartPossible)
{
    int busID(0);
    int waitingTime(0);

    int earlistLeavingTimestamp(INT32_MAX);
    string delimiter(",");

    int startingIndex(0);

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
            // Only need to study the earliest time mod the bus ID and pick the lowest one.
            // Waiting time is then trivial to compute.
            int currentTime = atoi(busTime.c_str());
            int totalTimeBeforeNextBus = currentTime - (earlistDepartPossible % currentTime);
            if (totalTimeBeforeNextBus < earlistLeavingTimestamp)
            {
                busID = currentTime;
                earlistLeavingTimestamp = totalTimeBeforeNextBus;
                waitingTime = totalTimeBeforeNextBus;
            }
        }

        // Update evertyhing
        busSchedule = busSchedule.substr(nextDelimiterIndex + 1, busSchedule.size() - 1);

        startingIndex = nextDelimiterIndex++;
        nextDelimiterIndex = busSchedule.find(delimiter);
    }

    return make_pair(busID, waitingTime);
}

void ExtractDataFromLine(string busSchedule, vector<int>* busIDs, vector<int>* offsets)
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
        nextDelimiterIndex = busSchedule.find(delimiter);
    }
}

unsigned long long inverse(unsigned long long number, int mod)
{
    signed long long t = 0, newt = 1;
    signed long long r = mod, newr = number;
    
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
}

unsigned long long SolveEquationWithChineseRemainderTheoreme(string busSchedule)
{
    vector<int> busIDs;
    vector<int> offsets;
    ExtractDataFromLine(busSchedule, &busIDs, &offsets);

    // Apply the Chinese remainder theorem
    // See https://en.wikipedia.org/wiki/Chinese_remainder_theorem
    unsigned long long productOfMod = 1;
    for (size_t i = 0; i < busIDs.size(); i++)
    {
        productOfMod *= busIDs[i];
    }

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
        result += static_cast<unsigned long long>(realOffset * currentE);
    }

    // We want the smallest answer so apply the modulo directly.
    result %= productOfMod;
    return result;
}