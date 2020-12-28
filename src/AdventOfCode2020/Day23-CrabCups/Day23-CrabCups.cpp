// Day23-CrabCups.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Part1(string fileName, bool part2)
{
    ifstream file;
    string line;

    vector<int> cups;
    
    int maxValue = 0;
    file.open(fileName);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            for (size_t i = 0; i < line.size(); i++)
            {
                string s(1, line[i]);
                int currentValue = atoi(s.c_str());
                cups.push_back(currentValue);

                if (maxValue == -1 || maxValue < currentValue)
                {
                    maxValue = currentValue;
                }
            }
        }
    }

    if (part2)
    {
        int nbCups = 1000000;
        maxValue = nbCups - 1;
        for (size_t i = cups.size(); i < nbCups; i++)
        {
            cups.push_back(i);
        }
    }

    cout << "Size " << cups.size() << endl;
    
    int pickUpNumber = 3;

    vector<int> pickUps;
    int currentIndex = 0;
    int nbTurns = 10000000;
    for (size_t turn = 0; turn < nbTurns; turn++)
    {
        if ((turn + 1) % 1000 == 0)
            cout << "-- Move " << (turn + 1) << " --" << endl;

        //cout << "cups: ";
        //for (size_t i = 0; i < cups.size(); i++)
        //{
        //    cout << cups[i] << ", ";
        //}
        //cout << endl;

        int value = cups[currentIndex] - 1;
        int lastIndex = min((int)cups.size(), currentIndex + 1 + pickUpNumber);

        pickUps.clear();
        int index = -1;
        for (size_t i = 0; i < pickUpNumber; i++)
        {
            index = (currentIndex + 1) % cups.size();
            if (index < currentIndex)
            {
                currentIndex--;
            }

            pickUps.push_back(cups[index]);
            cups.erase(cups.begin() + index);
        }

        //cout << "cups: ";
        //for (size_t i = 0; i < pickUps.size(); i++)
        //{
        //    cout << pickUps[i] << ", ";
        //}
        //cout << endl;

        int destination = value;
        while (destination == 0 || find(pickUps.begin(), pickUps.end(), destination) != pickUps.end())
        {
            destination = destination == 0 ? maxValue : destination - 1;
        }

        auto it = find(cups.begin(), cups.end(), destination);
        int destinationIndex = std::distance(cups.begin(), it);
        for(auto it = pickUps.rbegin(); it != pickUps.rend(); ++it)
        {
            cups.insert(cups.begin() + destinationIndex + 1, *it);
        }

        currentIndex = ((destinationIndex < currentIndex ? (currentIndex + pickUpNumber) % maxValue : currentIndex) + 1) % maxValue;
    }

    if (!part2)
    {
        cout << "-- final --" << endl;
        cout << "cups: ";
        for (size_t i = 0; i < cups.size(); i++)
        {
            cout << cups[i] << ", ";
        }
        cout << endl;
    }
    else
    {
        auto it = find(cups.begin(), cups.end(), 1);
        int index = std::distance(cups.begin(), it);

        cout << "Number 1 " << cups[index + 1] << endl;
        cout << "Number 2 " << cups[index + 2] << endl;

        unsigned long long result = cups[index + 1] * cups[index + 2];
        cout << "Result part 2 is " << result << endl;
    }
}

int main()
{
    std::cout << "Crab Cups" << endl;
    Part1("example.txt", true);
}
