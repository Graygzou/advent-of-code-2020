// Day1.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

const int SAFE_GUARD = 10000;

vector<string> ConstructInstructionsFromFile(string fileName);
bool RunBootCode(vector<string> instructions, int* result, bool swapWhenIndexMet = false, int swapIndex = -1);

int main(int argc, char** argv)
{
    cout << "Day 8 - Handheld Halting" << endl;

    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }

    vector<string> instructions = ConstructInstructionsFromFile(fileName);

    // Part 1
    int resultPart1 = 0;
    cout << "Start Part 1 ..." << endl;
    RunBootCode(instructions, &resultPart1);
    cout << "Result for part 1 is : " << resultPart1 << endl;

    // Part 2
    int resultPart2 = 0;
    int nextJmpOrNopToChange = 0;
    bool hasProgramFinished = false;
    cout << "Start Part 2 ..." << endl;
    while (nextJmpOrNopToChange < SAFE_GUARD && !hasProgramFinished)
    {
        nextJmpOrNopToChange++;
        vector<string> tempInstructions = vector<string>(instructions);
        hasProgramFinished = RunBootCode(tempInstructions, &resultPart2, true, nextJmpOrNopToChange);
    }
    cout << "Result for part 2 is : " << resultPart2 << endl;
}

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
    if (!myfile.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    while (getline(myfile, line))
    {
        instructions.push_back(line.c_str());
    }
    myfile.close();

    return instructions;
}
#pragma endregion

/// <summary>
/// Run list instructions contains in the vector until we meet twice the same instruction. 
/// 
/// Can also swap a nop +0 to jmp +0 if the parameters are provided to do so. This will allows to reach the end of the program
/// </summary>
/// <returns>true if the programs finished, false otherwise</returns>
bool RunBootCode(vector<string> instructions, int* result, bool swapWhenIndexMet, int swapIndex)
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