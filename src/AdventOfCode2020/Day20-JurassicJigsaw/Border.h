#pragma once
#include <iostream>
#include <string>
#include "Tile.h"

class Tile;

class Border
{
public:
    Tile* tile1;
    Tile* tile2;
    std::string pattern;
    bool isUnique = false;

    Border(Tile* tile1, Tile* tile2, std::string pattern);
};