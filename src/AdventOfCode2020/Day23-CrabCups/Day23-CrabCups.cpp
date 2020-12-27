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

    //maxValue -= 1;

    int nbTurns = 10;
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
        

        if (lastIndex == cups.size())
        {
            cups.erase(cups.begin() + currentIndex + 1, cups.begin() + lastIndex);

            // remove extra elements at the beginning
            int removingIndexStart = (currentIndex + pickUpNumber - 1) - cups.size();

            cout << "LALALALA" << removingIndexStart << endl;
            cups.erase(cups.begin(), cups.begin() + removingIndexStart);
        }
        else
        {
            cups.erase(cups.begin() + currentIndex + 1, cups.begin() + lastIndex);
        }
        
        int destination = value;
        
        while (find(pickUps.begin(), pickUps.end(), destination) != pickUps.end())
        {
            destination--;
            if (destination == 0)
            {
                destination = maxValue;
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
            int nbElementToRemoveAtTheEnd = max(0, (int)cups.size() - (currentIndex + 1));
            cout << "nbElementToRemoveAtTheEnd " << nbElementToRemoveAtTheEnd << endl;
            currentIndex = (currentIndex + (pickUpNumber - nbElementToRemoveAtTheEnd)) % maxValue;
            cout << "ICI " << currentIndex << endl;
            //index = currentIndex;
        }

        //for (size_t i = 0; i < n.size(); i++)
        for(auto it = pickUps.rbegin(); it != pickUps.rend(); ++it)
        {
            cups.insert(cups.begin() + index + 1, *it);
        }

        previousPickUps = pickUps;
        currentIndex = (currentIndex + 1) % maxValue;
    }

    for (size_t i = 0; i < cups.size(); i++)
    {
        cout << cups[i] << endl;
    }

}

int main()
{
    std::cout << "Crab Cups" << endl;
    Part1("example.txt");
}
