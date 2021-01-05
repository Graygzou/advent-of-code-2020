// Day23-CrabCups.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Cup 
{
private:
    Cup* nextNeigbors;
    int value = 0;

public:
    Cup(int value) { this->value = value; }

    void SetNext(Cup* next) { nextNeigbors = next; }
    int GetValue() { return value; }
    Cup* GetNext() { return nextNeigbors; }
};

void DisplayCups(Cup* currentCup)
{
    Cup* cup = currentCup;
    do
    {
        cout << cup->GetValue() << ", ";
        cup = cup->GetNext();
    } while (cup != currentCup);
    cout << endl;
}

void PlayGame(string fileName, bool useExtraCups, int nbTurns)
{
    ifstream file;
    
    // vakue => index
    map<int, Cup*> cups;

    Cup* firstCup = nullptr;
    Cup* previousCup = nullptr;

    // Add starting cups
    int maxValue = 0;
    file.open(fileName);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            maxValue = line.size();
            for (size_t i = 0; i < line.size(); i++)
            {
                string s(1, line[i]);
                int currentValue = atoi(s.c_str());
                Cup* currentCup = new Cup(currentValue);

                if (previousCup != nullptr)
                {
                    previousCup->SetNext(currentCup);
                }

                if (i == 0)
                {
                    firstCup = currentCup;
                }
                if (!useExtraCups && i == line.size() - 1)
                {
                    currentCup->SetNext(firstCup);
                }
                
                cups.insert(make_pair(currentValue, currentCup));
                previousCup = currentCup;
            }
        }
    }

    // Add missing cups
    if (useExtraCups)
    {
        int nbCups = 1000000;
        maxValue = nbCups;
        for (size_t i = cups.size() + 1; i <= nbCups; i++)
        {
            Cup* currentCup = new Cup(i);
            if (previousCup != nullptr)
            {
                previousCup->SetNext(currentCup);
            }

            if (i == nbCups)
            {
                currentCup->SetNext(firstCup);
            }

            cups.insert(make_pair(i, currentCup));
            previousCup = currentCup;
        }
    }

    // Run the algorithm
    int pickUpNumber = 3;
    Cup* currentCup = firstCup;

    for (size_t turn = 0; turn < nbTurns; turn++)
    {
        Cup* nextCup = currentCup->GetNext();
        Cup* nextCup2 = currentCup->GetNext()->GetNext();
        Cup* nextCup3 = currentCup->GetNext()->GetNext()->GetNext();

        // Find the right cup number (not present in pick ups cup)
        int destinationNumber = currentCup->GetValue() - 1;
        while (destinationNumber == 0 || 
            destinationNumber == nextCup->GetValue() ||
            destinationNumber == nextCup2->GetValue() ||
            destinationNumber == nextCup3->GetValue())
        {
            destinationNumber = destinationNumber == 0 ? maxValue : destinationNumber - 1;
        }

        Cup* destinationCup = cups[destinationNumber];
        Cup* nextIterationCup = nextCup3->GetNext();

        // Insert the pick at the right place.
        Cup* temp = destinationCup->GetNext();
        destinationCup->SetNext(nextCup);
        nextCup3->SetNext(temp);

        // Update the currentNode for next iteration
        currentCup->SetNext(nextIterationCup);

        currentCup = currentCup->GetNext();
    }

    Cup* theOneCup = cups[1];

    if (!useExtraCups)
    {
        cout << "Result part 1 is "<< endl;
        DisplayCups(currentCup);
    }
    else
    {
        cout << "Number + 1 " << theOneCup->GetNext()->GetValue() << endl;
        cout << "Number + 2 " << theOneCup->GetNext()->GetNext()->GetValue() << endl;

        __int64 result = static_cast<__int64>(theOneCup->GetNext()->GetValue()) * static_cast<__int64>(theOneCup->GetNext()->GetNext()->GetValue());
        cout << "Result part 2 is " << result << endl;
    }
}

int main()
{
    std::cout << "Crab Cups" << endl;
    PlayGame("input.txt", false, 100);
    PlayGame("input.txt", true, 10000000);
}