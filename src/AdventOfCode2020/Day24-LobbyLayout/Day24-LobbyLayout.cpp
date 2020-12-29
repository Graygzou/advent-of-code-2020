// Day24-LobbyLayout.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

pair<float,float> SumPair(pair<float, float> pair1, pair<float, float> pair2)
{
    return pair<float, float>(pair1.first + pair2.first, pair1.second + pair2.second);
}

pair<float,float> DividePairByFactor(pair<float, float> pair1, int factor)
{
    return pair<float, float>(pair1.first / factor, pair1.second / factor);
}

pair<float, float> StudyEastOrWestChar(char nextChar)
{
    pair<float, float> position;
    switch (nextChar)
    {
        case 'e':
            position = pair<float, float>(-1, 0);
            break;

        case 'w':
            position = pair<float, float>(1, 0);
            break;

        default:
            position = pair<float, float>(0, 0);
            break;
    }

    return position;
}

pair<float, float> ProcessDirection(string line)
{
    pair<float, float> position = pair<float, float>(0,0);
    for (size_t i = 0; i < line.size(); i++)
    {
        switch (line[i])
        {
            case 'e':
            case 'w':
                position = SumPair(position, StudyEastOrWestChar(line[i]));
                break;

            case 's':
                position = SumPair(position, pair<float, float>(0, -1));
                i++;
                position = SumPair(position, DividePairByFactor(StudyEastOrWestChar(line[i]), 2));
                break;

            case 'n':
                position = SumPair(position, pair<float, float>(0, 1));
                i++;
                position = SumPair(position, DividePairByFactor(StudyEastOrWestChar(line[i]), 2));
                break;

            default:
                break;
        }
    }

    return position;
}

void Part1(string fileName)
{
    ifstream file;
    string line;

    map<pair<float, float>, bool> tilePositions;

    int maxValue = 0;
    file.open(fileName);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            pair<float, float> position = ProcessDirection(line);
            //cout << "position " << "(" << position.first << "," << position.second << ")" << endl;

            if (tilePositions.find(position) == tilePositions.end())
            {
                tilePositions[position] = false;
            }

            tilePositions[position] = !tilePositions[position];
        }
    }

    int result = 0;
    for (auto it = tilePositions.begin(); it != tilePositions.end(); ++it)
    {
        //cout << "(" << it->first.first << "," << it->first.second << ") ==> " << it->second << endl;
        result += it->second ? 1 : 0;
    }

    cout << "Result part 1 is " << result << endl;
}

void Tests()
{
    cout << "Test 1 = " << (ProcessDirection("eeseww") == ProcessDirection("se") ? "true" : "false") << endl;
    cout << "Test 2 = " << (ProcessDirection("se") == ProcessDirection("swe") ? "true" : "false") << endl;
}

int main()
{
    std::cout << "Lobby Layout" << endl;
    //Tests();
    Part1("input.txt");
}