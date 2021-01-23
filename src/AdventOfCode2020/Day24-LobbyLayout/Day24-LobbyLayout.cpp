// Day24-LobbyLayout.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef pair<float, float> Position;

#pragma region function signatures defs
void ProcessInput(string fileName);

Position ProcessDirection(string line);
int CountTotalBlackTiles(map<Position, bool> tilePositions);
int CountBlackNeighbor(Position position, map<Position, bool> tilePositions);

void FlipTiles(map<Position, bool>* tilePositions);
vector<Position> FindCandidates(map<Position, bool> tilePositions, vector<Position>* futureWhiteTile);
vector<Position> FindFinalCandidates(vector<Position> candidates, map<Position, bool> tilePositions);
void FlipFinalCandidatesToBlack(vector<Position> nextBlackTiles, map<Position, bool>* tilePositions);
void FlipBlackTileToWhite(vector<Position> nextwhiteTiles, map<Position, bool>* tilePositions);
#pragma endregion

#pragma region Consts
const int NEIGHBOTS_TOTAL_COUNT = 6;
const Position NEIGHBORS_RELATIVE_POS[]
{ 
        Position(-0.5,1),  Position(0.5,1), 

    Position(-1,0),             Position(1,0), 

        Position(-0.5,-1), Position(0.5,-1) 
};
#pragma endregion

int main(int argc, char** argv)
{
    std::cout << "Day 24 - Lobby Layout" << endl;
    //Tests();

    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }

    ifstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    map<Position, bool> tilePositions;
    string line;
    while (getline(file, line))
    {
        Position position = ProcessDirection(line);
        if (tilePositions.find(position) == tilePositions.end())
        {
            tilePositions[position] = false;
        }

        tilePositions[position] = !tilePositions[position];
    }

    cout << "Result part 1 is " << CountTotalBlackTiles(tilePositions) << endl;

    int nbDays = 100;
    for (size_t day = 0; day < nbDays; day++)
    {
        FlipTiles(&tilePositions);
        cout << "Day " << (day + 1) << ":" << CountTotalBlackTiles(tilePositions) << endl;
    }

    cout << "Result part 2 is " << CountTotalBlackTiles(tilePositions) << endl;

}


#pragma region Position ope
Position SumPair(Position pair1, Position pair2)
{
    return Position(pair1.first + pair2.first, pair1.second + pair2.second);
}

Position DividePairByFactor(Position pair1, int factor)
{
    return Position(pair1.first / factor, pair1.second / factor);
}

double Magnitude(Position pos1, Position pos2)
{
    return sqrt(pow(pos1.first - pos2.first, 2) + pow(pos1.second - pos2.second, 2));
}
#pragma endregion


#pragma region Parsing
Position StudyEastOrWestChar(char nextChar)
{
    Position position;
    switch (nextChar)
    {
        case 'e': position = Position(-1, 0); break;
        case 'w': position = Position(1, 0); break;
        default: position = Position(0, 0); break;
    }
    return position;
}

Position ProcessDirection(string line)
{
    Position position = Position(0,0);
    for (size_t i = 0; i < line.size(); i++)
    {
        switch (line[i])
        {
            case 'e':
            case 'w':
                position = SumPair(position, StudyEastOrWestChar(line[i]));
                break;

            case 's':
                position = SumPair(position, Position(0, -1));
                i++;
                position = SumPair(position, DividePairByFactor(StudyEastOrWestChar(line[i]), 2));
                break;

            case 'n':
                position = SumPair(position, Position(0, 1));
                i++;
                position = SumPair(position, DividePairByFactor(StudyEastOrWestChar(line[i]), 2));
                break;

            default:
                break;
        }
    }

    return position;
}
#pragma endregion Parsing

int CountTotalBlackTiles(map<Position, bool> tilePositions)
{
    int result = 0;
    for (auto it = tilePositions.begin(); it != tilePositions.end(); ++it)
    {
        result += it->second ? 1 : 0;
    }

    return result;
}

