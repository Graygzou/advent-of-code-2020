#pragma once
#include <string>
#include <vector>
#include "Border.h"

enum SidePosition { Top, Right, Bottom, Left };

class Border;

class Tile
{
public:
    int id;
    bool isFlipped = false;
    int rotatingAngle;
    int nbBorders = 0;

    Border* top;
    Border* bottom;
    Border* left;
    Border* right;
    std::vector<std::string> lines;

    Tile(int id);
    void RotatePattern(SidePosition from, SidePosition to);
    void AddBorder(SidePosition direction, Tile* tile2);
};