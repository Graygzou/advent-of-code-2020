// Day12-RainRisk.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <cmath>

using namespace std;

void ApplyNavigationInstruction(string instruction, pair<int, int>* position, pair<int, int>* direction, bool useWaypoint);

int main(int argc, char** argv)
{
    cout << "Day 12 - Rain Risk" << endl;

    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }

    ifstream myfile;
    myfile.open(fileName);
    if (!myfile.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    // Starting position
    pair<int, int> startingPosition = make_pair(0, 0);

    // Part 1
    pair<int, int> positionPart1 = startingPosition;
    pair<int, int> direction = make_pair(1, 0);

    // Part 2
    pair<int, int> positionPart2 = startingPosition;
    pair<int, int> waypoint = make_pair(10, 1);

    string line;
    int lineIndex = 0;
    while (getline(myfile, line))
    {
        ApplyNavigationInstruction(line.c_str(), &positionPart1, &direction, false);
        ApplyNavigationInstruction(line.c_str(), &positionPart2, &waypoint, true);
    }
    myfile.close();

    int manhattanDistanceFromStart = abs(startingPosition.first - positionPart1.first) + abs(startingPosition.second - positionPart1.second);
    std::cout << "Part 1 result is " << manhattanDistanceFromStart << endl;

    int part2Result = abs(startingPosition.first - positionPart2.first) + abs(startingPosition.second - positionPart2.second);
    std::cout << "Part 2 result is " << part2Result << endl;
}

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

void ApplyNavigationInstruction(string instruction, pair<int, int> *position, pair<int,int> *direction, bool useWaypoint)
{
    cmatch cm;
    regex e("([A-Z])([0-9]*)");
    regex_match(instruction.c_str(), cm, e);

    string instructionLetter = cm[1].str();
    double amount = atoi(cm[2].str().c_str());

    if (instructionLetter == "F")
    {
        SumPair(position, *direction, amount);
    }
    else if (instructionLetter == "N" || instructionLetter == "S" || instructionLetter == "E" || instructionLetter == "W")
    {
        pair<int, int> offset = GetOffsetPosition(instructionLetter);
        if (useWaypoint)
        {
            // Part2: Move the waypoint
            SumPair(direction, offset, amount);
        }
        else
        {
            // Part1: Move the ship
            SumPair(position, offset, amount);
        }
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

        direction->first = previousX * round(cos(amount)) - previousY * round(sin(amount));
        direction->second = previousX * round(sin(amount)) + previousY * round(cos(amount));
    }
}