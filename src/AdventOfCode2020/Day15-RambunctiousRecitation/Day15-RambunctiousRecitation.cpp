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

    //
    // Run the algo
    //
    int mostRecentSpokenNumber = -1;

    // Store as key the number and has value his last position met.
    map<int, pair<int, int>> wordsSpokenCount;

    for (size_t i = 0; i < numbers.size(); i++)
    {
        //cout << numbers[i] << "Will take the value " << (i + 1) << endl;
        wordsSpokenCount[numbers[i]] = make_pair(i+1, 0);
    }
    mostRecentSpokenNumber = numbers[numbers.size() - 1];

    int turnToReach = 30000000;
    for (size_t turn = numbers.size() + 1; turn <= turnToReach; turn++)
    {
         /*for (auto it = wordsSpokenCount.begin(); it != wordsSpokenCount.end(); it++)
         {
             cout << it->first << " , (" << it->second.first << "," << it->second.second << ")" << endl;
         }**/
        //cout << "Turn " << turn << " - Previous number is " << mostRecentSpokenNumber << endl;

        // first time last number spoken
        if (wordsSpokenCount.at(mostRecentSpokenNumber).second == 0)
        {
            //cout << "FIRST !" << endl;
            //wordsSpokenCount[mostRecentSpokenNumber] = make_pair(turn, 0);
            int numberSpoken = 0;
            wordsSpokenCount[numberSpoken] = make_pair(turn, wordsSpokenCount[numberSpoken].first);

            mostRecentSpokenNumber = numberSpoken;
        }
        else
        {
            /*cout << mostRecentSpokenNumber << endl;
            cout << wordsSpokenCount.at(mostRecentSpokenNumber).first << wordsSpokenCount.at(mostRecentSpokenNumber).second << endl;
           */

            int gap = wordsSpokenCount.at(mostRecentSpokenNumber).first - wordsSpokenCount.at(mostRecentSpokenNumber).second;
            
            //cout << "GAPPP " << gap << endl;

            wordsSpokenCount[gap] = make_pair(turn, wordsSpokenCount[gap].first);
            mostRecentSpokenNumber = gap;
        }

        //cout << "I SAY " << mostRecentSpokenNumber << endl;
    }

    cout << "Result is " << mostRecentSpokenNumber << endl;

}