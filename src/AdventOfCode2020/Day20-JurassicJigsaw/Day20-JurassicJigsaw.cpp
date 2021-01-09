// Day20-JurassicJigsaw.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include "Tile.h"
#include "Border.h"

using namespace std;

string ReverseString(string str)
{
    reverse(str.begin(), str.end());
    return str;
}

#pragma region Tile
Tile::Tile(int id)
{
    this->id = id;
}

void Tile::RotatePattern(SidePosition from, SidePosition to)
{
    // If they are opposed
    if (from == SidePosition::Bottom && to == SidePosition::Top
        || from == SidePosition::Top && to == SidePosition::Bottom
        || from == SidePosition::Right && to == SidePosition::Left
        || from == SidePosition::Left && to == SidePosition::Right)
    {
        // nothing to do;
        return;
    }
    else if (from == to)
    {
        Border* temp = this->top->Copy();
        this->top = this->bottom;
        this->bottom = temp;

        temp = this->right->Copy();
        this->right = this->left;
        this->left = temp;

        // Rotate everything by 180 (reverse ?)
        for (size_t i = 0; i < lines.size(); i++)
        {
            lines[i] = ReverseString(lines[i]);
        }
    }
    else if (from == SidePosition::Right && to == SidePosition::Top
        || from == SidePosition::Bottom && to == SidePosition::Left
        || from == SidePosition::Left && to == SidePosition::Bottom
        || from == SidePosition::Top && to == SidePosition::Right)
    {
        // Rotate by 90 degree
        Border* temp = this->left->Copy();
        this->left = this->top;
        this->top = this->right;
        this->right = this->bottom;
        this->bottom = temp;

        // lines
        vector<string> newLines(lines.size(), "");
        for (size_t i = 0; i < lines.size(); i++)
        {
            for (int j = lines[i].size() - 1; j >= 0; j--)
            {
                newLines[j] += lines[i][j];
            }
        }
    }
    else if (from == SidePosition::Right && to == SidePosition::Bottom
        || from == SidePosition::Bottom && to == SidePosition::Right
        || from == SidePosition::Left && to == SidePosition::Top
        || from == SidePosition::Top && to == SidePosition::Left)
    {
        // Rotate by -90 degree
        Border* temp = this->left->Copy();
        this->left = this->bottom;
        this->bottom = this->right;
        this->right = this->top;
        this->top = temp;

        // lines
        vector<string> newLines(lines.size(), "");
        for (int i = lines.size() - 1; i >= 0; i--)
        {
            for (int j = lines[i].size() - 1; j >= 0; j--)
            {
                newLines[j] += lines[i][j];
            }
        }
    }
    else
    {
        throw new exception("bug");
    }
}

void Tile::AddBorder(SidePosition direction, Tile* tile2)
{
    switch (direction)
    {
    case Top:
        //top = new Border(this, tile2);
        break;
    case Right:
        break;
    case Bottom:
        break;
    case Left:
        break;
    default:
        break;
    }
}
#pragma endregion


#pragma region Border
Border::Border(Tile* tile1, Tile* tile2, string pattern)
{
    this->pattern = pattern;
    this->tile1 = tile1;
    this->tile2 = tile2;
}

Border* Border::Copy()
{
    return new Border(tile1, tile2, pattern);
}

Tile* Border::GetOtherTile(int id)
{
    Tile* tile = NULL;
    if (tile1->id == id)
    {
        tile = tile2;
    }
    else if (tile2->id == id)
    {
        tile = tile1;
    }

    return tile;
}

void Border::Switch(Tile* tileToswitch)
{
    if (tile1 == tileToswitch)
    {
        tile1->isFlipped = true;
        tile1->rotatingAngle += 180;
    }
    else if (tile2 == tileToswitch)
    {
        tile2->isFlipped = true;
    }
    else
    {
        cout << "Errors" << endl;
    }
}
#pragma endregion

//enum SidePosition { Top, Right, Bottom, Left };

