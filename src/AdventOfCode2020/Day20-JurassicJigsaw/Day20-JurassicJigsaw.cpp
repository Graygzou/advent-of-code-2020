// Day20-JurassicJigsaw.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <queue>
#include <regex>

#include "Tile.h"
#include "Border.h"
#include "Pattern.h"

using namespace std;

map<pair<int, int>, Tile*> ConstructFullGrid(string fileName);
unsigned long long MultiplyCornerIds(map<pair<int, int>, Tile*> grid);
Tile* CreateMergedImage(map<pair<int, int>, Tile*> grid);
int CountDialsInPicture(Tile* fullImage, char dialPattern);
int CountSeaMonsters(Tile* fullImage);

int main(int argc, char** argv)
{
    cout << "Jurassic Jigsaw " << endl;

    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }

    map<pair<int, int>, Tile*> finalGrid = ConstructFullGrid(fileName);

    // Part 1
    unsigned long long part1Result = MultiplyCornerIds(finalGrid);
    std::cout << "Result for part 1 is " << part1Result << std::endl;

    // Part 2
    const int dialIncludedInSeaMonster = 15;
    Tile* fullImage = CreateMergedImage(finalGrid);
    int totalNumberOfDial = CountDialsInPicture(fullImage, '#');
    int seaMonstersCount = CountSeaMonsters(fullImage);
    std::cout << "Result for part 2 is " << totalNumberOfDial - seaMonstersCount * dialIncludedInSeaMonster << std::endl;
}

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

void Tile::Flip(bool flipBorder)
{
    if (flipBorder)
    {
        this->top->pattern = ReverseString(this->top->pattern);
        this->bottom->pattern = ReverseString(this->bottom->pattern);

        Border* temp = this->right;
        this->right = this->left;
        this->left = temp;
    }

    // Apply to image
    for (size_t i = 0; i < lines.size(); i++)
    {
        lines[i] = ReverseString(lines[i]);
    }
}

void Tile::Rotate90ClockWise(bool flipBorders)
{
    if (flipBorders)
    {
        Border* temp = this->left;
        this->left = this->bottom;
        this->bottom = this->right;
        this->right = this->top;
        this->top = temp;
    }

    // Apply to image
    vector<string> newLines(lines.size(), "");
    for (int i = lines.size() - 1; i >= 0; i--)
    {
        for (int j = lines[i].size() - 1; j >= 0; j--)
        {
            newLines[j] += lines[i][j];
        }
    }
    lines = newLines;
}
#pragma endregion


#pragma region Border
Border::Border(Tile* tile1, Tile* tile2, string pattern)
{
    this->pattern = pattern;
    this->tile1 = tile1;
    this->tile2 = tile2;
}
#pragma endregion

