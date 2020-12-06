// Day6-CustomCustoms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

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

    //std::cout << "For " << nbPersonInGroup << " person answers are = " << *concatenatedAnswers << endl;
    return nbPersonInGroup;
}


#pragma region Functions for part 1
int ComputeGroupPositiveAnswers(ifstream* fileStream)
{
    int totalPositiveAnswers = 0;

    string concatenatedAnswers = "";
    ConcatenateGroupAnswers(fileStream, &concatenatedAnswers);

    for (size_t i = 'a'; i <= 'z'; i++)
    {
        totalPositiveAnswers += concatenatedAnswers.find(i) != string::npos ? 1 : 0;
    }

    return totalPositiveAnswers;
}

int CountCumulatedGroupsPositiveAnswers(ifstream* fileStream)
{
    int cumulativeGroupAnswers = 0;
    string line;
    do
    {
        cumulativeGroupAnswers += ComputeGroupPositiveAnswers(fileStream);
    } while (!fileStream->eof());

    std::cout << "cumulative group " << cumulativeGroupAnswers << endl;
    return cumulativeGroupAnswers;
}
#pragma endregion


#pragma region Functions for part 2
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

int CountCumulatedGroupsPositiveAnswersForEveryone(ifstream* fileStream)
{
    int cumulativeGroupAnswers = 0;
    string line;
    do
    {
        cumulativeGroupAnswers += ComputeGroupPositiveAnswersForEveryone(fileStream);
    } while (!fileStream->eof());

    std::cout << "cumulative group " << cumulativeGroupAnswers << endl;
    return cumulativeGroupAnswers;
}
#pragma endregion


int main()
{
    std::cout << "Custom Customes" << endl;

    const char* fileName = "input.txt";

    int part1Result = 0;
    int part2Result = 0;

    ifstream  fileStream;
    fileStream.open(fileName);
    if (fileStream.is_open())
    {
        // Part 1
        part1Result = CountCumulatedGroupsPositiveAnswers(&fileStream);
        std::cout << "Part 1 result is " << part1Result << endl;

        // Start again at the beginning of the file
        fileStream.clear();
        fileStream.seekg(ios::beg);

        // Part 2
        part2Result = CountCumulatedGroupsPositiveAnswersForEveryone(&fileStream);
        std::cout << "Part 2 result is " << part2Result << endl;
    }
    fileStream.close();

    
    
}