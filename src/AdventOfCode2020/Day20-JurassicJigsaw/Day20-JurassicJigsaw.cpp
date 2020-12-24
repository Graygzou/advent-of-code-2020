// Day20-JurassicJigsaw.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

using namespace std;

map<string, vector<int>> CreateUniqueIdsFromTileSides(ifstream *file)
{
    map<string, vector<int>> uniqueIds;

    string line;
    
    while (getline(*file, line))
    {
        string leftSide("");
        string rightSide("");

        // Get ID in Header
        cmatch cm;
        regex e("(?:Tile )([0-9]*)\:");
        regex_match(line.c_str(), cm, e);

        int id = atoi(cm[1].str().c_str());
        cout << id << endl;

        int index = 0;
        while (getline(*file, line) && !line.empty())
        {
            leftSide += line[0];
            rightSide += line[line.size() - 1];

            if (index == 0 || index == 9)
            {
                if (uniqueIds.find(line) == uniqueIds.end())
                {
                    uniqueIds.insert(make_pair(line, vector<int>()));
                }

                if (find(uniqueIds[line].begin(), uniqueIds[line].end(), id) == uniqueIds[line].end())
                {
                    uniqueIds[line].push_back(id);
                }

                reverse(line.begin(), line.end());
                if (uniqueIds.find(line) == uniqueIds.end())
                {
                    uniqueIds.insert(make_pair(line, vector<int>()));
                }

                if (find(uniqueIds[line].begin(), uniqueIds[line].end(), id) == uniqueIds[line].end())
                {
                    uniqueIds[line].push_back(id);
                }
            }

            index++;
        }

        // Left side
        if (uniqueIds.find(leftSide) == uniqueIds.end())
            uniqueIds.insert(make_pair(leftSide, vector<int>()));
        if (find(uniqueIds[leftSide].begin(), uniqueIds[leftSide].end(), id) == uniqueIds[leftSide].end())
            uniqueIds[leftSide].push_back(id);

        reverse(leftSide.begin(), leftSide.end());

        if (uniqueIds.find(leftSide) == uniqueIds.end())
            uniqueIds.insert(make_pair(leftSide, vector<int>()));
        if (find(uniqueIds[leftSide].begin(), uniqueIds[leftSide].end(), id) == uniqueIds[leftSide].end())
            uniqueIds[leftSide].push_back(id);

        // Right side
        if (uniqueIds.find(rightSide) == uniqueIds.end())
            uniqueIds.insert(make_pair(rightSide, vector<int>()));
        if (find(uniqueIds[rightSide].begin(), uniqueIds[rightSide].end(), id) == uniqueIds[rightSide].end())
            uniqueIds[rightSide].push_back(id);

        reverse(rightSide.begin(), rightSide.end());

        if (uniqueIds.find(rightSide) == uniqueIds.end())
            uniqueIds.insert(make_pair(rightSide, vector<int>()));
        if (find(uniqueIds[rightSide].begin(), uniqueIds[rightSide].end(), id) == uniqueIds[rightSide].end())
            uniqueIds[rightSide].push_back(id);
    }

    return uniqueIds;
}

bool cmp(pair<int, int>& pair1, pair<int, int>& pair2)
{
    return pair1.second < pair2.second;
}

vector<pair<int, int>> sort(map<int, int>& map)
{
    vector<pair<int, int>> vectorSorted;

    for (auto& it : map)
    {
        vectorSorted.push_back(it);
    }

    sort(vectorSorted.begin(), vectorSorted.end(), cmp);
    return vectorSorted;
}

void Part1(string fileName)
{
    std::ifstream file;
    file.open(fileName);
    if (file.is_open())
    {
        map<string, vector<int>> rules = CreateUniqueIdsFromTileSides(&file);
        map<int, int> nbCommunSide;

        for (auto it = rules.begin(); it != rules.end(); ++it)
        {
            if (it->second.size() == 2)
            {
                for (size_t i = 0; i < it->second.size(); i++)
                {
                    if (nbCommunSide.find(it->second[i]) == nbCommunSide.end())
                        nbCommunSide.insert(make_pair(it->second[i], 0));

                    nbCommunSide[it->second[i]]++;
                }
            }
        }

        vector<pair<int, int>> sortedSides = sort(nbCommunSide);

        int index = 0;
        unsigned long long result = 1;
        for (auto& it : sortedSides)
        {
            if (index < 4)
            {
                result *= it.first;
            }
            index++;

            cout << it.first << ' ' << it.second << endl;
        }

        std::cout << "Result for part 1 is " << result << std::endl;
    }
}

int main()
{
    cout << "Jurassic Jigsaw " << endl;

    Part1("input.txt");
}
