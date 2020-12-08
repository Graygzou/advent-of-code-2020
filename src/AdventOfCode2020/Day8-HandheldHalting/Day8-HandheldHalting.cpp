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
            cout << line.c_str() << endl;
            instructions.push_back(line.c_str());
        }
    }
    myfile.close();

    return instructions;
}

bool Part1(vector<string> instructions, int* result, bool swapWhenIndexMet = false, int swapIndex = -1)
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

        //cout << instructionPointer << " And size of vector " << instructions.size() << endl;
        string currentInstruction = instructions[instructionPointer];
        int number = GetArgumentFromInstruction(currentInstruction);

        if (swapWhenIndexMet && nbJmpAndNopMet == swapIndex)
        {
            string newInstruction = currentInstruction.substr(0, 3) == "nop" ? "jmp" : "nop";
            instructions[instructionPointer].replace(0, 3, newInstruction);
        }
        //cout << "Instruction is " << currentInstruction << " number is " << number << endl;

        if (currentInstruction.substr(0, 3) == "acc")
        {
            accumulator += number;
            instructionPointer++;
        }
        else if (currentInstruction.substr(0, 3) == "jmp")
        {
            instructionPointer += number;
        }
        else if (currentInstruction.substr(0, 3) == "nop")
        {
            instructionPointer++;
        }

        loopIndex++;
        isInstructorPointeurInBounds = instructionPointer >= 0 && instructionPointer < instructions.size();
        isLooping = find(visitedInstructionPointer.begin(), visitedInstructionPointer.end(), instructionPointer) != visitedInstructionPointer.end();
    } while (loopIndex < SAFE_GUARD && isInstructorPointeurInBounds && !isLooping);

    *result = accumulator;

    return instructionPointer >= instructions.size();
}

int Part2(vector<string> instructions)
{
    //vector<int> visitedInstructionPointer = vector<int>();

    int accumulator = 0;
    //int instructionPointer = 0;
    int nextJmpOrNopToChange = 0;

    bool hasProgramFinished = false;
    int mainLoopIndex = 0;
    while (mainLoopIndex < SAFE_GUARD && !hasProgramFinished)
    {
        nextJmpOrNopToChange++;

        vector<string> tempInstructions = vector<string>(instructions);

        // reset everything
        //accumulator = 0;
        //instructionPointer = 0;
        //visitedInstructionPointer.clear();

        //int jmpOrNopMet = 1;
        //int loopIndex = 0;

        hasProgramFinished = Part1(tempInstructions, &accumulator, true, nextJmpOrNopToChange);

        //while (loopIndex < SAFE_GUARD && instructionPointer < tempInstructions.size() &&
        //    find(visitedInstructionPointer.begin(), visitedInstructionPointer.end(), instructionPointer) == visitedInstructionPointer.end())
        //{
        //    visitedInstructionPointer.push_back(instructionPointer);

        //    cout << instructionPointer << " And size of vector " << tempInstructions.size() << endl;
        //    string currentInstruction = tempInstructions[instructionPointer];
        //    int number = GetArgumentFromInstruction(currentInstruction);

        //    cout << "Number is " << number << endl;

        //    cout << "Instruction is " << currentInstruction << " number is " << number << endl;

        //    if (currentInstruction.substr(0, 3) == "acc")
        //    {
        //        cout << "RESULT UPDATED " << accumulator << endl;
        //        accumulator += number;
        //        instructionPointer++;
        //    }
        //    else if (currentInstruction.substr(0, 3) == "jmp")
        //    {
        //        if (jmpOrNopMet == nextJmpOrNopToChange)
        //        {
        //            cout << "CHANGE IT" << endl;
        //            tempInstructions[instructionPointer].replace(0, 3, "nop");

        //            // Do a nop here
        //            instructionPointer++;
        //        }
        //        else
        //        {
        //            instructionPointer += number;
        //        }
        //        jmpOrNopMet++;
        //    }
        //    else if (currentInstruction.substr(0, 3) == "nop")
        //    {
        //        if (jmpOrNopMet == nextJmpOrNopToChange)
        //        {
        //            if (instructionPointer + number >= 0 && instructionPointer + number < instructions.size())
        //            {
        //                cout << "CHANGE IT" << endl;
        //                tempInstructions[instructionPointer].replace(0, 3, "jmp");
        //                // Do a jump here
        //                instructionPointer += number;
        //            }
        //            else
        //            {
        //                nextJmpOrNopToChange++;
        //            }
        //        }
        //        else
        //        {
        //            instructionPointer++;
        //        }
        //        jmpOrNopMet++;
        //    }

        //    loopIndex++;
        //}

        //cout << "Main loop" << endl;

        mainLoopIndex++;
    }

    return accumulator;
}

int main()
{
    vector<string> instructions = ConstructInstructionsFromFile("input.txt");

    int resultPart1 = 0;
    Part1(instructions, &resultPart1);

    //int resultPart2 = Part2(instructions);

    cout << "Result for part 1 is : " << resultPart1 << endl;
    //cout << "Result for part 2 is : " << resultPart2 << endl;
}