// Day11-SeatingSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

bool HasNonEmptyNeighbor(
    vector<vector<char>> previousLayout, 
    int xDirection, 
    int yDirection,
    int *neighborI, 
    int *neighborJ, 
    int minBoundsX, 
    int maxBoundsX, 
    int minBoundsY, 
    int maxBoundsY)
{
    bool found = false;

    int currentI = *neighborI;
    int currentJ = *neighborJ;

    while (!found &&
        currentI >= minBoundsX && currentI <= maxBoundsX &&
        currentJ >= minBoundsY && currentJ <= maxBoundsY)
    {
        // Find it
        found = previousLayout[currentJ][currentI] != '.';

        if (!found)
        {
            // Update for part 1 basically
            currentI += xDirection;
            currentJ += yDirection;
        }
    }

    *neighborI = currentI;
    *neighborJ = currentJ;

    return found;
}

bool ComputeNeighborhood(vector<vector<char>> previousLayout, int i, int j, int xBound, int yBound, int* neighborsOccupiedTotal, int sightLength = -1)
{
    bool allNeighborsEmpty = true;

    int minXBounds = max(0, i - 1);
    int maxXBounds = min(i + 1, xBound);

    int minYBounds = max(0, j - 1);
    int maxYBounds = min(j + 1, yBound);

    // Determine the bound to study more or less further neighbors.
    int sightXMinBounds = 0;
    int sightXMaxBounds = xBound;
    int sightYMinBounds = 0;
    int sightYMaxBounds = yBound;
    if (sightLength > 0)
    {
        sightXMinBounds = i - sightLength;
        sightXMaxBounds = i + sightLength;
        sightYMinBounds = j - sightLength;
        sightYMaxBounds = j + sightLength;
    }

    for (int neighborJ = minYBounds; neighborJ <= maxYBounds; neighborJ++)
    {
        for (int neighborI = minXBounds; neighborI <= maxXBounds; neighborI++)
        {
            if (neighborJ != j || neighborI != i)
            {
                int* currentI = new int(neighborI);
                int* currentJ = new int(neighborJ);
                if (HasNonEmptyNeighbor(
                    previousLayout, 
                    (*currentI - i), 
                    (*currentJ - j), 
                    currentI, 
                    currentJ, 
                    sightXMinBounds, 
                    sightXMaxBounds, 
                    sightYMinBounds,
                    sightYMaxBounds))
                {
                    if (previousLayout[*currentJ][*currentI] == '#')
                    {
                        (*neighborsOccupiedTotal)++;
                    }

                    allNeighborsEmpty = allNeighborsEmpty && previousLayout[*currentJ][*currentI] != '#';
                }
            }
        }
    }

    return allNeighborsEmpty;
}

int ApplyRulesToSeats(vector<vector<char>> seatLayout, int nbSeatOccupiedBeforeEmpty)
{
    bool hasChanged = true;
    do
    {
        hasChanged = false;

        // Make a copy to swap all seat "at the same time".
        vector<vector<char>> previousLayout = seatLayout;
        for (int j = 0; j < previousLayout.size(); j++)
        {
            for (int i = 0; i < previousLayout[0].size(); i++)
            {
                if (previousLayout[j][i] != '.')
                {
                    // tag the seat has occupied
                    int neighborsOccupiedTotal = 0;

                    // Find neighbors
                    bool allNeighborsEmpty = false;
                    if (nbSeatOccupiedBeforeEmpty == 4)
                    {
                        allNeighborsEmpty = ComputeNeighborhood(previousLayout, i, j, (int)seatLayout[0].size() - 1, (int)seatLayout.size() - 1, &neighborsOccupiedTotal, 1);
                    }
                    else
                    {
                        allNeighborsEmpty = ComputeNeighborhood(previousLayout, i, j, (int)seatLayout[0].size() - 1, (int)seatLayout.size() - 1, &neighborsOccupiedTotal);
                    }

                    if (previousLayout[j][i] == 'L' && allNeighborsEmpty)
                    {
                        hasChanged = true;
                        seatLayout[j][i] = '#';
                    }

                    if (previousLayout[j][i] == '#' && neighborsOccupiedTotal >= nbSeatOccupiedBeforeEmpty)
                    {
                        hasChanged = true;
                        seatLayout[j][i] = 'L';
                    }
                }
            }
        }
    } while (hasChanged);

    int nbOccupiedSeats = 0;
    for (size_t i = 0; i < seatLayout.size(); i++)
    {
        for (size_t j = 0; j < seatLayout[i].size(); j++)
        {
            if (seatLayout[i][j] == '#')
            {
                nbOccupiedSeats++;
            }
        }
    }

    return nbOccupiedSeats;
}

void DisplaySeats(vector<vector<char>> seatLayout)
{
    for (size_t j = 0; j < seatLayout.size(); j++)
    {
        for (size_t i = 0; i < seatLayout[j].size(); i++)
        {
            cout << seatLayout[j][i];
        }
        cout << endl;
    }
}

vector<vector<char>> RetrieveInputs(string fileName)
{
    vector<vector<char>> seatLayout = vector<vector<char>>();

    ifstream  myfile;
    myfile.open(fileName);
    if (myfile.is_open())
    {
        string line;
        int lineIndex = 0;
        while (getline(myfile, line))
        {
            seatLayout.push_back(vector<char>());
            for (size_t i = 0; i < line.size(); i++)
            {
                seatLayout[lineIndex].push_back(line[i]);
            }

            lineIndex++;
        }
    }
    myfile.close();

    return seatLayout;
}

int main()
{
    cout << "Day 11 - Seating System" << endl;

    // Use of vector<char> instead of string because easier to iterate over neighbors in any directions.
    vector<vector<char>> seatLayout = RetrieveInputs("input.txt");
    DisplaySeats(seatLayout);

    int nbOccupiedSeatsPart1 = ApplyRulesToSeats(seatLayout, 4);
    cout << "Result for part 1 is : " << nbOccupiedSeatsPart1 << endl;

    int nbOccupiedSeatsPart2 = ApplyRulesToSeats(seatLayout, 5);
    cout << "Result for part 2 is : " << nbOccupiedSeatsPart2 << endl;
}