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

    Border* top;
    Border* bottom;
    Border* left;
    Border* right;
    std::vector<std::string> lines;

    Tile(int id);
    void Flip(bool flipBorder = true);
    void Rotate90ClockWise(bool flipBorder = true);
};