#pragma region Pattern
bool Pattern::Match(Tile* tile)
{
    // top checks
    if (!(this->uniqueTop && tile->top->isUnique || 
        !this->uniqueTop && this->topPattern.empty() ||
        this->topPattern == tile->top->pattern ||
        this->topPattern == ReverseString(tile->top->pattern)))
    {
        return false;
    }

    // bottom checks
    if (!(this->uniqueBottom && tile->bottom->isUnique ||
        !this->uniqueBottom && this->bottomPattern.empty() ||
        this->bottomPattern == tile->bottom->pattern ||
        this->bottomPattern == ReverseString(tile->bottom->pattern)))
    {
        return false;
    }

    // left checks
    if (!(this->uniqueLeft && tile->left->isUnique ||
        !this->uniqueLeft && this->leftPattern.empty() ||
        this->leftPattern == tile->left->pattern ||
        this->leftPattern == ReverseString(tile->left->pattern)))
    {
        return false;
    }

    // right checks
    if (!(this->uniqueRight && tile->right->isUnique ||
        !this->uniqueRight && this->rightPattern.empty() ||
        this->rightPattern == tile->right->pattern || 
        this->rightPattern == ReverseString(tile->right->pattern)))
    {
        return false;
    }

    return true;
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

void InitializeUniqueSide(vector<Tile*> tiles)
{
    for (size_t i = 0; i < tiles.size(); i++)
    {
        Tile* currentTile = tiles[i];

        vector<pair<Border*, SidePosition>> currentBorders;
        currentBorders.push_back(make_pair(currentTile->top, SidePosition::Top));
        currentBorders.push_back(make_pair(currentTile->right, SidePosition::Right));
        currentBorders.push_back(make_pair(currentTile->bottom, SidePosition::Bottom));
        currentBorders.push_back(make_pair(currentTile->left, SidePosition::Left));

        for (auto bord = currentBorders.begin(); bord != currentBorders.end(); bord++)
        {
            bool isUniqueSide = true;
            string pattern = (*bord).first->pattern;
            for (auto it = tiles.begin(); it != tiles.end(); it++)
            {
                if (*it != currentTile)
                {
                    if (pattern == (*it)->bottom->pattern || pattern == ReverseString((*it)->bottom->pattern))
                    {
                        isUniqueSide = false;
                    }
                    else if (pattern == (*it)->left->pattern || pattern == ReverseString((*it)->left->pattern))
                    {
                        isUniqueSide = false;
                    }
                    else if (pattern == (*it)->top->pattern || pattern == ReverseString((*it)->top->pattern))
                    {
                        isUniqueSide = false;
                    }
                    else if (pattern == (*it)->right->pattern || pattern == ReverseString((*it)->right->pattern))
                    {
                        isUniqueSide = false;
                    }
                }
            }

            if (isUniqueSide)
            {
                if ((*bord).second == SidePosition::Top)
                    currentTile->top->isUnique = true;
                else if((*bord).second == SidePosition::Bottom)
                    currentTile->bottom->isUnique = true;
                else if((*bord).second == SidePosition::Left)
                    currentTile->left->isUnique = true;
                else if((*bord).second == SidePosition::Right)
                    currentTile->right->isUnique = true;
            }
        }
    }
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

int FindTileMatchingPattern(vector<Tile*> tiles, Tile* firstCorner, Pattern pattern)
{
    for (size_t i = 0; i < tiles.size(); i++)
    {
        for (size_t z = 0; z < 2; z++)
        {
            // Test all configuration here
            for (size_t j = 0; j < 4; j++)
            {
                if (pattern.Match(tiles[i]))
                {
                    *firstCorner = *tiles[i];
                    return i;
                }

                tiles[i]->Rotate90ClockWise();
            }

            tiles[i]->Flip();
        }
    }

    return -1;
}

map<pair<int, int>, Tile*> ConstructFullGrid(string fileName)
{
    map<pair<int, int>, Tile*> finalGrid;

    std::ifstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    vector<Tile*> tiles;
    map<string, vector<int>> rules = CreateUniqueIdsFromTileSides(&file, &tiles);
    InitializeUniqueSide(tiles);

    Tile* firstCorner = nullptr;

    map<pair<int, int>, Pattern*> patterns;
    queue<pair<int, int>> nextPositions;

    // Create and insert first pattern to find a top left tile
    Pattern* pattern = new Pattern();
    pattern->uniqueTop = true;
    pattern->uniqueLeft = true;
    patterns.insert(make_pair(make_pair(0, 0), pattern));
    nextPositions.push(make_pair(0, 0));

    int currentTileIndex = 0;
    while (tiles.size() > 0)
    {
        Tile* currentTile = new Tile(0);

        pair<int, int> currentPos = nextPositions.front();
        nextPositions.pop();

        if (finalGrid.find(currentPos) != finalGrid.end())
        {
            // The tile was already found.
            continue;
        }

        int tileIndex = FindTileMatchingPattern(tiles, currentTile, *(patterns[currentPos]));
        if (firstCorner == nullptr)
        {
            firstCorner = currentTile;
        }

        tiles.erase(tiles.begin() + tileIndex);
        finalGrid.insert(make_pair(currentPos, currentTile));

        // Build the next two patterns (2 sides left)
        for (size_t i = 0; i < 2; i++)
        {
            pair<int, int> nextPos = make_pair(0, 0);

            // Right
            if (i == 0 && !currentTile->right->isUnique)
            {
                nextPos = make_pair(currentPos.first + 1, currentPos.second);
                if (patterns.find(nextPos) == patterns.end())
                {
                    patterns.insert(make_pair(nextPos, new Pattern()));
                }

                if (currentTile->top->isUnique)
                    patterns[nextPos]->uniqueTop = true;

                patterns[nextPos]->leftPattern = currentTile->right->pattern;

                nextPositions.push(nextPos);
            }
            // Bottom
            else if (!currentTile->bottom->isUnique)
            {
                nextPos = make_pair(currentPos.first, currentPos.second + 1);
                if (patterns.find(nextPos) == patterns.end())
                {
                    patterns.insert(make_pair(nextPos, new Pattern()));
                }

                if (currentTile->left->isUnique)
                    patterns[nextPos]->uniqueLeft = true;

                patterns[nextPos]->topPattern = currentTile->bottom->pattern;

                nextPositions.push(nextPos);
            }
        }
    }

    return finalGrid;
}


int CountSeaMonsters(Tile* fullImage)
{
    // Count of many sea monsters there is in the picture
    // Warning ! Doing it like that could detect sea monsters but "splitted" (every line will not be aligned with each other
    vector<regex> seaMonsterPattern = {
        regex(".{18}#."),
        regex("#.{4}##.{4}##.{4}###"),
        regex(".#.{2}#.{2}#.{2}#.{2}#.{2}#.{3}")
    };
    int seaMonsterLength = 20;
    int seaMonsterHeight = 3;

    // Find sea monsters
    int nbLoop = 0;
    int seaMonsterCount = 0;
    do
    {
        for (size_t i = 0; i <= fullImage->lines.size() - seaMonsterHeight; i++)
        {
            for (size_t j = 0; j <= fullImage->lines[i].size() - seaMonsterLength; j++)
            {
                if (regex_match(fullImage->lines[i].substr(j, seaMonsterLength), seaMonsterPattern[0]) &&
                    regex_match(fullImage->lines[i + 1].substr(j, seaMonsterLength), seaMonsterPattern[1]) &&
                    regex_match(fullImage->lines[i + 2].substr(j, seaMonsterLength), seaMonsterPattern[2]))
                {
                    seaMonsterCount++;
                    j += seaMonsterLength;
                }
            }
                
        }

        if ((nbLoop + 1) % 4 == 0)
        {
            // flip it;
            fullImage->Flip(false);
        }
        else
        {
            // rotate it
            fullImage->Rotate90ClockWise();
        }
        nbLoop++;
    } while (seaMonsterCount == 0);

    return seaMonsterCount;
}

unsigned long long MultiplyCornerIds(map<pair<int, int>, Tile*> grid)
{
    unsigned long long result = 1;

    int lineSize = sqrt(grid.size());
    for (size_t i = 0; i < grid.size(); i++)
    {
        pair<int, int> position = make_pair(i % lineSize, i / lineSize);
        if (i == 0 ||
            i == lineSize - 1 ||
            i == grid.size() - lineSize ||
            i == grid.size() - 1)
        {
            result *= grid[position]->id;
        }
    }

    return result;
}

Tile* CreateMergedImage(map<pair<int, int>, Tile*> grid)
{
    Tile* fullImage = new Tile(0);

    int lineSize = sqrt(grid.size());
    vector<string> currentlines;
    for (size_t i = 0; i < grid.size(); i++)
    {
        pair<int, int> position = make_pair(i % lineSize, i / lineSize);
        if (position.first == 0)
        {
            currentlines.clear();
            currentlines = grid[position]->lines;
        }
        else
        {
            for (size_t j = 0; j < currentlines.size(); j++)
            {
                currentlines[j] += grid[position]->lines[j];
            }
        }

        if (position.first == lineSize - 1)
        {
            for (size_t j = 0; j < currentlines.size(); j++)
            {
                fullImage->lines.push_back(currentlines[j]);
            }
        }
    }

    return fullImage;
}

int CountDialsInPicture(Tile* fullImage, char dialPattern)
{
    int totalNumberOfDial = 0;
    for (size_t i = 0; i < fullImage->lines.size(); i++)
    {
        for (size_t j = 0; j < fullImage->lines[i].size(); j++)
        {
            if (fullImage->lines[i][j] == dialPattern)
            {
                totalNumberOfDial++;
            }
        }
    }

    return totalNumberOfDial;
}