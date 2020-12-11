// Day11-SeatingSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

void FirstTry(int nbSpotLeft, vector<vector<char>> seatLayout)
{
    int nbOccupiedSeats = 0;
    int nbLoop = 0;
    while (nbSpotLeft > 0 && nbLoop < 25)
    {
        nbSpotLeft = 0;

        bool exploreLine = false;
        int i = 0;
        int j = 0;

        int startJ = j;
        int startI = i;

        while (j < seatLayout.size() && i < seatLayout[0].size())
        {
            //cout << seatLayout[j][i];

            if (j < seatLayout.size() && i < seatLayout[0].size() && seatLayout[j][i] != '.' && seatLayout[j][i] != 'V')
            {
                //cout << "(" << i << "," << j << ")";

                // tag the seat has occupied
                int neighborsCount = 0;
                // Leave the seat empty
                bool hasOccupiedNeighbors = false;
                bool allNeighborsEmpty = true;

                // Find neighbors
                int minXBounds = max(0, j - 1);
                int maxXBounds = min(j + 1, (int)seatLayout.size() - 1);

                int minYBounds = max(0, i - 1);
                int maxYBounds = min(i + 1, (int)seatLayout[0].size() - 1);
                for (size_t neighborJ = minXBounds; neighborJ <= maxXBounds; neighborJ++)
                {
                    for (size_t neighborI = minYBounds; neighborI <= maxYBounds; neighborI++)
                    {
                        if (neighborJ != j || neighborI != i)
                        {
                            //cout << " loooooop >> ";
                            if (seatLayout[neighborJ][neighborI] != '.')
                            {
                                //cout << "neigbor found ! " << seatLayout[neighborJ][neighborI];
                                neighborsCount++;
                            }

                            hasOccupiedNeighbors |= seatLayout[neighborJ][neighborI] == 'V';
                            allNeighborsEmpty &= seatLayout[neighborJ][neighborI] != 'V' && seatLayout[neighborJ][neighborI] != '#';
                        }
                    }
                }

                if (j < seatLayout[0].size() && i < seatLayout.size())
                {
                    //cout << " Compute ... Neighbor count = " << neighborsCount;
                    if (neighborsCount < 4)
                    {
                        //cout << " SCORE ! ";
                        nbOccupiedSeats++;
                        seatLayout[j][i] = 'V';
                    }
                    else if (hasOccupiedNeighbors)
                    {
                        seatLayout[j][i] = 'L';
                    }
                    else
                    {
                        // Apply regular rules
                        nbSpotLeft++;
                        if (seatLayout[j][i] == '?' && allNeighborsEmpty)
                        {
                            seatLayout[j][i] = '#';
                        }
                        else if (seatLayout[j][i] == '#' && neighborsCount >= 4)
                        {
                            seatLayout[j][i] = '?';
                        }
                    }
                }
            }

            if (exploreLine)
            {
                i++;
                if (i >= seatLayout[0].size())
                {
                    exploreLine = false;
                    startJ++;
                    i = startI;
                    j = startJ;

                    //cout << endl;
                }
            }
            else
            {
                j++;
                if (j >= seatLayout.size())
                {
                    startI++;
                    i = startI;
                    j = startJ;

                    //cout << endl;
                }
            }

            /* cout << "starting I " << startI << " starting J " << startJ << endl;
             cout << " I " << i << " J " << j << endl;*/
             //cout << endl;
        }

        // DEBUG: Display
        cout << "Display current" << endl;
        for (size_t i = 0; i < seatLayout.size(); i++)
        {
            for (size_t j = 0; j < seatLayout[i].size(); j++)
            {
                cout << seatLayout[i][j];
            }

            cout << endl;
        }
        cout << "end" << endl;
        // END DEBUG

        nbLoop++;
    }


    // DEBUG: Display
    cout << "Display current" << endl;
    for (size_t i = 0; i < seatLayout.size(); i++)
    {
        for (size_t j = 0; j < seatLayout[i].size(); j++)
        {
            cout << seatLayout[i][j];
        }

        cout << endl;
    }
    cout << "end" << endl;
    // END DEBUG
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
                    bool allNeighborsEmpty = true;

                    // Find neighbors
                    int minXBounds = max(0, i - 1);
                    int maxXBounds = min(i + 1, (int)seatLayout[0].size() - 1);

                    int minYBounds = max(0, j - 1);
                    int maxYBounds = min(j + 1, (int)seatLayout.size() - 1);
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
                                    neighborsOccupiedTotal++;
                                }

                                allNeighborsEmpty = allNeighborsEmpty && previousLayout[neighborJ][neighborI] != '#';
                            }
                        }
                    }

                    // COmpute neighbors

                    if (previousLayout[j][i] == 'L' && allNeighborsEmpty)
                    {
                        hasChanged = true;
                        seatLayout[j][i] = '#';
                    }

                    if (previousLayout[j][i] == '#' && neighborsOccupiedTotal >= 4)
                    {
                        hasChanged = true;
                        seatLayout[j][i] = 'L';
                    }
                }
            }
        }
        nbLoop++;

        

    } while (hasChanged && nbLoop < 100000);
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
            //cout << seatLayout[i][j];
        }
    }
 
    
    cout << "Result is : " << nbOccupiedSeats << endl;
}