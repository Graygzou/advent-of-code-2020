// Day12-RainRisk.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <cmath>

using namespace std;

static double degreeToRadian(double d) {
    return (d / 180.0) * ((double)M_PI);
}

void SumPair(pair<int, int>* pair1, pair<int, int> pair2, int amount)
{
    pair1->first += pair2.first * amount;
    pair1->second += pair2.second * amount;
}

pair<int, int> GetOffsetPosition(string instructionLettre)
{
    pair<int, int> offset = make_pair(0, 0);
    if (instructionLettre == "N")
    {
        offset.second = 1;
    }
    else if (instructionLettre == "S")
    {
        offset.second = -1;
    }
    else if (instructionLettre == "E")
    {
        offset.first = 1;
    }
    else if (instructionLettre == "W")
    {
        offset.first = -1;
    }

    return offset;
}

void ApplyNavigationInstruction(string instruction, pair<int, int> *position, pair<int,int> *direction)
{
    cmatch cm;
    regex e("([A-Z])([0-9]*)");
    regex_match(instruction.c_str(), cm, e);

    string instructionLetter = cm[1].str();
    double amount = atoi(cm[2].str().c_str());

    cout << instructionLetter << " " << amount << endl;

    if (instructionLetter == "F")
    {
        SumPair(position, *direction, amount);
    }
    else if (instructionLetter == "N" || instructionLetter == "S" || instructionLetter == "E" || instructionLetter == "W")
    {
        pair<int, int> offeset = GetOffsetPosition(instructionLetter);
        SumPair(position, offeset, amount);
    }
    else if (instructionLetter == "R" || instructionLetter == "L")
    {
        if (instructionLetter == "R")
        {
            amount *= -1;
        }

        amount = degreeToRadian(amount);

        // Apply rotation matrix 2d
        int previousX = direction->first;
        int previousY = direction->second;
        direction->first = previousX * cos(amount) - previousY * sin(amount);
        direction->second = previousX * (int)sin(amount) + previousY * cos(amount);
    }
}


int main()
{
    // Starting position
    pair<int, int> startingPosition = make_pair(0, 0);
    // Start east
    pair<int, int> direction = make_pair(1, 0);

    string line;
    ifstream  myfile;

    pair<int, int> position = startingPosition;
    myfile.open("input.txt");
    if (myfile.is_open())
    {
        int lineIndex = 0;
        while (getline(myfile, line))
        {
            cout << line.c_str() << endl;

            ApplyNavigationInstruction(line.c_str(), &position, &direction);

            //cout << "POSITION IS NOW " << position.first << ", " << position.second << endl;
            //cout << "DIRECTION IS NOW " << direction.first << ", " << direction.second << endl;
        }
    }
    myfile.close();

    int manhattanDistanceFromStart = abs(startingPosition.first - position.first) + abs(startingPosition.second - position.second);
    std::cout << "Part 1 result is " << manhattanDistanceFromStart << endl;;
}
