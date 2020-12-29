// Day24-LobbyLayout.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef pair<float, float> Position;

#pragma region function defs
void ProcessInput(string fileName);

void FlipTiles(map<Position, bool>* tilePositions);
vector<Position> FindCandidates(map<Position, bool> tilePositions);
vector<Position> FindFinalCandidates(vector<Position> candidates, map<Position, bool> tilePositions);
void FlipFinalCandidates(vector<Position> nextBlackTiles, map<Position, bool>* tilePositions);
bool CountBlackNeighbor(Position position, map<Position, bool> tilePositions);
#pragma endregion

#pragma region Consts
const int NEIGHBOTS_TOTAL_COUNT = 6;
const Position NEIGHBORS_RELATIVE_POS[]
{ 
        Position(-0.5,1),  Position(0.5,1), 

    Position(0,-1),             Position(0,1), 

        Position(-0.5,-1), Position(0.5,-1) 
};
#pragma endregion

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
        //cout << "(" << it->first.first << "," << it->first.second << ") ==> " << it->second << endl;
        result += it->second ? 1 : 0;
    }

    return result;
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
    ProcessInput("example.txt");
}

void ProcessInput(string fileName)
{
    ifstream file;
    string line;

    map<Position, bool> tilePositions;

    int maxValue = 0;
    file.open(fileName);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            Position position = ProcessDirection(line);
            //cout << "position " << "(" << position.first << "," << position.second << ")" << endl;

            if (tilePositions.find(position) == tilePositions.end())
            {
                tilePositions[position] = false;
            }

            tilePositions[position] = !tilePositions[position];
        }
    }

    cout << "Result part 1 is " << CountTotalBlackTiles(tilePositions) << endl;

    int nbDays = 1;
    for (size_t day = 0; day < nbDays; day++)
    {
        FlipTiles(&tilePositions);
        cout << "Day " << day << ":" << CountTotalBlackTiles(tilePositions) << endl;
    }

    cout << "Result part 2 is " << CountTotalBlackTiles(tilePositions) << endl;
}

#pragma region Part 2 functions
void FlipTiles(map<Position, bool>* tilePositions)
{
    vector<Position> candidates = FindCandidates(*tilePositions);
    vector<Position> finalCandidates = FindFinalCandidates(candidates, *tilePositions);
    FlipFinalCandidates(finalCandidates, tilePositions);
}

vector<Position> FindCandidates(map<Position, bool> tilePositions)
{
    vector<Position> candidates;
    
    for (auto it = tilePositions.begin(); it != tilePositions.end(); ++it)
    {
        for (auto it2 = tilePositions.begin(); it2 != tilePositions.end() && it2 != it; ++it2)
        {
            // For now we will add all his neighbors. 
            // IMPROVEMENTS: we could filtrate more if needed by only adding potential node thanks to every configurations.
            
            bool nextToEachOther = Magnitude(it->first, it2->first) < 2;
            // sqrt(4) == 2
            bool appartButAligned = Magnitude(it->first, it2->first) == 2;
            // sqrt(3) == 1.80277564
            bool appartAndFollowHexaLine = Magnitude(it->first, it2->first) == 1.80277564;
            // sqrt(5) == 2,23606798
            bool appartAndNotFollowHexaLine = Magnitude(it->first, it2->first) == 2.23606798;
            if (nextToEachOther || appartButAligned || appartAndFollowHexaLine || appartAndNotFollowHexaLine)
            {
                for (size_t i = 0; i < NEIGHBOTS_TOTAL_COUNT; i++)
                {
                    Position currentCandidate = SumPair(it->first, NEIGHBORS_RELATIVE_POS[i]);
                    if (find(candidates.begin(), candidates.end(), currentCandidate) == candidates.end())
                    {
                        candidates.push_back(currentCandidate);
                    }
                }
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
        // If the tile is not black yet
        if (!tilePositions[*it])
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

bool CountBlackNeighbor(Position position, map<Position, bool> tilePositions)
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

void FlipFinalCandidates(vector<Position> nextBlackTiles, map<Position, bool>* tilePositions)
{
    for (auto it = nextBlackTiles.begin(); it != nextBlackTiles.end(); ++it)
    {
        (*tilePositions)[*it] = true;
    }
}
#pragma endregion Part 2 functions