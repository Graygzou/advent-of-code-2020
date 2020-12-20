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

void DisplayGrid(vector<Node> activeCubes, pair<int, int> xBounds, pair<int, int> yBounds, pair<int, int> zBounds, pair<int, int> wBounds)
{
    int gridSize = 5;

    for (int w = wBounds.first; w <= wBounds.second; w++)
    {
        for (int z = zBounds.first; z <= zBounds.second; z++)
        {
            std::cout << "z=" << z << "  w=" << w << endl;

            for (int x = xBounds.first; x <= xBounds.second; x++)
            {
                for (int y = yBounds.first; y <= yBounds.second; y++)
                {
                    bool found = false;
                    for (int i = 0; !found && i < activeCubes.size(); i++)
                    {
                        if (activeCubes[i].Equals(x, y, z, w))
                        {
                            std::cout << "#";
                            found = true;
                        }
                    }

                    if (!found)
                    {
                        std::cout << ".";
                    }
                }
                std::cout << endl;
            }
        }
    }
}

void UpdateBounds(vector<Node> activeCubes, pair<int, int>* xBounds, pair<int, int>* yBounds, pair<int, int>* zBounds, pair<int, int>* wBounds)
{
    for (size_t i = 0; i < activeCubes.size(); i++)
    {
        if (activeCubes[i].positonX < xBounds->first)
            xBounds->first = activeCubes[i].positonX;
        else if (activeCubes[i].positonX > xBounds->second)
            xBounds->second = activeCubes[i].positonX;

        if (activeCubes[i].positonY < yBounds->first)
            yBounds->first = activeCubes[i].positonY;
        else if (activeCubes[i].positonY > yBounds->second)
            yBounds->second = activeCubes[i].positonY;

        if (activeCubes[i].positonZ < zBounds->first)
            zBounds->first = activeCubes[i].positonZ;
        else if (activeCubes[i].positonZ > zBounds->second)
            zBounds->second = activeCubes[i].positonZ;

        if (activeCubes[i].positonW < wBounds->first)
            wBounds->first = activeCubes[i].positonW;
        else if (activeCubes[i].positonW > wBounds->second)
            wBounds->second = activeCubes[i].positonW;
    }

    xBounds->first--;
    xBounds->second++;

    yBounds->first--;
    yBounds->second++;

    zBounds->first--;
    zBounds->second++;

    wBounds->first--;
    wBounds->second++;
}

vector<Node> RunCycle(vector<Node> activeCubes, pair<int, int> *xBounds, pair<int, int> *yBounds, pair<int, int> *zBounds, pair<int, int> *wBounds)
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

    // Check if we should activate new nodes.
    for (int w = wBounds->first; w <= wBounds->second; w++)
    {
        for (int z = zBounds->first; z <= zBounds->second; z++)
        {
            for (int x = xBounds->first; x <= xBounds->second; x++)
            {
                for (int y = yBounds->first; y <= yBounds->second; y++)
                {
                    Node candidate = Node(x, y, z, w);

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

                        //std::cout << "Neighbors count " << NeigborsCount << endl;
                        if (NeigborsCount == 3)
                        {
                            tempActiveCubes.push_back(candidate);
                        }
                    }
                }
            }
        }
    }

    // Debug
    //DisplayGrid(tempActiveCubes, *xBounds, *yBounds, *zBounds, *wBounds);

    UpdateBounds(tempActiveCubes, xBounds, yBounds, zBounds, wBounds);

    return tempActiveCubes;
}

/// <summary>
/// Construct the list of nodes to iters over.
/// </summary>
vector<Node> GetStartingActiveNodes(pair<int, int> *xBounds, pair<int, int> *yBounds, pair<int, int> *zBounds, pair<int, int> *wBounds)
{
    vector<Node> activeCubes;

    ifstream file;
    string line;
    file.open("input.txt");
    if (file.is_open())
    {
        int w = 0;
        int z = 0;
        int x = 0;
        xBounds->first = x - 1;
        zBounds->first = z - 1;
        wBounds->first = w - 1;

        while (getline(file, line))
        {
            std::cout << line << endl;
            for (size_t y = 0; y < line.size(); y++)
            {
                if (line[y] == '#')
                {
                    Node node = Node(x, y, z, w);

                    // Find any neighbor active
                    for (int activeIndex = 0; activeIndex < activeCubes.size(); activeIndex++)
                    {
                        // Compute squared magnitude of both cube
                        int magnitude = node.Magnitude(activeCubes[activeIndex]);
                        if (magnitude < 1.75)
                        {
                            if (yBounds->first > y)
                                yBounds->first = y;
                            else if (yBounds->second < y)
                                yBounds->second = y;

                            if (zBounds->first > z)
                                zBounds->first = z;
                            else if (zBounds->second < z)
                                zBounds->second = z;

                            //std::cout << i << y << endl;
                            //std::cout << "Neighbor with (" << activeCubes[i].positonX << "," << activeCubes[i].positonY << "," << activeCubes[i].positonZ << ")" << endl;

                            // Know each other
                            //node.neighbors.push_back(activeCubes[activeIndex]);
                            //activeCubes[activeIndex].neighbors.push_back(node);
                        }
                    }

                    activeCubes.push_back(node);
                }
            }
            x++;
        }
        yBounds->first -= 1;

        xBounds->second = x;
        yBounds->second += 1;
        zBounds->second += 1;
        wBounds->second += 1;
    }

    return activeCubes;
}

void Part1()
{
    pair<int, int> xBounds, yBounds, zBounds, wBounds;
    vector<Node> activeCubes = GetStartingActiveNodes(&xBounds, &yBounds, &zBounds, &wBounds);

    // Run all cycles
    int nbCycle = 6;
    for (size_t i = 0; i < nbCycle; i++)
    {
        vector<Node> finalNodes = RunCycle(activeCubes, &xBounds, &yBounds, &zBounds, &wBounds);
        activeCubes = finalNodes;
    }


    cout << "Result 1 = " << activeCubes.size() << endl;

    // Grid
    //DisplayGrid(activeCubes, xBounds, yBounds, zBounds);
}


int main()
{
    std::cout << "Conway Cubes" << endl;
    Part1();
}
