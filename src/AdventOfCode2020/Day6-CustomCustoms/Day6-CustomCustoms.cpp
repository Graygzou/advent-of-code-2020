// Day6-CustomCustoms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

int CountCumulatedGroupsPositiveAnswers(ifstream* fileStream);
int CountCumulatedGroupsPositiveAnswersForEveryone(ifstream* fileStream);

int main(int argc, char** argv)
{
    std::cout << "Day 6 - Custom Customes" << endl;

    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }

    ifstream  fileStream;
    fileStream.open(fileName);
    if (!fileStream.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    // Part 1
    int part1Result = CountCumulatedGroupsPositiveAnswers(&fileStream);
    std::cout << "Part 1 result is " << part1Result << endl;

    // Start again at the beginning of the file
    fileStream.clear();
    fileStream.seekg(ios::beg);

    // Part 2
    int part2Result = CountCumulatedGroupsPositiveAnswersForEveryone(&fileStream);
    std::cout << "Part 2 result is " << part2Result << endl;

    fileStream.close();
}

int ConcatenateGroupAnswers(ifstream* fileStream, string* concatenatedAnswers)
{
    int nbPersonInGroup = 0;

    string line;
    // A group is composed of at least of 1 person
    getline(*fileStream, line);
    do
    {
        nbPersonInGroup++;
        *concatenatedAnswers += line;
        getline(*fileStream, line);
    } while (!fileStream->eof() && line.size() > 0);

    return nbPersonInGroup;
}

int ComputeGroupPositiveAnswers(ifstream* fileStream)
{
    string concatenatedAnswers = "";
    ConcatenateGroupAnswers(fileStream, &concatenatedAnswers);

    int totalPositiveAnswers = 0;
    for (size_t i = 'a'; i <= 'z'; i++)
    {
        totalPositiveAnswers += concatenatedAnswers.find(i) != string::npos ? 1 : 0;
    }

    return totalPositiveAnswers;
}

/// <summary>
/// count the number of questions to which anyone answered "yes" in a group and sum them.
/// </summary>
/// <returns>The sum of the count</returns>
int CountCumulatedGroupsPositiveAnswers(ifstream* fileStream)
{
    int cumulativeGroupAnswers = 0;
    string line;
    do
    {
        cumulativeGroupAnswers += ComputeGroupPositiveAnswers(fileStream);
    } while (!fileStream->eof());

    return cumulativeGroupAnswers;
}

int ComputeGroupPositiveAnswersForEveryone(ifstream* fileStream)
{
    int totalPositiveAnswersForEveryone = 0;
    string concatenatedAnswers = "";
    string nbPersonInGroupStr = to_string(ConcatenateGroupAnswers(fileStream, &concatenatedAnswers));

    // Sort it, before hand, to simplify the regex search.
    sort(concatenatedAnswers.begin(), concatenatedAnswers.end());

    for (size_t i = 'a'; i <= 'z'; i++)
    {
        // Build a regexp to know if the number of "yes" answers for a question, match the group size.
        char character = static_cast<char>(i);
        std::ostringstream regexpExpr;
        regexpExpr << ".*" << character << "{" << nbPersonInGroupStr << "}.*";

        smatch m;
        regex e(regexpExpr.str());
        totalPositiveAnswersForEveryone += regex_match(concatenatedAnswers, m, e) ? 1 : 0;
    }

    return totalPositiveAnswersForEveryone;
}

/// <summary>
/// Count the number of questions to which everyone answered "yes" and sum them for all the groups.
/// </summary>
/// <returns>The sum of the count</returns>
int CountCumulatedGroupsPositiveAnswersForEveryone(ifstream* fileStream)
{
    int cumulativeGroupAnswers = 0;
    string line;
    do
    {
        cumulativeGroupAnswers += ComputeGroupPositiveAnswersForEveryone(fileStream);
    } while (!fileStream->eof());

    return cumulativeGroupAnswers;
}
#pragma endregion
