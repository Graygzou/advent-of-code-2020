// Day15-RambunctiousRecitation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Should be moved to Utils.cpp
vector<int> SplitWithDelimiter(string str, string delimiter)
{
    vector<int> results = vector<int>();

    int startingIndex(0);
    while (str.size() > 0)
    {
        int nextDelimiterIndex = str.find(delimiter);
        if (nextDelimiterIndex != string::npos)
        {
            results.push_back(atoi(str.substr(0, nextDelimiterIndex).c_str()));
        }
        else
        {
            results.push_back(atoi(str.c_str()));
        }

        // Update evertyhing
        str = str.substr(nextDelimiterIndex + 1, str.size() - 1);
    }

    return results;
}

int main()
{
    ifstream file;
    string line;

    string startingNumbers("");

    file.open("input.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            startingNumbers = line;
        }
    }

    int part1Result = 0;

    string delimiter(",");
    vector<int> numbers = SplitWithDelimiter(startingNumbers, delimiter);

    for (size_t i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i] << endl;
    }

    // Run the algo
    int mostRecentSpokenNumber = -1;
    map<int, int> wordsSpokenCount;
    vector<int> gameHistoric = vector<int>();

    int turnToReach = 2020;
    for (size_t turn = 0; turn < turnToReach; turn++)
    {
        //cout << "Game History" << endl;
        //for (size_t i = 0; i < gameHistoric.size(); i++)
        //{
        //    cout << gameHistoric[i] << endl;
        //}

        if (turn < numbers.size() && gameHistoric.size() < numbers.size())
        {
            mostRecentSpokenNumber = numbers[turn];

            wordsSpokenCount[mostRecentSpokenNumber] = 1;
            gameHistoric.push_back(mostRecentSpokenNumber);
        }
        else
        {
            // first time last number spoken
            auto lastTurnBeforePreviousOneSpokenNumber = find(gameHistoric.begin(), gameHistoric.end() - 1, mostRecentSpokenNumber);
            if (lastTurnBeforePreviousOneSpokenNumber == gameHistoric.end() - 1)
            {
                //cout << "FIRST !" << endl;
                int numberSpoken = 0;

                auto it = wordsSpokenCount.find(numberSpoken);
                if (it != wordsSpokenCount.end())
                {
                    it->second++;
                }
                else
                {
                    wordsSpokenCount[numberSpoken] = 1;
                }

                gameHistoric.push_back(numberSpoken);
                mostRecentSpokenNumber = numberSpoken;
            }
            else
            {
                //cout << "ALREADY" << endl;
                int index = 0;
                for (size_t i = gameHistoric.size() - 2; i >= 0; i--)
                {
                    //cout << gameHistoric[i] << endl;
                    if (gameHistoric[i] == mostRecentSpokenNumber)
                    {
                        index = i + 1;
                        break;
                    }
                }

                //cout << "HERE" << turn << " and " << index << endl;
                // Found the gap
                //auto lastTurnBeforePreviousOneSpokenNumber = find(gameHistoric.rbegin(), gameHistoric.rend(), mostRecentSpokenNumber);
                
                int gap = turn - index;

                //cout << "GAPPP " << gap << endl;


                auto it = wordsSpokenCount.find(gap);
                if (it != wordsSpokenCount.end())
                {
                    it->second++;
                }
                else
                {
                    wordsSpokenCount[gap] = 1;
                }
                
                mostRecentSpokenNumber = gap;
                gameHistoric.push_back(mostRecentSpokenNumber);
            }
        }

        cout << "Turn " << (turn + 1) << " - Previous number is " << mostRecentSpokenNumber << endl;
    }

    /*for (size_t i = 0; i < 5; i++)
    {
        cout << gameHistoric[i] << endl;
    }*/

    cout << gameHistoric.size() << endl;

    cout << "Result is " << mostRecentSpokenNumber << endl;

}