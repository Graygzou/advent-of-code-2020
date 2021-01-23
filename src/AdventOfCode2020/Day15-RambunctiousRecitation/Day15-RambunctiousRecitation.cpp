// Day15-RambunctiousRecitation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> SplitWithDelimiter(string str, string delimiter);
int RunMemoryGame(vector<int> numbers, map<int, pair<int, int>> wordsSpokenCount, int nbTurns);

int main(int argc, char** argv)
{
    cout << "Day 15 - Rambunctious Recitation" << endl;

    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }

    ifstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    vector<int> numbers;
    string line;
    while (getline(file, line))
    {
        numbers = SplitWithDelimiter(line, ",");
    }

    // Store as key the number and has value his last position met.
    map<int, pair<int, int>> wordsSpokenCount;
    for (size_t i = 0; i < numbers.size(); i++)
    {
        wordsSpokenCount[numbers[i]] = make_pair(i + 1, 0);
    }

    // Part 1
    int part1Result = RunMemoryGame(numbers, wordsSpokenCount, 2020);
    cout << "Result Part 1 is " << part1Result << endl;

    // Part 2
    int part2Result = RunMemoryGame(numbers, wordsSpokenCount, 30000000);
    cout << "Result Part 2 is " << part2Result << endl;
}

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

int RunMemoryGame(vector<int> numbers, map<int, pair<int, int>> wordsSpokenCount, int nbTurns)
{
    int mostRecentSpokenNumber = numbers[numbers.size() - 1];

    for (size_t turn = numbers.size() + 1; turn <= nbTurns; turn++)
    {
        // first time last number spoken
        if (wordsSpokenCount.at(mostRecentSpokenNumber).second == 0)
        {
            int numberSpoken = 0;
            wordsSpokenCount[numberSpoken] = make_pair(turn, wordsSpokenCount[numberSpoken].first);

            mostRecentSpokenNumber = numberSpoken;
        }
        else
        {
            int gap = wordsSpokenCount.at(mostRecentSpokenNumber).first - wordsSpokenCount.at(mostRecentSpokenNumber).second;
            wordsSpokenCount[gap] = make_pair(turn, wordsSpokenCount[gap].first);
            mostRecentSpokenNumber = gap;
        }
    }

    return mostRecentSpokenNumber;
}