// Day10-AdapterArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

int ComputeFollowingGroup(vector<int> followingNumbers, int maxNumber)
{
    int result = 0;

    int i = 0;
    vector<int> temp = vector<int>();
    vector<int> save = vector<int>();

    // DEBUG: Display
    cout << "Display vector" << endl;
    for (size_t i = 0; i < followingNumbers.size(); i++)
    {
        cout << followingNumbers[i] << endl;
    }
    cout << "end" << endl;
    cout << "max number is " << maxNumber << endl;
    // END DEBUG
    cout << "Length of vector is " << followingNumbers.size() << endl;

    int currentNumber = 1;

    temp.push_back(followingNumbers[0]);
    save.push_back(followingNumbers[0]);

    int globalIndex = 0;
    while (!temp.empty())
    {
        cout << "TEMP AND size of temp " << temp.size() << " ==> ";
        for (size_t i = 0; i < temp.size(); i++)
        {
            cout << temp[i] << ", ";
        }
        cout << endl;

        cout << "SAVE AND size of temp " << save.size() << " ==> ";
        for (size_t i = 0; i < save.size(); i++)
        {
            cout << save[i] << ", ";
        }
        cout << endl;

        currentNumber = temp[0];

        cout << "current number is " << currentNumber << endl;

        // can continue iterating
        temp.erase(temp.begin());

        if (currentNumber + 1 <= maxNumber)
        {
            //save.pop_back();

            cout << "Index found " << globalIndex << endl;
           
            // found following number index
            int followingNumberIndex = 0;
            for (size_t i = 0; i < followingNumbers.size(); i++)
            {
                if (followingNumbers[i] == currentNumber)
                {
                    followingNumberIndex = i;
                }
            }

            if (followingNumberIndex + 1 < followingNumbers.size())
            {
                temp.push_back(followingNumbers[followingNumberIndex + 1]);
                save.push_back(followingNumbers[followingNumberIndex + 1]);
            }
            
            if (followingNumberIndex + 2 < followingNumbers.size())
            {
                temp.push_back(followingNumbers[followingNumberIndex + 2]);
                save.push_back(followingNumbers[followingNumberIndex + 2]);
            }

            if (followingNumberIndex + 3 < followingNumbers.size())
            {
                temp.push_back(followingNumbers[followingNumberIndex + 3]);
                save.push_back(followingNumbers[followingNumberIndex + 3]);
            }
        }
        else
        {
            cout << "score !" << endl;
            //temp.pop_back();
            result++;
            //save.push_back(currentNumber);
        }
       /* else if (currentNumber - 1 > minNumber)
        {
            temp.pop_back();
            temp.push_back(followingNumbers[i + 1]);
        }*/
    }


    for (size_t i = 0; i < temp.size(); i++)
    {
        cout << temp[i] << endl;
    }
    cout << "end" << endl;
    cout << "Length of vector is " << temp.size() << " result is " << result << endl;
    cout << "Test with save " << save.size() << endl;
    return result;
}


int main()
{
    vector<int> adapters = vector<int>();

    int nbOneJoltDiff = 0;
    int nbTwoJoltDiff = 0;
    int nbThreeJoltsDiff = 0;

    long long resultPart2 = 1;

    string line;
    ifstream  myfile;

    myfile.open("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line.c_str() << endl;
            adapters.push_back(atoi(line.c_str()));
        }
    }
    myfile.close();

    adapters.push_back(0);

    sort(adapters.begin(), adapters.end());

    vector<int> numbers = vector<int>();

    int currentDiffPath = 1;
    int currentNumber = 0;
    for (int i = 0; i < adapters.size() - 1; i++)
    {
        currentNumber = adapters[i];
        int nextNumber = adapters[i+1];

        /*int secondNextNumber = 0;
        if (i - 2 >= 0)
        {
            secondNextNumber = adapters[i-2];
        }

        int thirdNextNumber = 0;
        if (i - 3 >= 0)
        {
            thirdNextNumber = adapters[i-3];
        }*/
        cout << "end" << endl;

        int joltDiff = nextNumber - currentNumber;
        nbOneJoltDiff = joltDiff == 1 ? nbOneJoltDiff + 1 : nbOneJoltDiff;
        nbTwoJoltDiff = joltDiff == 2 ? nbTwoJoltDiff + 1 : nbTwoJoltDiff;
        nbThreeJoltsDiff = joltDiff == 3 ? nbThreeJoltsDiff + 1 : nbThreeJoltsDiff;

        cout << joltDiff << endl;
        if (joltDiff == 3)
        {
            cout << "Push last number " << currentNumber << endl;
            numbers.push_back(currentNumber);

            int combinaisons = ComputeFollowingGroup(numbers, currentNumber);

            cout << "Break ! Result is " << combinaisons << endl;
            resultPart2 *= combinaisons;

            numbers.clear();
        }
        else if (joltDiff == 1)
        {
            cout << "Push number " << currentNumber << endl;
            numbers.push_back(currentNumber);

            /*int currentSum = 0;
            cout << "Start ! because " << joltDiff << endl;
            if (i-2 >=0 && (currentNumber - secondNextNumber) == 2)
            {
                currentSum++;
            }
            if (i-3 >= 0 && (currentNumber - thirdNextNumber) == 3)
            {
                currentSum+=2;
            }
            cout << "sum is " << currentSum << endl;

            if (currentSum > 0)
            {
                currentDiffPath *= currentSum;
            }*/
        }

        cout << "end" << endl;
    }

    if (numbers.size() > 0)
    {
        currentNumber = adapters[adapters.size() - 1];
        cout << "Push last number " << currentNumber << endl;
        numbers.push_back(currentNumber);
        int combinaisons = ComputeFollowingGroup(numbers, currentNumber);

        cout << "Break ! Result is " << combinaisons << endl;
        resultPart2 *= combinaisons;
    }

    // our device's built-in adapter is always 3 higher than the highest adapter
    nbThreeJoltsDiff++;

    cout << "Nb two joft " << nbTwoJoltDiff << endl;

    cout << "Result for part1 is : " << nbOneJoltDiff * nbThreeJoltsDiff << endl;
    cout << "Result for part2 is : " << resultPart2 << endl;
}
