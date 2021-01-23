// Day10-AdapterArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <stack>

using namespace std;

vector<int> RetrieveAdapterVoltageFromFile(string fileName);
int ComputeFollowingGroup(vector<int> arrangementSegment, int maxNumber);

int main(int argc, char** argv)
{
    cout << "Day 10 - Adapter Array" << endl;

    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }

    vector<int> adapters = RetrieveAdapterVoltageFromFile(fileName);
    map<int, int> numberOfSameJoltDiff = map<int, int>
    {
        make_pair(1,0),
        make_pair(2,0),
        make_pair(3,0),
    };

    // Add the charing outlet voltage
    adapters.push_back(0);

    sort(adapters.begin(), adapters.end());

    long long numberOfDistinctCombinaisons = 1;
    vector<int> currentArrangement = vector<int>();
    for (int i = 0; i < adapters.size() - 1; i++)
    {
        int currentNumber = adapters[i];

        int currentJoltDiff = adapters[i + 1] - currentNumber;
        numberOfSameJoltDiff[currentJoltDiff] += 1;

        // if the currentJoltDiff is three, we're guaranteed that all arrangements will have it.
        // We can study how many possibilities will generate the segment of arrangement we gather.
        currentArrangement.push_back(currentNumber);
        if (currentJoltDiff == 3)
        {
            // The segment arrangement can be found "N" times where N is the result of the function.
            numberOfDistinctCombinaisons *= ComputeFollowingGroup(currentArrangement, currentNumber);
            currentArrangement.clear();
        }
    }

    // our device's built-in adapter is always 3 higher than the highest adapter
    numberOfSameJoltDiff[3]++;
    cout << "Result for part 1 is : " << numberOfSameJoltDiff[1] * numberOfSameJoltDiff[3] << endl;

    // Apply to last arrangement
    int lastNumber = adapters[adapters.size() - 1];
    currentArrangement.push_back(lastNumber);
    numberOfDistinctCombinaisons *= ComputeFollowingGroup(currentArrangement, lastNumber);
    cout << "Result for part 2 is : " << numberOfDistinctCombinaisons << endl;
}

void DisplayVoltageRating(vector<int> voltageRating)
{
    cout << "Display vector - Size = " << voltageRating.size() << endl;
    for (size_t i = 0; i < voltageRating.size(); i++)
    {
        cout << voltageRating[i] << ", ";
    }
    cout << endl;
}

/// <summary>
/// /!\ WARNING: This function required following numbers to be sorted.
/// </summary>
int ComputeFollowingGroup(vector<int> arrangementSegment, int maxNumber)
{
    int nbDistinctArrangementsForSegment = 0;

    const int minVoltageDiff = 1;
    const int maxVoltageDiff = 3;

    stack<int> chargersLeft = stack<int>();
    chargersLeft.push(arrangementSegment[0]);

    while (!chargersLeft.empty())
    {
        int currentNumber = chargersLeft.top();
        chargersLeft.pop();

        if (currentNumber == maxNumber)
        {
            nbDistinctArrangementsForSegment++;
        }
        else
        {
            // find the index of the current number to add his 
            int followingNumberIndex = 0;
            for (size_t i = 0; i < arrangementSegment.size(); i++)
            {
                if (arrangementSegment[i] == currentNumber)
                {
                    followingNumberIndex = i;
                    break;
                }
            }

            for (size_t offset = minVoltageDiff; offset <= maxVoltageDiff; offset++)
            {
                if (followingNumberIndex + offset < arrangementSegment.size())
                {
                    chargersLeft.push(arrangementSegment[followingNumberIndex + offset]);
                }
            }
        }
    }

    return nbDistinctArrangementsForSegment;
}

vector<int> RetrieveAdapterVoltageFromFile(string fileName)
{
    vector<int> adapterVotages = vector<int>();

    ifstream myfile;
    myfile.open(fileName);
    if (!myfile.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    string line;
    while (getline(myfile, line))
    {
        adapterVotages.push_back(atoi(line.c_str()));
    }
    myfile.close();

    return adapterVotages;
}