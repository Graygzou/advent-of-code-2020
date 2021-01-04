// Day23-CrabCups.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

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

    cout << "Size " << cups.size() << endl;
    //cout << "cups: ";
    //for (size_t i = 0; i < cups.size(); i++)
    //{
    //    cout << cups[i] << ", ";
    //}

    // Construct an map to access index in O(1)
    map<int, int> numberIndexes;
    for (size_t i = 0; i < cups.size(); i++)
    {
        numberIndexes.insert(make_pair(cups[i], i));
    }

    int pickUpNumber = 3;

    vector<int> pickUps;
    int currentDestinationIndex = 0;

    int destination = -1;
    int nextDestination = cups[currentDestinationIndex] - 1;

    int nbTurns = 100;
    for (size_t turn = 0; turn < nbTurns; turn++)
    {
        destination = nextDestination;

        //cout << "cups: ";
        //for (size_t i = 0; i < cups.size(); i++)
        //{
        //    cout << cups[i] << ", ";
        //}
        //cout << endl;

        pickUps.clear();
        int index = -1;
        for (size_t i = 0; i < pickUpNumber; i++)
        {
            index = (currentDestinationIndex + 1) % cups.size();
            pickUps.push_back(cups[index]);
            cups.erase(cups.begin() + index);
        }

        //cout << "cups: ";
        //for (size_t i = 0; i < pickUps.size(); i++)
        //{
        //    cout << pickUps[i] << ", ";
        //}
        //cout << endl;

        int destinationNumber = destination;
        while (destinationNumber == 0 || find(pickUps.begin(), pickUps.end(), destinationNumber) != pickUps.end())
        {
            destinationNumber = destinationNumber == 0 ? maxValue : destinationNumber - 1;
        }

        //auto it = find(cups.begin(), cups.end(), destination);
        //int destinationIndex = std::distance(cups.begin(), it);

        int destinationIndex = numberIndexes[destinationNumber];
        nextDestination = cups[(destinationIndex + 1) % maxValue];

        // Update the maps
        for (size_t i = currentDestinationIndex + pickUpNumber + 1; i < destinationIndex + 1; i++)
        {
            int indexWithoutPickUp = i % pickUpNumber;
            numberIndexes[cups[indexWithoutPickUp]] = currentDestinationIndex + indexWithoutPickUp;
        }

        int i = pickUpNumber - 1;
        for (auto it = pickUps.rbegin(); it != pickUps.rend(); ++it)
        {
            cups.insert(cups.begin() + destinationIndex + 1, *it);
            numberIndexes[*it] = destination + i;
            i--;
        }

        currentDestinationIndex = ((destinationIndex < currentDestinationIndex ? (currentDestinationIndex + pickUpNumber) % maxValue : currentDestinationIndex) + 1) % maxValue;
    }

    cout << "-- final --" << endl;
    cout << "cups: ";
    for (size_t i = 0; i < cups.size(); i++)
    {
        cout << cups[i] << ", ";
    }
    cout << endl;
}

