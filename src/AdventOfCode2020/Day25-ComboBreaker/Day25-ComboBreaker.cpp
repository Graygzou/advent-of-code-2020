// Day25-ComboBreaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

void Part1(int subjectNumber, unsigned long long* finalNumber, unsigned long long *currentLoop, int targetKey = 0, unsigned long long targetLoopSize = 100000000000000)
{
    int startingNumber = 1;
    int dividingNumber = 20201227;

    unsigned long long temp = startingNumber;

    *currentLoop = 0;
    //cout << "targetLoopSize " << targetLoopSize << endl;
    while (*currentLoop < targetLoopSize && temp != targetKey)
    {
        temp *= subjectNumber;
        temp %= dividingNumber;

        //cout << "temp " << temp << endl;
        (*currentLoop)++;
    }

    cout << "Loop size reached: " << *currentLoop << endl;

    *finalNumber = temp;
}

//int RunIterationForGivenLoop(int cardPublicKey, int subjectNumber)
//{
//    int startingNumber = 1;
//    int dividingNumber = 20201227;
//
//    unsigned long long temp = startingNumber;
//
//    int currentLoop = 0;
//    int nbLoopMax = 10000000;
//    while (currentLoop < nbLoopMax && temp != 14897079)
//    {
//        temp *= cardPublicKey;
//        temp %= dividingNumber;
//
//        currentLoop++;
//    }
//
//    cout << "currentLoop " << currentLoop << endl;
//    cout << "temp " << temp << endl;
//
//    if (currentLoop == nbLoopMax)
//    {
//        cout << "Max Loop Reached ! Exit." << endl;
//    }
//
//    return temp;
//}

void Tests()
{
    int cardPublicKey = 5764801;
    int doorPublicKey = 17807724;

    // Step 1
    unsigned long long finalNumber = 0;
    unsigned long long finalLoop = 0;
    Part1(7, &finalNumber, &finalLoop, cardPublicKey);

    // Step 2
    unsigned long long finalNumber2 = 0;
    unsigned long long finalLoop2 = 0;
    Part1(doorPublicKey, &finalNumber2, &finalLoop2, 0, finalLoop);

    cout << "FINAL = " << finalNumber2 << endl;

    //Part1(17807724, &finalLoop2, &finalNumber2, 0, finalLoop);
    //cout << Part1(17807724, 0, Part1(7, 17807724)) << endl;
}

int main()
{
    std::cout << "Combo Breaker" << endl;

    //Tests();

    int cardPublicKey = 6930903;
    int doorPublicKey = 19716708;

    // Step 1
    unsigned long long finalNumber = 0;
    unsigned long long finalLoop = 0;
    Part1(7, &finalNumber, &finalLoop, cardPublicKey);

    // Step 2
    unsigned long long finalNumber2 = 0;
    unsigned long long finalLoop2 = 0;
    Part1(doorPublicKey, &finalNumber2, &finalLoop2, 0, finalLoop);

    cout << "FINAL = " << finalNumber2 << endl;
    
    //Part1(cardPublicKey, subjectNumber);
}