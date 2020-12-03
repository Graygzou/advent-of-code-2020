#pragma once
#include <string>
#include <fstream>

using namespace std;

class Utils
{

public:
	static int CreateIntArrayFromInputFile(const char* fileName, int* intArray);
	static int CreateStringArrayFromInputFile(const char* fileName, string* intArray);
};

