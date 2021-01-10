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
    void RotatePattern(SidePosition from, SidePosition to);
    void Flip();
    void Rotate90ClockWise();
};