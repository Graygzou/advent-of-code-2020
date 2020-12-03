// TobogganTrajectory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    const char* treeSymbol = "#";

    // slope

    int slopeX = 1;
    int slopeY = 2;

    int playerX = 0;

    int nbTreesMet = 0;

    int currentLine = 0;
    int nextLineNumber = slopeY;

    string line;
    ifstream  myfile;
    myfile.open("inputs.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (currentLine == nextLineNumber)
            {
                cout << line.length() << endl;

                playerX = (playerX + slopeX) % line.length();

                cout << line.c_str() << endl;
                cout << playerX << endl;
                cout << line[playerX] << endl;
                if (line[playerX] == *treeSymbol)
                {
                    nbTreesMet++;
                }
                nextLineNumber = currentLine + slopeY;
            }
            currentLine++;
        }
    }
    myfile.close();

    cout << currentLine << endl;

    cout << "Result for part 1 is : " << nbTreesMet << endl;
}