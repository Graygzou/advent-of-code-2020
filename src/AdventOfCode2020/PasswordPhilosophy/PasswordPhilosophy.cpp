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

bool IsPasswordLegitPart1(int minBound, int maxBound, int nbOccurences)
{
    return minBound <= nbOccurences && nbOccurences <= maxBound;
}

bool IsPasswordLegitPart2(int index1, int index2, string password, const char& charToFind)
{
    return password[index1 - 1] == charToFind && password[index2 - 1] != charToFind;
}

void GetInputsFromPassword(string line, string* password, int* minBound, int* maxBound, string* charToFind)
{
    string spaceDelimiter = " ";
    int firstIndexOfDelimiter = line.find_first_of(spaceDelimiter);
    string bornesPolicy = line.substr(0, firstIndexOfDelimiter);

    getBoundsPolicy(bornesPolicy, minBound, maxBound);
    //cout << minBound << endl;
    //cout << maxBound << endl;

    *charToFind = line.substr(firstIndexOfDelimiter + 1, 1);
    //cout << "char to find " << charToFind << endl;

    *password = line.substr(firstIndexOfDelimiter + 4);
}

bool ComputeIfPasswordLegitPart1(string line)
{
    int minBound = -1;
    int maxBound = -1;
    string* password = new string;
    string* charToFind = new string;
    GetInputsFromPassword(line, password, &minBound, &maxBound, charToFind);

    int nbOccurences = CountOccurenceOfCharInPassword(*password, *(*charToFind).c_str());

    delete password;
    delete charToFind;

    return IsPasswordLegitPart1(minBound, maxBound, nbOccurences);
}

bool ComputeIfPasswordLegitPart2(string line)
{
    int minBound = -1;
    int maxBound = -1;
    string* password = new string;
    string* charToFind = new string;
    GetInputsFromPassword(line, password, &minBound, &maxBound, charToFind);

    bool result = IsPasswordLegitPart2(minBound, maxBound, *password, *charToFind->c_str())
        || IsPasswordLegitPart2(maxBound, minBound, *password, *charToFind->c_str());

    delete password;
    delete charToFind;

    return result;
}

int main()
{
    // TESTS
    string test = "9-12 q: qqqxhnhdmqqqqjz";
    if (ComputeIfPasswordLegitPart1(test))
    {
        cout << "Password legit for part 1 !" << endl;
    }

    test = "1-3 a: abcde";
    if (ComputeIfPasswordLegitPart2(test))
    {
        cout << "Password legit for part 2 !" << endl;
    }
    // END TESTS

    cout << "===== Password Philosophy" << endl;

    string* array = new string[1000];
    int arrayLength = Utils::CreateStringArrayFromInputFile("input.txt", array);

    int nbPasswordLegitPart1 = 0;
    int nbPasswordLegitPart2 = 0;
    for (size_t i = 0; i < arrayLength; i++)
    {
        if (ComputeIfPasswordLegitPart1(array[i]))
        {
            nbPasswordLegitPart1++;
        }

        if (ComputeIfPasswordLegitPart2(array[i]))
        {
            nbPasswordLegitPart2++;
        }
    }

    cout << "Result Part 1 is " << nbPasswordLegitPart1 << endl;
    cout << "Result Part 2 is " << nbPasswordLegitPart2 << endl;
}