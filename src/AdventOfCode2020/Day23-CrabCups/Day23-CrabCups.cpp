// Day23-CrabCups.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Part1(string fileName)
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

    int nbTurns = 100;
    vector<int> previousPickUps;

    int currentIndex = 0;
    int pickUpNumber = 3;
    for (size_t turn = 0; turn < nbTurns; turn++)
    {
        int value = cups[currentIndex] - 1;
        int lastIndex = min((int)cups.size(), currentIndex + 1 + pickUpNumber);
        vector<int> pickUps = vector<int>(cups.begin() + currentIndex + 1, cups.begin() + lastIndex);
        // Add if any element left need to be added.
        if (lastIndex == cups.size())
        {
            for (int i = 0; i < (currentIndex + 1 + pickUpNumber) - cups.size(); i++)
            {
                pickUps.push_back(cups[i]);
            }
        }

        cout << "-- Move " << (turn + 1) << " --" << endl;
        cout << "cups: ";
        for (size_t i = 0; i < cups.size(); i++)
        {
            if (i == currentIndex)
            {
                cout << "(";
            }
            cout << cups[i];
            if (i == currentIndex)
            {
                cout << ")";
            }
            cout << ", ";
        }
        cout << endl << "pick up: ";
        for (auto it = pickUps.begin(); it != pickUps.end(); ++it)
        {
            cout << *it << ", ";
        }
        

        // remove extra elements at the beginning
        int removingIndexStart = max(0, (currentIndex + pickUpNumber) - (int)cups.size());
        cups.erase(cups.begin() + currentIndex + 1, cups.begin() + lastIndex);

        cups.erase(cups.begin(), cups.begin() + pickUpNumber - (lastIndex - (currentIndex + 1)));
        
        int destination = value;
        
        while (destination == 0 || 
            find(pickUps.begin(), pickUps.end(), destination) != pickUps.end())
        {
            if (destination == 0)
            {
                destination = maxValue;
            }
            else
            {
                destination--;
            }
        }

        auto it = find(cups.begin(), cups.end(), destination);
        int index = std::distance(cups.begin(), it);

        cout << endl << "destination: " << destination << endl;
        cout << endl << "index: " << index << endl;

        for (size_t i = 0; i < pickUps.size(); i++)
        {
            cout << pickUps[i] << endl;
        }

        if (index < currentIndex )
        {
            currentIndex = (currentIndex + pickUpNumber - (pickUpNumber - (lastIndex - (currentIndex + 1)))) % maxValue;
        }

        for(auto it = pickUps.rbegin(); it != pickUps.rend(); ++it)
        {
            cups.insert(cups.begin() + index + 1, *it);
        }

        previousPickUps = pickUps;
        currentIndex = (currentIndex + 1) % maxValue;
    }

    cout << "-- final --" << endl;
    cout << "cups: ";
    for (size_t i = 0; i < cups.size(); i++)
    {
        cout << cups[i] << ", ";
    }
    cout << endl;

}

int main()
{
    std::cout << "Crab Cups" << endl;
    Part1("input.txt");
}
