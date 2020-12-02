// PasswordPhilosophy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "../Utils/Utils.h"
#include "../Utils/Utils.cpp"

using namespace std;

void getBoundsPolicy(string line, int* minBound, int* maxBound)
{
    string spaceDelimiter = "-";

    int firstIndexOfDelimiter = line.find_first_of(spaceDelimiter);
    *minBound = std::atoi(line.substr(0, firstIndexOfDelimiter).c_str());
    *maxBound = std::atoi(line.substr(firstIndexOfDelimiter + 1, line.length()).c_str());
}

int CountOccurenceOfCharInPassword(string password, const char& charToFind)
{
    int count = 0;
    for (size_t i = 0; i < password.length(); i++)
    {
        count = password[i] == charToFind ? count + 1 : count;
    }

    return count;
}

bool IsPasswordLegit(int minBound, int maxBound, int nbOccurences)
{
    return minBound <= nbOccurences && nbOccurences <= maxBound;
}

bool ComputeIfPasswordLegit(string password)
{
    string spaceDelimiter = " ";

    int firstIndexOfDelimiter = password.find_first_of(spaceDelimiter);
    string bornesPolicy = password.substr(0, firstIndexOfDelimiter);

    int minBound = -1;
    int maxBound = -1;
    getBoundsPolicy(bornesPolicy, &minBound, &maxBound);

    //cout << minBound << endl;
    //cout << maxBound << endl;

    string charToFind = password.substr(firstIndexOfDelimiter + 1, 1);
    //cout << "char to find " << charToFind << endl;

    int nbOccurences = CountOccurenceOfCharInPassword(password.substr(firstIndexOfDelimiter + 3), *charToFind.c_str());

    return IsPasswordLegit(minBound, maxBound, nbOccurences);
}

int main()
{
    // TEST
    /*string test = "9-12 q: qqqxhnhdmqqqqjz";
    if (ComputeIfPasswordLegit(test))
    {
        cout << "Password legit !" << endl;
    }*/
    // END TEST

    cout << "Password Philosophy" << endl;

    int total = 0;

    string* array = new string[1000];
    int arrayLength = Utils::CreateStringArrayFromInputFile("input.txt", array);

    for (size_t i = 0; i < arrayLength; i++)
    {
        if (ComputeIfPasswordLegit(array[i]))
        {
            total++;
        }
    }

    cout << "Result is " << total << endl;
}