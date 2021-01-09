#pragma once
#include <iostream>
#include <string>
#include "Tile.h"

class Tile;

class Border
{
public:
    Border(Tile* tile1, Tile* tile2, std::string pattern);
    Border* Copy();
    Tile* GetOtherTile(int id);
    void Switch(Tile* tileToswitch);
    Tile* tile1;
    Tile* tile2;
    std::string pattern;
};