void Tests()
{
    cout << "Test 1 = " << (ProcessDirection("eeseww") == ProcessDirection("se") ? "true" : "false") << endl;
    cout << "Test 2 = " << (ProcessDirection("se") == ProcessDirection("swe") ? "true" : "false") << endl;
}

#pragma region Part 2 functions
void FlipTiles(map<Position, bool>* tilePositions)
{
    vector<Position> futureWhiteTiles;
    vector<Position> candidates = FindCandidates(*tilePositions, &futureWhiteTiles);
    vector<Position> finalCandidates = FindFinalCandidates(candidates, *tilePositions);

    FlipBlackTileToWhite(futureWhiteTiles, tilePositions);
    FlipFinalCandidatesToBlack(finalCandidates, tilePositions);
}

vector<Position> FindCandidates(map<Position, bool> tilePositions, vector<Position> *futureWhiteTile)
{
    vector<Position> candidates;
    
    for (auto it = tilePositions.begin(); it != tilePositions.end(); ++it)
    {
        if (tilePositions[it->first])
        {
            int nbAdjacentBlackTiles = 0;
            for (auto it2 = tilePositions.begin(); it2 != tilePositions.end(); ++it2)
            {
                if (it2->first != it->first && tilePositions[it2->first])
                {
                    bool nextToEachOther = Magnitude(it->first, it2->first) <= 1.5;
                    if (nextToEachOther)
                    {
                        nbAdjacentBlackTiles++;
                    }

                    // For now we will add all his neighbors. 
                    // IMPROVEMENTS: we could filtrate more if needed by only adding potential node thanks to every configurations.
                    if (nextToEachOther || Magnitude(it->first, it2->first) < 2.5)
                    {
                        for (size_t i = 0; i < NEIGHBOTS_TOTAL_COUNT; i++)
                        {
                            Position currentCandidate = SumPair(it->first, NEIGHBORS_RELATIVE_POS[i]);
                            // If the tile is not a candidate neither black yet
                            if (find(candidates.begin(), candidates.end(), currentCandidate) == candidates.end())
                            {
                                candidates.push_back(currentCandidate);
                            }
                        }
                    }
                }
            }

            if (nbAdjacentBlackTiles == 0 || nbAdjacentBlackTiles > 2)
            {
                futureWhiteTile->push_back(it->first);
            }
        }
    }

    return candidates;
}

vector<Position> FindFinalCandidates(vector<Position> candidates, map<Position, bool> tilePositions)
{
    vector<Position> finalCandidates;

    for (auto it = candidates.begin(); it != candidates.end(); ++it)
    {
        // Make sure we only study white tiles
        if (tilePositions.find(*it) == tilePositions.end() || !tilePositions[*it])
        {
            int nbBlackNeighnors = CountBlackNeighbor(*it, tilePositions);
            if (nbBlackNeighnors == 2)
            {
                finalCandidates.push_back(*it);
            }
        }
    }

    return finalCandidates;
}

int CountBlackNeighbor(Position position, map<Position, bool> tilePositions)
{
    int nbBlackNeighbor = 0;
    for (size_t i = 0; i < NEIGHBOTS_TOTAL_COUNT; i++)
    {
        if (tilePositions[SumPair(position, NEIGHBORS_RELATIVE_POS[i])])
        {
            nbBlackNeighbor++;
        }
    }

    return nbBlackNeighbor;
}

void FlipFinalCandidatesToBlack(vector<Position> nextBlackTiles, map<Position, bool>* tilePositions)
{
    for (auto it = nextBlackTiles.begin(); it != nextBlackTiles.end(); ++it)
    {
        (*tilePositions)[*it] = true;
    }
}

void FlipBlackTileToWhite(vector<Position> nextwhiteTiles, map<Position, bool>* tilePositions)
{
    for (auto it = nextwhiteTiles.begin(); it != nextwhiteTiles.end(); ++it)
    {
        tilePositions->erase(*it);
    }
}
#pragma endregion Part 2 functions