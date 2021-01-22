// TobogganTrajectory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

using namespace std;

constexpr char TREE_SYMBOL = '#';

long long CountNumberOfTreeHitForTrajectories(const char* fileName, tuple<int, int> slopes[], int nbSlopes);

int main(int argc, char** argv)
{
    cout << "Day 3 - Toboggan Trajectory" << endl;

    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }
    
    tuple<int, int> slopesPart1[] = { make_tuple(3, 1) };
    int nbSlopes = 1;

    long long resultPart1 = CountNumberOfTreeHitForTrajectories(fileName, slopesPart1, nbSlopes);
    cout << "Result for part 1 is : " << resultPart1 << endl;

    tuple<int, int> slopesPart2[] =
    {
        make_tuple(1, 1),
        make_tuple(3, 1),
        make_tuple(5, 1),
        make_tuple(7, 1),
        make_tuple(1, 2),
    };
    nbSlopes = 5;

    long long resultPart2 = CountNumberOfTreeHitForTrajectories(fileName, slopesPart2, nbSlopes);
    cout << "Result for part 2 is : " << resultPart2 << endl;
}

int CountNumberOfTreeHit(ifstream* file, tuple<int, int> slope)
{
    int nbTreesMet = 0;

    int currentLine = 0;
    int nextLineNumber = get<1>(slope);

    int xPosition = 0;

    string line;
    while (getline(*file, line))
    {
        if (currentLine == nextLineNumber)
        {
            xPosition = (xPosition + get<0>(slope)) % line.length();
            if (line[xPosition] == TREE_SYMBOL)
            {
                nbTreesMet++;
            }

            nextLineNumber = currentLine + get<1>(slope);
        }

        currentLine++;
    }

    return nbTreesMet;
}

/// <summary>
/// Count how many trees we hit for each slope trajectory we take and multiply them.
/// </summary>
/// <returns>Multiplication of all tree hit per slope.</returns>
long long CountNumberOfTreeHitForTrajectories(const char* fileName, tuple<int, int> slopes[], int nbSlopes)
{
    ifstream inputFile;
    inputFile.open(fileName);
    if (!inputFile.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    long long resultPart2 = 1;
    for (size_t i = 0; i < nbSlopes; i++)
    {
        resultPart2 *= CountNumberOfTreeHit(&inputFile, slopes[i]);

        // Instead of doing this, we could go through the file once and compute each position as we go through it.
        // We will have to store N xPosition and basically N if statements for each slope to check against at each lines.
        inputFile.clear();
        inputFile.seekg(ios::beg);
    }
    inputFile.close();

    return resultPart2;
}