map<string, vector<int>> CreateUniqueIdsFromTileSides(ifstream* file, vector<Tile*>* tiles)
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
        Tile* currentTile = new Tile(id);

        int index = 0;
        while (getline(*file, line) && !line.empty())
        {
            leftSide += line[0];
            rightSide += line[line.size() - 1];

            if (index == 0 || index == 9)
            {
                if (index == 0)
                {
                    currentTile->top = new Border(currentTile, nullptr, line);
                }
                else
                {
                    currentTile->bottom = new Border(currentTile, nullptr, line);
                }

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
            else
            {
                currentTile->lines.push_back(line.substr(1, line.size() - 2));
            }

            index++;
        }

        // Left side
        currentTile->left = new Border(currentTile, nullptr, leftSide);
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
        currentTile->right = new Border(currentTile, nullptr, rightSide);
        if (uniqueIds.find(rightSide) == uniqueIds.end())
            uniqueIds.insert(make_pair(rightSide, vector<int>()));
        if (find(uniqueIds[rightSide].begin(), uniqueIds[rightSide].end(), id) == uniqueIds[rightSide].end())
            uniqueIds[rightSide].push_back(id);

        reverse(rightSide.begin(), rightSide.end());

        if (uniqueIds.find(rightSide) == uniqueIds.end())
            uniqueIds.insert(make_pair(rightSide, vector<int>()));
        if (find(uniqueIds[rightSide].begin(), uniqueIds[rightSide].end(), id) == uniqueIds[rightSide].end())
            uniqueIds[rightSide].push_back(id);


        tiles->push_back(currentTile);
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
        vector<Tile*> tiles;
        map<string, vector<int>> rules = CreateUniqueIdsFromTileSides(&file, &tiles);

        vector<Tile*> grid;
        vector<Border*> gridBorders;

        //gridBorders.push_back(tiles[0]->top);
        //gridBorders.push_back(tiles[0]->right);
        //gridBorders.push_back(tiles[0]->bottom);
        //gridBorders.push_back(tiles[0]->left);
        //tiles.erase(tiles.begin());

        int loop = 0;
        int limit = 20;
        int currentTileIndex = 0;
        while (tiles.size() > 0 && loop < limit)
        {
            Tile* currentTile = tiles[currentTileIndex];
            vector<pair<Border*, SidePosition>> currentBorders;
            currentBorders.push_back(make_pair(currentTile->top, SidePosition::Top));
            currentBorders.push_back(make_pair(currentTile->right, SidePosition::Right));
            currentBorders.push_back(make_pair(currentTile->bottom, SidePosition::Bottom));
            currentBorders.push_back(make_pair(currentTile->left, SidePosition::Left));

            int nbMatchingSide = 0;
            int nbUniqueSide = 0;

            // We only care if we find two unique side and/or matching pattern

            //for (size_t i = 0; i < currentBorders.size(); i++)
            for (auto bord = currentBorders.begin(); bord != currentBorders.end(); bord++)
            {
                vector<pair<Tile*, bool>> candidates;
                SidePosition side;

                bool isUniqueSide = true;
                string pattern = (*bord).first->pattern;
                for (auto it = tiles.begin(); it != tiles.end(); it++)
                {
                    if (*it != currentTile)
                    {
                        bool flipped = false;
                        if (pattern == (*it)->bottom->pattern || (flipped = pattern == ReverseString((*it)->bottom->pattern)))
                        {
                            isUniqueSide = false;
                            candidates.push_back(make_pair(*it, flipped));
                            side = SidePosition::Bottom;
                            //cout << (*bord).first->tile1->id << " tile match pattern " << pattern << " with bottom of " << (*it)->id << " and is flipped =" << flipped << endl;
                        }
                        else if (pattern == (*it)->left->pattern || (flipped = pattern == ReverseString((*it)->left->pattern)))
                        {
                            isUniqueSide = false;
                            candidates.push_back(make_pair(*it, flipped));
                            side = SidePosition::Left;
                            //cout << (*bord).first->tile1->id << " tile match pattern " << pattern << " with left of " << (*it)->id << " and is flipped =" << flipped << endl;
                        }
                        else if (pattern == (*it)->top->pattern || (flipped = pattern == ReverseString((*it)->top->pattern)))
                        {
                            isUniqueSide = false;
                            //if (flipped)
                            //{
                            //    (*it)->isFlipped = true;
                            //}
                            candidates.push_back(make_pair(*it, flipped));
                            side = SidePosition::Top;
                            //cout << (*bord).first->tile1->id << " tile match pattern " << pattern << " with top " << (*it)->id << " and is flipped =" << flipped << endl;
                        }
                        else if (pattern == (*it)->right->pattern || (flipped = pattern == ReverseString((*it)->right->pattern)))
                        {
                            isUniqueSide = false;
                            candidates.push_back(make_pair(*it, flipped));
                            side = SidePosition::Right;
                            //cout << (*bord).first->tile1->id << " tile match pattern " << pattern << " with right " << (*it)->id << " and is flipped =" << flipped << endl;
                        }
                    }
                }

                cout << "Unique Side = " << isUniqueSide << endl;
                if (isUniqueSide)
                {
                    nbUniqueSide++;
                }

                if (candidates.size() == 1)
                {
                    candidates[0].first->isFlipped = candidates[0].second;
                    candidates[0].first->RotatePattern((*bord).second, side);
                    (*bord).first->tile2 = candidates[0].first;

                    switch ((*bord).second)
                    {
                    case Top:
                        candidates[0].first->bottom = (*bord).first;
                        break;
                    case Right:
                        candidates[0].first->left = (*bord).first;
                        break;
                    case Bottom:
                        candidates[0].first->top = (*bord).first;
                        break;
                    case Left:
                        candidates[0].first->right = (*bord).first;
                        break;
                    default:
                        break;
                    }

                    nbMatchingSide++;
                }
            }

            cout << "Nb Unique Side " <<  nbUniqueSide << endl;
            if (nbUniqueSide >= 2)
            {
                grid.push_back(currentTile);
                tiles.erase(tiles.begin() + currentTileIndex);
                cout << "End for " << currentTile->id << endl;
            }
            else if (nbUniqueSide == 1 && nbMatchingSide >= 1 || nbMatchingSide >= 2)
            {
                grid.push_back(currentTile);
                tiles.erase(tiles.begin() + currentTileIndex);
                cout << "End for " << currentTile->id << endl;
            }

            loop++;
            currentTileIndex++;
            if (tiles.size() > 0)
            {
                currentTileIndex %= tiles.size();
            }
        }

        // Find the top left tile
        Tile* topLeftTile = NULL;
        for (auto it = grid.begin(); it != grid.end(); it++)
        {
            if ((*it)->top->tile2 == NULL && (*it)->left->tile2 == NULL)
            {
                topLeftTile = *it;
            }
        }

        // Display the grid
        vector<string> lines;
        Tile* currentTile = topLeftTile;
        while (currentTile != nullptr)
        {
            // concatenate Tile
            if (lines.empty())
            {
                lines = currentTile->lines;
            }
            else
            {
                for (size_t i = 0; i < lines.size(); i++)
                {
                    lines[i] += currentTile->lines[i];
                }
            }

            //if (currentTile->isFlipped)
            //{
            //    currentTile = currentTile->left->GetOtherTile(currentTile->id);
            //}
            //else
            //{
                currentTile = currentTile->right->GetOtherTile(currentTile->id);
            //}
        }


        for (size_t i = 0; i < lines.size(); i++)
        {
            cout << lines[i] << endl;
        }



        //cout << tiles.size() << endl;
        //for (auto it = tiles.begin(); it != tiles.end(); ++it)
        //{
        //    cout << it->first << endl;
        //}

        //map<int, int> nbCommunSide;
        //for (auto it = rules.begin(); it != rules.end(); ++it)
        //{
        //    if (it->second.size() == 2)
        //    {
        //        for (size_t i = 0; i < it->second.size(); i++)
        //        {
        //            cout <<
        //                tiles[it->second[i]]->AddBorder()


        //                if (nbCommunSide.find(it->second[i]) == nbCommunSide.end())
        //                    nbCommunSide.insert(make_pair(it->second[i], 0));

        //            nbCommunSide[it->second[i]]++;
        //        }
        //    }
        //}

        //vector<pair<int, int>> sortedSides = sort(nbCommunSide);

        // Display grid
        //cout << grid.Display() << endl;


        int index = 0;
        unsigned long long result = 1;
        //for (auto& it : sortedSides)
        //{
        //    if (index < 4)
        //    {
        //        result *= it.first;
        //    }
        //    index++;

        //    cout << it.first << ' ' << it.second << endl;
        //}

        std::cout << "Result for part 1 is " << result << std::endl;
    }
}

int main()
{
    cout << "Jurassic Jigsaw " << endl;

    Part1("example.txt");
}