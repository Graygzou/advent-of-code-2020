// Day22-CrabCombat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

int PlayCombatGame(string fileName, bool allowRecursion);

int main(int argc, char** argv)
{
    std::cout << "Crab Combat" << endl;

    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }

    int resultPart1 = PlayCombatGame(fileName, false);
    std::cout << "Part 1 result is " << resultPart1 << endl;

    int resultPart2 = PlayCombatGame(fileName, true);
    std::cout << "Part 2 result is " << resultPart2 << endl;
}

queue<int> CreateNewQueueFrom(queue<int> deck, int size)
{
    queue<int> result;
    int index = 0;
    while (!deck.empty() && index < size)
    {
        result.push(deck.front());
        deck.pop();

        index++;
    }

    return result;
}

string GetConfigurationFootprint(queue<int> player1Cards)
{
    string result("");
    while (!player1Cards.empty())
    {
        result += to_string(player1Cards.front()) + ",";
        player1Cards.pop();
    }
    return result;
}

string DisplayDeck(queue<int> deck)
{
    string result("");
    while (!deck.empty())
    {
        result += to_string(deck.front()) + ",";
        deck.pop();
    }

    return result;
}

int PlayCombatGame(string fileName, bool allowRecursion)
{
    ifstream file;
    string line;

    queue<int> player1deck;
    queue<int> player2deck;

    file.open(fileName);
    if (!file.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    while (getline(file, line) && !line.empty())
    {
        if (line.size() > 0 && line.size() < 5)
        {
            player1deck.push(atoi(line.c_str()));
        }
    }

    while (getline(file, line) && !line.empty())
    {
        if (line.size() > 0 && line.size() < 5)
        {
            player2deck.push(atoi(line.c_str()));
        }
    }

    // avoid recursions
    vector<string> currentConfigurationFootprintPla1;
    vector<string> currentConfigurationFootprintPla2;
    stack<vector<string>> configurationFootprintsMetPla1;
    stack<vector<string>> configurationFootprintsMetPla2;
    // decks stack
    stack<queue<int>> savedConfigurationsPla1;
    stack<queue<int>> savedConfigurationsPla2;
    // played cards stack
    stack<int> player1Cards;
    stack<int> player2Cards;

    bool player1WinRound = false;
    bool player2WinRound = false;

    bool currentGameDone = false;

    int index = 1;
    int gameIndex = 1;
    while (!currentGameDone || !savedConfigurationsPla1.empty())
    {
        player1WinRound = false;
        player2WinRound = false;

        int player1Card = 0;
        int player2Card = 0;

        string currentFootprintPla1 = GetConfigurationFootprint(player1deck);
        string currentFootprintPla2 = GetConfigurationFootprint(player2deck);

        if (find(currentConfigurationFootprintPla1.begin(), currentConfigurationFootprintPla1.end(), currentFootprintPla1) != currentConfigurationFootprintPla1.end()
            || find(currentConfigurationFootprintPla2.begin(), currentConfigurationFootprintPla2.end(), currentFootprintPla2) != currentConfigurationFootprintPla2.end())
        {
            // game instantly ends in a win for player 1
            player1WinRound = true;
            player2deck = queue<int>();
            currentGameDone = true;
        }
        else
        {
            currentConfigurationFootprintPla1.push_back(currentFootprintPla1);
            currentConfigurationFootprintPla2.push_back(currentFootprintPla2);
        }

        if (currentGameDone)
        {
            if (gameIndex > 1)
            {
                player1WinRound = !player1deck.empty();
                player2WinRound = !player2deck.empty();

                player1deck = savedConfigurationsPla1.top();
                player2deck = savedConfigurationsPla2.top();

                savedConfigurationsPla1.pop();
                savedConfigurationsPla2.pop();

                player1Card = player1Cards.top();
                player1Cards.pop();
                player2Card = player2Cards.top();
                player2Cards.pop();

                // Setup back footprints
                currentConfigurationFootprintPla1 = configurationFootprintsMetPla1.top();
                configurationFootprintsMetPla1.pop();
                currentConfigurationFootprintPla2 = configurationFootprintsMetPla2.top();
                configurationFootprintsMetPla2.pop();

                gameIndex--;
                index = 1;
            }
        }
        else
        {
            // pick cards
            player1Card = player1deck.front();
            player1deck.pop();
            player2Card = player2deck.front();
            player2deck.pop();

            // Check if we can recurse
            if (allowRecursion && player1Card <= player1deck.size() && player2Card <= player2deck.size())
            {
                // Recursive start
                gameIndex++;
                index = 1;
                savedConfigurationsPla1.push(player1deck);
                savedConfigurationsPla2.push(player2deck);
                player1Cards.push(player1Card);
                player2Cards.push(player2Card);

                // Resize deck to fit the player cards
                player1deck = CreateNewQueueFrom(player1deck, player1Card);
                player2deck = CreateNewQueueFrom(player2deck, player2Card);

                configurationFootprintsMetPla1.push(currentConfigurationFootprintPla1);
                configurationFootprintsMetPla2.push(currentConfigurationFootprintPla2);
                currentConfigurationFootprintPla1 = vector<string>();
                currentConfigurationFootprintPla2 = vector<string>();
            }
            else
            {
                // Regular rounds
                player1WinRound = player1Card > player2Card;
                player2WinRound = !player1WinRound;
            }
        }

        if (player1WinRound)
        {
            player1deck.push(player1Card);
            player1deck.push(player2Card);
        }
        else if (player2WinRound)
        {
            player2deck.push(player2Card);
            player2deck.push(player1Card);
        }

        currentGameDone = player1deck.empty() || player2deck.empty();
        index++;
    }

    int result = 0;
    if (player1WinRound)
    {
        int factor = player1deck.size();
        while (!player1deck.empty())
        {
            result += factor * player1deck.front();
            player1deck.pop();
            factor--;
        }
    }
    else
    {
        int factor = player2deck.size();
        while (!player2deck.empty())
        {
            result += factor * player2deck.front();
            player2deck.pop();
            factor--;
        }
    }

    return result;
}