#pragma once
#include <string>

class Pattern
{
public:
	std::string topPattern;
	bool uniqueTop;
	std::string bottomPattern;
	bool uniqueBottom;
	std::string leftPattern;
	bool uniqueLeft;
	std::string rightPattern;
	bool uniqueRight;


	bool Match(Tile* tile);
};