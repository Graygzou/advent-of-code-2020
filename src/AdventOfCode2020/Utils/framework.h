#pragma once
#include <string>
#include <fstream>
#include <iostream>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

int CreateIntArrayFromInputFile(const char* fileName, int* intArray);

int CreateStringArrayFromInputFile(const char* fileName, std::string* intArray);