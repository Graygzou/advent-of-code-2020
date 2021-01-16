// Day25-ComboBreaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

const int STARTING_NUMBER = 1;
const int DIVINDING_NUMBER = 20201227;

void Part1(int subjectNumber, unsigned long long* finalNumber, unsigned long long* currentLoop, int targetKey = 0, unsigned long long targetLoopSize = 100000000000000);

int main()
{
    std::cout << "Day 25 - Combo Breaker" << endl;

    int cardPublicKey = 6930903;
    int doorPublicKey = 19716708;

    // Step 1
    unsigned long long finalNumber = 0;
    unsigned long long finalLoop = 0;
    Part1(7, &finalNumber, &finalLoop, cardPublicKey);

    // Step 2
    unsigned long long resultPart1 = 0;
    unsigned long long finalLoop2 = 0;
    Part1(doorPublicKey, &resultPart1, &finalLoop2, 0, finalLoop);

    cout << "Result for part 1 = " << resultPart1 << endl;
}

void Part1(int subjectNumber, unsigned long long* finalNumber, unsigned long long *currentLoop, int targetKey, unsigned long long targetLoopSize)
{
    int startingNumber = STARTING_NUMBER;
    int dividingNumber = DIVINDING_NUMBER;

    unsigned long long temp = startingNumber;

    *currentLoop = 0;
    while (*currentLoop < targetLoopSize && temp != targetKey)
    {
        temp *= subjectNumber;
        temp %= dividingNumber;

        (*currentLoop)++;
    }

    *finalNumber = temp;
}