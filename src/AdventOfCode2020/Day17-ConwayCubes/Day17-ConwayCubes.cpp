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
    //vector<Node> neighbors = vector<Node>();
    int positonX = -1;
    int positonY = -1;
    int positonZ = -1;

    Node(int x, int y, int z)
    {
        //neighbors = vector<Node>();
        positonX = x;
        positonY = y;
        positonZ = z;
    }

    float SquaredMagnitude(Node destination)
    {
        int vectorX = destination.positonX - positonX;
        int vectorY = destination.positonY - positonY;
        int vectorZ = destination.positonZ - positonZ;
        return vectorX * vectorX + vectorY * vectorY + vectorZ * vectorZ;
    }

    float Magnitude(Node destination)
    {
        return sqrt(SquaredMagnitude(destination));
    }

    bool Equals(Node node)
    {
        return Equals(node.positonX, node.positonY, node.positonZ);
    }

    bool Equals(int x, int y, int z)
    {
        return positonX == x && positonY == y && positonZ == z;
    }

    void Display()
    {
        std::cout << " Position is (" << positonX << "," << positonY << "," << positonZ << ")" << endl;
    }

    bool operator<(const Node& rhs) const noexcept
    {
        return this->positonX < rhs.positonX 
            || this->positonX == rhs.positonX && this->positonY < rhs.positonY
            || this->positonX == rhs.positonX && this->positonY == rhs.positonY && this->positonZ < rhs.positonZ;
    }

    bool operator==(const Node& rhs) const noexcept
    {
        return this->positonX == rhs.positonX && this->positonY == rhs.positonY && this->positonZ == rhs.positonZ;
    }
};

