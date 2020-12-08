// Day1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

const int SAFE_GUARD = 10000;

int GetArgumentFromInstruction(string instruction)
{
    cmatch cm;
    regex e("[a-z]* ([+|-])([0-9]*)");
    regex_match(instruction.c_str(), cm, e);

    string sign = cm[1];
    int value = atoi(cm[2].str().c_str());

    if (sign == "-")
        value *= -1;

    return value;
}

int main()
{
    vector<string> instructions = vector<string>();

    string line;
    ifstream  myfile;

    myfile.open("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line.c_str() << endl;
            instructions.push_back(line.c_str());
        }
    }
    myfile.close();

    vector<int> visitedInstructionPointer = vector<int>();

    int accumulator = 0;
    int instructionPointer = 0;
    int nextJmpOrNopToChange = 0;

    int mainLoopIndex = 0;
    while (mainLoopIndex < SAFE_GUARD && instructionPointer < instructions.size())
    {
        nextJmpOrNopToChange++;

        vector<string> tempInstructions = vector<string>(instructions);

        // reset everything
        accumulator = 0;
        instructionPointer = 0;
        visitedInstructionPointer.clear();

        int jmpOrNopMet = 1;
        int loopIndex = 0;
        while (loopIndex < SAFE_GUARD && instructionPointer < tempInstructions.size() &&
            find(visitedInstructionPointer.begin(), visitedInstructionPointer.end(), instructionPointer) == visitedInstructionPointer.end())
        {
            visitedInstructionPointer.push_back(instructionPointer);

            cout << instructionPointer << " And size of vector " << tempInstructions.size() << endl;
            string currentInstruction = tempInstructions[instructionPointer];
            int number = GetArgumentFromInstruction(currentInstruction);

            cout << "Number is " << number << endl;

            cout << "Instruction is " << currentInstruction << " number is " << number << endl;

            if (currentInstruction.substr(0, 3) == "acc")
            {
                cout << "RESULT UPDATED " << accumulator << endl;
                accumulator += number;
                instructionPointer++;
            }
            else if (currentInstruction.substr(0, 3) == "jmp")
            {
                if (jmpOrNopMet == nextJmpOrNopToChange)
                {
                    cout << "CHANGE IT" << endl;
                    tempInstructions[instructionPointer].replace(0, 3, "nop");

                    // Do a nop here
                    instructionPointer++;
                }
                else
                {
                    instructionPointer += number;
                }
                jmpOrNopMet++;
            }
            else if (currentInstruction.substr(0, 3) == "nop")
            {
                if (jmpOrNopMet == nextJmpOrNopToChange)
                {
                    if (instructionPointer + number >= 0 && instructionPointer + number < instructions.size())
                    {
                        cout << "CHANGE IT" << endl;
                        tempInstructions[instructionPointer].replace(0, 3, "jmp");
                        // Do a jump here
                        instructionPointer += number;
                    }
                    else
                    {
                        nextJmpOrNopToChange++;
                    }
                }
                else
                {
                    instructionPointer++;
                }
                jmpOrNopMet++;
            }

            loopIndex++;
        }

        cout << "Main loop" << endl;

        mainLoopIndex++;
    }


    cout << "Result is : " << accumulator << endl;
}