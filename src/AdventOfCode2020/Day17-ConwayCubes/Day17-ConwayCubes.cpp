// Day17-ConwayCubes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Node 
{
    int positonX = -1;
    int positonY = -1;
    int positonZ = -1;
    int positonW = -1;

    Node(int x, int y, int z, int w)
    {
        positonX = x;
        positonY = y;
        positonZ = z;
        positonW = w;
    }

    Node(vector<int> positions)
    {
        positonX = positions.size() > 0 ? positions[0] : 0;
        positonY = positions.size() > 1 ? positions[1] : 0;
        positonZ = positions.size() > 2 ? positions[2] : 0;
        positonW = positions.size() > 3 ? positions[3] : 0;
    }

    int GetPosition(int index)
    {
        if (index == 0)
            return positonX;
        else if (index == 1)
            return positonY;
        else if (index == 2)
            return positonZ;
        else if (index == 3)
            return positonW;
        else
            throw new exception("Can't get position of index > 3");
    }

    float SquaredMagnitude(Node destination)
    {
        int vectorX = destination.positonX - positonX;
        int vectorY = destination.positonY - positonY;
        int vectorZ = destination.positonZ - positonZ;
        return vectorX * vectorX + vectorY * vectorY + vectorZ * vectorZ;
    }

    bool WeigthDifferByOne(Node destination)
    {
        return abs(positonW - destination.positonW) <= 1.0;
    }

    float Magnitude(Node destination)
    {
        return sqrt(SquaredMagnitude(destination));
    }

    bool Equals(Node node)
    {
        return Equals(node.positonX, node.positonY, node.positonZ, node.positonW);
    }

    bool Equals(int x, int y, int z, int w)
    {
        return positonX == x && positonY == y && positonZ == z && positonW == w;
    }

    void Display()
    {
        std::cout << " Position is (" << positonX << "," << positonY << "," << positonZ << "," << positonW << ")" << endl;
    }

    bool operator<(const Node& rhs) const noexcept
    {
        return this->positonX < rhs.positonX 
            || this->positonX == rhs.positonX && this->positonY < rhs.positonY
            || this->positonX == rhs.positonX && this->positonY == rhs.positonY && this->positonZ < rhs.positonZ
            || this->positonX == rhs.positonX && this->positonY == rhs.positonY && this->positonZ == rhs.positonZ && this->positonW < rhs.positonW;
    }

    bool operator==(const Node& rhs) const noexcept
    {
        return this->positonX == rhs.positonX 
            && this->positonY == rhs.positonY 
            && this->positonZ == rhs.positonZ
            && this->positonW == rhs.positonW;
    }
};

vector<Node> SimulateConwayCycles(string fileName, int dimensions, int nbCycles);
Node MoveToNextCandidate(Node currentCandidate, vector<pair<int, int>> boundsCoordinates, int nbDimensions);

int main()
{
    std::cout << "Day 17 - Conway Cubes" << endl;

    string fileName = "input.txt";
    int dimensions = 3;
    vector<Node> activeCubes = SimulateConwayCycles(fileName, dimensions, 6);
    cout << "Result for part 1 is " << activeCubes.size() << endl;

    activeCubes.clear();
    dimensions++;
    activeCubes = SimulateConwayCycles(fileName, dimensions, 6);
    cout << "Result for part 2 is " << activeCubes.size() << endl;
}

void DisplayGrid(vector<Node> activeCubes, vector<pair<int, int>> boundsCoordinates)
{
    vector<int> minBounds;
    int nbCandidates = 1;
    for (size_t i = 0; i < boundsCoordinates.size(); i++)
    {
        nbCandidates *= (boundsCoordinates[i].second - boundsCoordinates[i].first) + 1;
        minBounds.push_back(boundsCoordinates[i].first);
    }

    Node candidate = Node(minBounds);
    for (size_t i = 0; i < nbCandidates; i++)
    {
        bool found = false;
        for (int j = 0; !found && j < activeCubes.size(); j++)
        {
            if (activeCubes[j].Equals(candidate))
            {
                std::cout << "#";
                found = true;
            }
        }

        if (!found)
        {
            std::cout << ".";
        }

        int oldY = candidate.positonY;
        int oldZ = candidate.positonZ;
        candidate = MoveToNextCandidate(candidate, boundsCoordinates, boundsCoordinates.size());

        if (candidate.positonY != oldY
            || candidate.positonZ != oldZ)
        {
            cout << endl;
            if (candidate.positonZ != oldZ)
            {
                cout << endl;
                cout << "Z = " << candidate.positonZ << endl;
            }
        }
    }

    cout << endl;
    cout << "=====================" << endl;
}

void UpdateBounds(vector<Node> activeCubes, vector<pair<int, int>>* boundsCoordinates)
{
    for (size_t i = 0; i < activeCubes.size(); i++)
    {
        for (size_t j = 0; j < boundsCoordinates->size(); j++)
        {
            if (activeCubes[i].GetPosition(j) < (*boundsCoordinates)[j].first)
            {
                (*boundsCoordinates)[j].first = activeCubes[i].GetPosition(j);
            }
            else if (activeCubes[i].GetPosition(j) > (*boundsCoordinates)[j].second)
            {
                (*boundsCoordinates)[j].second = activeCubes[i].GetPosition(j);
            }
        }
    }

    // Since we want to consider neigbors, we substract or add one to each new bounds found.
    for (size_t i = 0; i < boundsCoordinates->size(); i++)
    {
        (*boundsCoordinates)[i].first--;
        (*boundsCoordinates)[i].second++;
    }
}


