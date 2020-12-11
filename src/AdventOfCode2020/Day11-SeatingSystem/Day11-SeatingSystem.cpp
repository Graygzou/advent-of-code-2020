// Day11-SeatingSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

bool Part1NeighborhoodComputation(vector<vector<char>> previousLayout, int i, int j, int xBound, int yBound, int *neighborsOccupiedTotal)
{
    bool allNeighborsEmpty = true;

    int minXBounds = max(0, i - 1);
    int maxXBounds = min(i + 1, xBound);

    int minYBounds = max(0, j - 1);
    int maxYBounds = min(j + 1, yBound);
    //cout << "study neighbors" << endl;
    for (int neighborJ = minYBounds; neighborJ <= maxYBounds; neighborJ++)
    {
        for (int neighborI = minXBounds; neighborI <= maxXBounds; neighborI++)
        {
            if (neighborJ != j || neighborI != i)
            {
                //cout << "(" << neighborI << "," << neighborJ << ")" << endl;
                if (previousLayout[neighborJ][neighborI] == '#')
                {
                    //cout << "neigbor found ! " << seatLayout[neighborJ][neighborI];
                    (*neighborsOccupiedTotal)++;
                }

                allNeighborsEmpty = allNeighborsEmpty && previousLayout[neighborJ][neighborI] != '#';
            }
        }
    }

    return allNeighborsEmpty;
}

bool Part2NeighborhoodComputation(vector<vector<char>> previousLayout, int i, int j, int xBound, int yBound, int* neighborsOccupiedTotal)
{
    bool allNeighborsEmpty = true;

    int minXBounds = max(0, i - 1);
    int maxXBounds = min(i + 1, xBound);

    int minYBounds = max(0, j - 1);
    int maxYBounds = min(j + 1, yBound);
    //cout << "study neighbors" << endl;
    for (int neighborJ = minYBounds; neighborJ <= maxYBounds; neighborJ++)
    {
        for (int neighborI = minXBounds; neighborI <= maxXBounds; neighborI++)
        {
            if (neighborJ != j || neighborI != i)
            {
                //cout << "Here" << endl;

                bool found = false;
                int currentI = neighborI;
                int currentJ = neighborJ;
                while (!found &&
                    currentI >= 0 && currentI <= xBound &&
                    currentJ >= 0 && currentJ <= yBound)
                {
                    // Find it
                    found = previousLayout[currentJ][currentI] != '.';

                    if (!found)
                    {
                        // Update
                        currentI += (neighborI - i);
                        currentJ += (neighborJ - j);
                    }
                }

                if (found)
                {
                    //cout << "(" << currentI << "," << currentJ << ")" << endl;
                    if (previousLayout[currentJ][currentI] == '#')
                    {
                        //cout << "neigbor found ! " << seatLayout[neighborJ][neighborI];
                        (*neighborsOccupiedTotal)++;
                    }

                    allNeighborsEmpty = allNeighborsEmpty && previousLayout[currentJ][currentI] != '#';
                }
            }
        }
    }

    return allNeighborsEmpty;
}



int Part1(vector<vector<char>> seatLayout, int nbSeatOccupiedBeforeEmpty)
{
    int nbOccupiedSeats = 0;

    int nbLoop = 0;
    bool hasChanged = false;
    do
    {
        hasChanged = false;
        vector<vector<char>> previousLayout = seatLayout;

        for (int j = 0; j < previousLayout.size(); j++)
        {
            for (int i = 0; i < previousLayout[0].size(); i++)
            {
                if (previousLayout[j][i] != '.')
                {

                    //cout << "(" << i << "," << j << ") => " << previousLayout[j][i] << endl;

                    // tag the seat has occupied
                    int neighborsOccupiedTotal = 0;
                    // Leave the seat empty
                    bool hasOccupiedNeighbors = false;

                    // Find neighbors
                    //bool allNeighborsEmpty = Part1NeighborhoodComputation(previousLayout, i, j, (int)previousLayout[0].size() - 1, (int)previousLayout.size() - 1, &neighborsOccupiedTotal);
                    bool allNeighborsEmpty = Part2NeighborhoodComputation(previousLayout, i, j, (int)seatLayout[0].size() - 1, (int)seatLayout.size() - 1, &neighborsOccupiedTotal);

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
        nbLoop++;

        //// DEBUG: Display
        //cout << "Display current" << endl;
        //for (size_t i = 0; i < seatLayout.size(); i++)
        //{
        //    for (size_t j = 0; j < seatLayout[i].size(); j++)
        //    {
        //        if (seatLayout[i][j] == '#')
        //        {
        //            nbOccupiedSeats++;
        //        }
        //        cout << seatLayout[i][j];
        //    }

        //    cout << endl;
        //}


    } while (hasChanged && nbLoop < 500);
    cout << nbLoop << endl;


    // DEBUG: Display
    cout << "Display current" << endl;
    for (size_t i = 0; i < seatLayout.size(); i++)
    {
        for (size_t j = 0; j < seatLayout[i].size(); j++)
        {
            if (seatLayout[i][j] == '#')
            {
                nbOccupiedSeats++;
            }
            cout << seatLayout[i][j];
        }

        cout << endl;
    }

    return nbOccupiedSeats;
}


int main()
{
    vector<vector<char>> seatLayout = vector<vector<char>>();

    string line;
    ifstream  myfile;

    int nbSpotLeft = 0;

    myfile.open("input.txt");
    if (myfile.is_open())
    {
        int lineIndex = 0;
        while (getline(myfile, line))
        {
            //cout << line.c_str() << endl;
            seatLayout.push_back(vector<char>());
            for (size_t i = 0; i < line.size(); i++)
            {
                seatLayout[lineIndex].push_back(line[i]);
            }

            lineIndex++;
        }
    }
    myfile.close();

    // DEBUG: Display
    cout << "Display" << endl;
    for (size_t j = 0; j < seatLayout.size(); j++)
    {
        for (size_t i = 0; i < seatLayout[j].size(); i++)
        {
            cout << seatLayout[j][i];
        }

        cout << endl;
    }
    cout << "end" << endl;
    // END DEBUG

    cout << "TEST 1 " << seatLayout.size() << endl;
    cout << "TEST 2 " << seatLayout[0].size() << endl;

    // Part1(seatLayout, 4)
    int nbOccupiedSeats = Part1(seatLayout, 5);

    
    cout << "Result is : " << nbOccupiedSeats << endl;
}