void Part2(string fileName, bool debug)
{
    ifstream file;
    string line;

    map<int, int> cups;

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
                cups.insert(make_pair(i, currentValue));

                if (maxValue == -1 || maxValue < currentValue)
                {
                    maxValue = currentValue;
                }
            }
        }
    }

    if (!debug)
    {
        int nbCups = 1000000;
        maxValue = nbCups;
        for (size_t i = cups.size() + 1; i <= nbCups; i++)
        {
            cups.insert(make_pair(i - 1, i));
        }
    }

    cout << "Size " << cups.size() << endl;
    //cout << "cups: ";
    //for (size_t i = 0; i < cups.size(); i++)
    //{
    //    cout << cups[i] << ", ";
    //}

    // Construct an map to access index in O(1)
    // Will always start at index 1.
    map<int, int> indexesOfCups;
    for (size_t i = 0; i < cups.size(); i++)
    {
        indexesOfCups.insert(make_pair(cups[i], i));
    }

    int pickUpNumber = 3;

    vector<int> pickUps;
    int selectedCupIndex = 0;

    int destination = -1;
    //int nextDestination = cups[selectedCupIndex] - 1;

    int nbTurns = 100;
    for (size_t turn = 0; turn < nbTurns; turn++)
    {
        destination = cups[selectedCupIndex] - 1;

        //cout << "-- Move " << (turn + 1) << " --" << endl;
        //cout << "index -> cup: ";
        //int yy = 0;
        //for (auto it = cups.begin(); it != cups.end(); ++it)
        //{
        //    if (yy == selectedCupIndex)
        //    {
        //        cout << "(";
        //    }
        //    cout << it->second;
        //    if (yy == selectedCupIndex)
        //    {
        //        cout << ")";
        //    }
        //    cout << ", ";
        //    yy++;
        //}
        //cout << endl;

        //cout << "number -> index: ";
        //for (auto it = indexesOfCups.begin(); it != indexesOfCups.end(); ++it)
        //    cout << it->first << " => " << it->second << ", ";
        //cout << endl;

        if ((turn + 1) % 2000 == 0)
            cout << "-- Move " << (turn + 1) << " --" << endl;

        pickUps.clear();
        int index = -1;
        for (size_t i = 0; i < pickUpNumber; i++)
        {
            index = (selectedCupIndex + i + 1) % cups.size();
            pickUps.push_back(cups[index]);
            //cups.erase(cups.begin() + index);
        }

        //cout << "cups: ";
        //for (size_t i = 0; i < pickUps.size(); i++)
        //    cout << pickUps[i] << ", ";
        //cout << endl;

        int destinationNumber = destination;
        while (destinationNumber == 0 || find(pickUps.begin(), pickUps.end(), destinationNumber) != pickUps.end())
        {
            destinationNumber = destinationNumber == 0 ? maxValue : destinationNumber - 1;
        }

        int destinationIndex = indexesOfCups[destinationNumber];
        //nextDestination = selectedCupIndex + 1;

        //cout << "Current index " << selectedCupIndex << endl;
        //cout << "destination number is " << destinationNumber << endl;
        //cout << "Current destination index is " << destinationIndex << endl;

        //cout << "Test " << (selectedCupIndex < destinationIndex) << endl;

        if (selectedCupIndex < destinationIndex)
        {
            // Update the maps by moving all cups next to the current selected cups
            int offset = 1;
            for (size_t i = selectedCupIndex + pickUpNumber + 1; i < destinationIndex + 1; i++)
            {
                int index = (selectedCupIndex + offset) % maxValue;;

                // Update both maps
                //int temp = indexesOfCups[cups[i]];
                if (destinationNumber == cups[i]
                    /*&& (destinationIndex + 1) - pickUpNumber < 0*/)
                {
                    destinationIndex = index + 1;
                }

                indexesOfCups[cups[i]] = index;
                cups[index] = cups[i];
                offset++;
            }

            int i = 0;
            for (auto it = pickUps.begin(); it != pickUps.end(); ++it)
            {
                int index = (destinationIndex + i) % maxValue;/* - pickUpNumber + i*/;

                // Update both maps
                //int temp = indexesOfCups[*it];
                indexesOfCups[*it] = index;
                cups[index] = *it;
                i++;
            }
        }
        else
        {
            int offset = selectedCupIndex - destinationIndex;
            for (size_t i = selectedCupIndex; i >= destinationIndex + 1; i--)
            {
                int index = (destinationIndex + pickUpNumber + offset) % maxValue;
                indexesOfCups[cups[i]] = index;
                cups[index] = cups[i];
                offset--;
            }

            int i = 1;
            for (auto it = pickUps.begin(); it != pickUps.end(); ++it)
            {
                int index = (destinationIndex + i) % maxValue;/* - pickUpNumber + i*/;

                // Update both maps
                indexesOfCups[*it] = index;
                cups[index] = *it;
                i++;
            }

            selectedCupIndex += pickUpNumber;
        }

        selectedCupIndex++;
        selectedCupIndex %= maxValue;
    }

    cout << "-- final --" << endl;
    cout << "cups: ";
    for (size_t i = 0; i < cups.size(); i++)
    {
        cout << cups[i] << ", ";
        selectedCupIndex++;
        selectedCupIndex %= maxValue;
    }
    cout << endl;

    auto it = cups.find(1);
    //auto it = find(cups.begin(), cups.end(), 1);
    int index = std::distance(cups.begin(), it);

    cout << "Number indexOf1 + 1 " << cups[index + 1] << endl;
    cout << "Number indexOf1 - 1 " << cups[index - 1] << endl;
    cout << "Number indexOf1 + 2 " << cups[index + 2] << endl;
    cout << "Number indexOf1 - 2 " << cups[index - 2] << endl;

    unsigned long long result = cups[index + 1] * cups[index + 2];
    cout << "Result part 2 is " << result << endl;
}

int main()
{
    std::cout << "Crab Cups" << endl;
    //Part1("example.txt");
    Part2("example.txt", false);
}