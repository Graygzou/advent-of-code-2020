// Day1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

const int SAFE_GUARD = 10000;

#pragma region Helpers
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

vector<string> ConstructInstructionsFromFile(string fileName)
{
    vector<string> instructions = vector<string>();

    string line;
    ifstream  myfile;

    myfile.open(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            instructions.push_back(line.c_str());
        }
    }
    myfile.close();

    return instructions;
}
#pragma endregion

bool RunBootCode(vector<string> instructions, int* result, bool swapWhenIndexMet = false, int swapIndex = -1)
{
    vector<int> visitedInstructionPointer = vector<int>();

    int accumulator = 0;
    int instructionPointer = 0;
    int nbJmpAndNopMet = 0;

    bool isLooping = true;
    bool isInstructorPointeurInBounds = true;
    int loopIndex = 0;
    do
    {
        visitedInstructionPointer.push_back(instructionPointer);

        string currentInstruction = instructions[instructionPointer];
        int number = GetArgumentFromInstruction(currentInstruction);

        if (swapWhenIndexMet)
        {
            if ((currentInstruction.substr(0, 3) == "jmp" || currentInstruction.substr(0, 3) == "nop") 
                && (nbJmpAndNopMet + 1) == swapIndex)
            {
                string newInstruction = currentInstruction.substr(0, 3) == "nop" ? "jmp" : "nop";
                instructions[instructionPointer].replace(0, 3, newInstruction);
                currentInstruction = instructions[instructionPointer];
            }
        }

        if (currentInstruction.substr(0, 3) == "acc")
        {
            accumulator += number;
            instructionPointer++;
        }
        else if (currentInstruction.substr(0, 3) == "jmp")
        {
            instructionPointer += number;
            nbJmpAndNopMet++;
        }
        else if (currentInstruction.substr(0, 3) == "nop")
        {
            instructionPointer++;
            nbJmpAndNopMet++;
        }

        loopIndex++;
        isInstructorPointeurInBounds = instructionPointer >= 0 && instructionPointer < instructions.size();
        isLooping = find(visitedInstructionPointer.begin(), visitedInstructionPointer.end(), instructionPointer) != visitedInstructionPointer.end();
    } while (loopIndex < SAFE_GUARD && isInstructorPointeurInBounds && !isLooping);

    *result = accumulator;

    return instructionPointer >= instructions.size();
}

int main()
{
    cout << "Day 8 - Handheld Halting" << endl;

    vector<string> instructions = ConstructInstructionsFromFile("input.txt");

    // Part 1
    cout << "Start Part 1 ..." << endl;
    int resultPart1 = 0;
    RunBootCode(instructions, &resultPart1);
    cout << "Result for part 1 is : " << resultPart1 << endl;

    // Part 2
    cout << "Start Part 2 ..." << endl;
    int resultPart2 = 0;
    int nextJmpOrNopToChange = 0;
    bool hasProgramFinished = false;
    while (nextJmpOrNopToChange < SAFE_GUARD && !hasProgramFinished)
    {
        nextJmpOrNopToChange++;
        vector<string> tempInstructions = vector<string>(instructions);
        hasProgramFinished = RunBootCode(tempInstructions, &resultPart2, true, nextJmpOrNopToChange);
    }
    cout << "Result for part 2 is : " << resultPart2 << endl;
}