void DisplayGrid(vector<Node> activeCubes, pair<int, int> xBounds, pair<int, int> yBounds, pair<int, int> zBounds)
{
    int gridSize = 5;
    for (int z = zBounds.first; z <= zBounds.second; z++)
    {
        std::cout << "z=" << z << endl;

        for (int x = xBounds.first; x <= xBounds.second; x++)
        {
            for (int y = yBounds.first; y <= yBounds.second; y++)
            {
                bool found = false;
                for (int i = 0; !found && i < activeCubes.size(); i++)
                {
                    if (activeCubes[i].Equals(x, y, z))
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

void GetCandidateNode(Node node1, Node node2, vector<Node> *candidates)
{
    //vector<Node> currentCandidates;

    //int minX = min(node1.positonX, node2.positonX) - 1;
    //int maxX = max(node1.positonX, node2.positonX) + 1;

    //int minY = min(node1.positonY, node2.positonY) - 1;
    //int maxY = max(node1.positonY, node2.positonY) + 1;

    //int minZ = min(node1.positonZ, node2.positonZ) - 1;
    //int maxZ = max(node1.positonZ, node2.positonZ) + 1;

    //// Add all the "3D bounding box" points to be later tested
    //for (size_t x = minX; x <= maxX; x++)
    //{
    //    for (size_t y = minY; y <= maxY; y++)
    //    {
    //        for (size_t z = minZ; z < maxZ; z++)
    //        {
    //            Node candidate = Node(x, y, z);
    //            if (find(candidates->begin(), candidates->end(), candidate) == candidates->end())
    //            {
    //                candidates->push_back(candidate);
    //            }
    //        }
    //    }
    //}

    //candidates = currentCandidates;
}

//
//vector<Node> DeactivateNodes(vector<Node> tempActiveCubes)
//{
//    vector<Node> activeCubes;
//    for (auto it = tempActiveCubes.begin(); it != tempActiveCubes.end(); it++)
//    {
//        std::cout << "BLABLABLA " << it->neighbors.size() << endl;
//        //auto nodeSaved = find(tempActiveCubes.begin(), tempActiveCubes.end(), it);
//        if (it->neighbors.size() >= 2 && it->neighbors.size() <= 3)
//        {
//            // Update his neighbors
//            activeCubes.push_back(*it);
//        }
//    }
//
//    std::cout << activeCubes.size() << endl;
//    return activeCubes;
//}

//vector<Node> MergedActiveNodes(vector<Node> nodeWithExtraActives, vector<Node> nodesWithoutInactives, pair<int, int>* xBounds, pair<int, int>* yBounds, pair<int, int>* zBounds)
//{
//    vector<Node> nodes = nodesWithoutInactives;
//
//    for (size_t i = 0; i < nodeWithExtraActives.size(); i++)
//    {
//        if (nodeWithExtraActives[i].positonX < xBounds->first)
//            xBounds->first = nodeWithExtraActives[i].positonX;
//        else if (nodeWithExtraActives[i].positonX > xBounds->second)
//            xBounds->second = nodeWithExtraActives[i].positonX;
//
//        if (nodeWithExtraActives[i].positonY < yBounds->first)
//            yBounds->first = nodeWithExtraActives[i].positonY;
//        else if (nodeWithExtraActives[i].positonY > yBounds->second)
//            yBounds->second = nodeWithExtraActives[i].positonY;
//
//        if (nodeWithExtraActives[i].positonZ < zBounds->first)
//            zBounds->first = nodeWithExtraActives[i].positonZ;
//        else if (nodeWithExtraActives[i].positonZ > zBounds->second)
//            zBounds->second = nodeWithExtraActives[i].positonZ;
//
//        if (find(nodes.begin(), nodes.end(), nodeWithExtraActives[i]) == nodes.end())
//        {
//            // Link it to existing nodes
//            for (size_t j = 0; j < nodes.size(); j++)
//            {
//                float magnitude = nodeWithExtraActives[i].Magnitude(nodes[j]);
//                if (magnitude < 1.75)
//                {
//                    nodeWithExtraActives[i].neighbors.push_back(nodes[j]);
//                    nodes[j].neighbors.push_back(nodeWithExtraActives[i]);
//                }
//            }
//
//            nodes.push_back(nodeWithExtraActives[i]);
//        }
//    }
//
//    xBounds->first--;
//    xBounds->second++;
//
//    yBounds->first--;
//    yBounds->second++;
//
//    zBounds->first--;
//    zBounds->second++;
//
//    return nodes;
//}


void UpdateBounds(vector<Node> activeCubes, pair<int, int>* xBounds, pair<int, int>* yBounds, pair<int, int>* zBounds)
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
    }

    xBounds->first--;
    xBounds->second++;

    yBounds->first--;
    yBounds->second++;

    zBounds->first--;
    zBounds->second++;
}

vector<Node> RunCycle(vector<Node> activeCubes, pair<int, int> *xBounds, pair<int, int> *yBounds, pair<int, int> *zBounds)
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
                if (magnitude < 1.75)
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

    cout << "Size of temp " << tempActiveCubes.size() << endl;
    DisplayGrid(tempActiveCubes, *xBounds, *yBounds, *zBounds);

    // Check if we should activate new nodes.
    for (int z = zBounds->first; z <= zBounds->second; z++)
    {
        for (int x = xBounds->first; x <= xBounds->second; x++)
        {
            for (int y = yBounds->first; y <= yBounds->second; y++)
            {
                Node candidate = Node(x, y, z);

                auto it = find(activeCubes.begin(), activeCubes.end(), candidate);
                if (it == activeCubes.end())
                {
                    // Node not active yet.

                    int NeigborsCount = 0;
                    for (size_t i = 0; i < activeCubes.size(); i++)
                    {
                        //std::cout << "mangitude is " << candidate.Magnitude(activeCubes[i]) << endl;
                        // sqrt(3) == 1,73205081
                        float magnitude = candidate.Magnitude(activeCubes[i]);
                        if (magnitude < 1.75)
                        {
                            //auto it2 = find(tempActiveCubes.begin(), tempActiveCubes.end(), activeCubes[i]);
                            //if (it2 != tempActiveCubes.end())
                            //{
                            //    //candidate.neighbors.push_back(*it2);
                            //}

                            NeigborsCount++;
                        }
                    }

                    //std::cout << "Neighbors count " << NeigborsCount << endl;
                    if (NeigborsCount == 3)
                    {
                        tempActiveCubes.push_back(candidate);

                        //for (size_t i = 0; i < candidate.neighbors.size(); i++)
                        //{
                        //    //auto it2 = find(tempActiveCubes.begin(), tempActiveCubes.end(), candidate.neighbors[i]);
                        //    //if (it2 != tempActiveCubes.end())
                        //    //{
                        //    //    std::cout << "OOF" << endl;
                        //    candidate.neighbors[i].neighbors.push_back(candidate);
                        //    //}
                        //    //else
                        //    //{
                        //    //    std::cout << "WATTTT" << endl;
                        //    //}
                        //}
                    }
                }
            }
        }
    }

    UpdateBounds(tempActiveCubes, xBounds, yBounds, zBounds);

    //DisplayGrid(tempActiveCubes, *xBounds, *yBounds, *zBounds);

    std::cout << "^^^^^^===================" << endl;

    // Check if we should keep some nodes
    //vector<Node> newNodes2 = DeactivateNodes(activeCubes);
    //DisplayGrid(newNodes2, *xBounds, *yBounds, *zBounds);

    //std::cout << "^^^^^^===================" << endl;
    //vector<Node> finalNodes = MergedActiveNodes(tempActiveCubes, newNodes2, xBounds, yBounds, zBounds);
    return tempActiveCubes;
}

/// <summary>
/// Construct the list of nodes to iters over.
/// </summary>
vector<Node> GetStartingActiveNodes(pair<int, int> *xBounds, pair<int, int> *yBounds, pair<int, int> *zBounds)
{
    vector<Node> activeCubes;

    ifstream file;
    string line;
    file.open("input.txt");
    if (file.is_open())
    {
        int z = 0;
        int x = 0;
        xBounds->first = x - 1;
        zBounds->first = z - 1;

        while (getline(file, line))
        {
            std::cout << line << endl;
            for (size_t y = 0; y < line.size(); y++)
            {
                if (line[y] == '#')
                {
                    Node node = Node(x, y, z);

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
    }

    return activeCubes;
}

void Part1()
{
    pair<int, int> xBounds;
    pair<int, int> yBounds;
    pair<int, int> zBounds;
    vector<Node> activeCubes = GetStartingActiveNodes(&xBounds, &yBounds, &zBounds);

    std::cout << xBounds.first << ", " << xBounds.second << endl;
    std::cout << yBounds.first << ", " << yBounds.second << endl;
    std::cout << zBounds.first << ", " << zBounds.second << endl;

    // Debug
    for (size_t i = 0; i < activeCubes.size(); i++)
    {
        activeCubes[i].Display();
    }

    // Run all cycles
    int nbCycle = 6;
    for (size_t i = 0; i < nbCycle; i++)
    {
        vector<Node> finalNodes = RunCycle(activeCubes, &xBounds, &yBounds, &zBounds);

        for (size_t i = 0; i < activeCubes.size(); i++)
        {
            activeCubes[i].Display();
        }

        // Debug
        DisplayGrid(finalNodes, xBounds, yBounds, zBounds);

        // Update
        activeCubes = finalNodes;

        std::cout << "===================" << endl;
        std::cout << "===================" << endl;
        std::cout << "===================" << endl;
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