Node MoveToNextCandidate(Node currentCandidate, vector<pair<int, int>> boundsCoordinates, int nbDimensions)
{
    Node nextCandidate = currentCandidate;

    nextCandidate.positonX++;
    if (nbDimensions >= 2 && nextCandidate.positonX > boundsCoordinates[0].second)
    {
        nextCandidate.positonX = boundsCoordinates[0].first;
        nextCandidate.positonY++;

        if (nbDimensions >= 3 && nextCandidate.positonY > boundsCoordinates[1].second)
        {
            nextCandidate.positonY = boundsCoordinates[1].first;
            nextCandidate.positonZ++;

            if (nbDimensions >= 4 && nextCandidate.positonZ > boundsCoordinates[2].second)
            {
                nextCandidate.positonZ = boundsCoordinates[2].first;
                nextCandidate.positonW++;
            }
        }
    }

    return nextCandidate;
}

vector<Node> RunCycle(
    vector<Node> activeCubes, 
    vector<pair<int, int>> *boundsCoordinates, 
    int dimensions)
{
    vector<Node> tempActiveCubes = vector<Node>();

    for (auto it = activeCubes.begin(); it != activeCubes.end(); ++it)
    {
        int nbNeigbors = 0;
        for (auto it2 = activeCubes.begin(); it2 != activeCubes.end(); ++it2)
        {
            if (it2 != it)
            {
                float magnitude = it->Magnitude(*it2);
                if (magnitude < 1.75 && it->WeigthDifferByOne(*it2))
                {
                    nbNeigbors++;
                }
            }
        }

        // All nodes are active here
        if (nbNeigbors >= 2 && nbNeigbors <= 3)
        {
            tempActiveCubes.push_back(*it);
        }
    }

    
    vector<int> minBounds;
    int nbCandidates = 1;
    for (size_t i = 0; i < boundsCoordinates->size(); i++)
    {
        nbCandidates *= ((*boundsCoordinates)[i].second - (*boundsCoordinates)[i].first) + 1;
        minBounds.push_back((*boundsCoordinates)[i].first);
    }

    Node candidate = Node(minBounds);
    for (size_t i = 0; i < nbCandidates; i++)
    {
        auto it = find(activeCubes.begin(), activeCubes.end(), candidate);
        // Node not active yet.
        if (it == activeCubes.end())
        {
            int NeigborsCount = 0;
            for (size_t i = 0; i < activeCubes.size(); i++)
            {
                // sqrt(3) == 1,73205081
                // sqrt(3.8) == 1,94935887
                float magnitude = candidate.Magnitude(activeCubes[i]);
                if (magnitude < 1.75 && candidate.WeigthDifferByOne(activeCubes[i]))
                {
                    NeigborsCount++;
                }
            }

            if (NeigborsCount == 3)
            {
                tempActiveCubes.push_back(candidate);
            }
        }

        candidate = MoveToNextCandidate(candidate, *boundsCoordinates, boundsCoordinates->size());
    }

    UpdateBounds(tempActiveCubes, boundsCoordinates);

    return tempActiveCubes;
}

/// <summary>
/// Construct the list of nodes already actives since calculations are based on them.
/// </summary>
vector<Node> GetStartingActiveNodes(string fileName, vector<pair<int, int>> *boundsCoordinates)
{
    vector<Node> activeCubes;

    ifstream file;
    file.open(fileName);
    if (file.is_open())
    {
        int w = 0, z = 0, y = 0;
        for (size_t i = 0; i < boundsCoordinates->size(); i++)
        {
            (*boundsCoordinates)[i].first = -1;
        }

        string line;
        while (getline(file, line))
        {
            for (int x = 0; x < line.size(); x++)
            {
                if (line[x] == '#')
                {
                    Node node = Node(x, y, z, w);

                    // Find any neighbor active
                    for (int activeIndex = 0; activeIndex < activeCubes.size(); activeIndex++)
                    {
                        // Compute squared magnitude of both cube
                        int magnitude = node.Magnitude(activeCubes[activeIndex]);
                        if (magnitude < 1.75)
                        {
                            if ((*boundsCoordinates)[0].first > x)
                                (*boundsCoordinates)[0].first = x;
                            else if ((*boundsCoordinates)[0].second < x)
                                (*boundsCoordinates)[0].second = x;

                            if ((*boundsCoordinates)[1].first > y)
                                (*boundsCoordinates)[1].first = y;
                            else if ((*boundsCoordinates)[1].second < y)
                                (*boundsCoordinates)[1].second = y;
                        }
                    }

                    activeCubes.push_back(node);
                }
            }
            y++;
        }

        // We make sure we study all neighbors by increasing/decreasing bounds by one.
        // We already increased "y" in the last loop run
        (*boundsCoordinates)[1].second = y - 1;
        for (size_t i = 0; i < boundsCoordinates->size(); i++)
        {
            (*boundsCoordinates)[i].second += 1;
        }
    }

    return activeCubes;
}

/// <summary>
/// Find and return how many cubes are left in the active state after the N cycle
/// </summary>
vector<Node> SimulateConwayCycles(string fileName, int dimensions, int nbCycles)
{
    // Pairs are in order => (x, y, z, w)
    // We contruct the boundsCoordinates to only study the minimal numbers of nodes possibles (based on previous activated cubes)
    // Bounds will create a cube (or hypercube) of coordinates to iterate over that could become new activate cubes.
    vector<pair<int, int>> boundsCoordinates = vector<pair<int, int>>(dimensions, make_pair(0, 0));
    vector<Node> activeCubes = GetStartingActiveNodes(fileName , &boundsCoordinates);

    // Run all cycles
    for (size_t i = 0; i < nbCycles; i++)
    {
        vector<Node> finalNodes = RunCycle(activeCubes, &boundsCoordinates, dimensions);
        activeCubes = finalNodes;
    }

    return activeCubes;
}
