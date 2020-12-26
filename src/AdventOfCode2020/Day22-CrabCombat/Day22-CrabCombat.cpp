// Day22-CrabCombat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

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

string GetConfigurationFootprint(queue<int> player1Cards, queue<int> player2Cards)
{
    string result("");
    while (!player1Cards.empty())
    {
        result += to_string(player1Cards.front()) + ",";
        player1Cards.pop();
    }
    result += "/";
    while (!player2Cards.empty())
    {
        result += to_string(player2Cards.front()) + ",";
        player2Cards.pop();
    }

    //cout << result << endl;

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

void Part1(string fileName)
{
    ifstream file;
    string line;

    queue<int> player1deck;
    queue<int> player2deck;

    int factor = 0;
    file.open(fileName);
    if (file.is_open())
    {
        while (getline(file, line) && !line.empty())
        {
            if (line.size() > 0 && line.size() < 5)
            {
                player1deck.push(atoi(line.c_str()));
                factor++;
            }
        }

        while (getline(file, line) && !line.empty())
        {
            if (line.size() > 0 && line.size() < 5)
            {
                player2deck.push(atoi(line.c_str()));
                factor++;
            }
        }
    }

    vector<string> currentConfigurationFootprint;
    queue<vector<string>> configurationFootprintsMet;

    queue<queue<int>> savedConfigurationsPla1;
    queue<queue<int>> savedConfigurationsPla2;
    queue<int> player1Cards;
    queue<int> player2Cards;

    bool player1WinRound = false;
    bool currentGameDone = false;
    bool newGameStarted = false;
    int index = 1;
    int gameIndex = 1;
    while (!currentGameDone || !savedConfigurationsPla1.empty())
    {
        player1WinRound = true;

        int player1Card = 0;
        int player2Card = 0;

        cout << "Round " << index << " Game (" << gameIndex << ")" << endl;
        cout << "Player 1's deck: " << DisplayDeck(player1deck) << endl;
        cout << "Player 2's deck: " << DisplayDeck(player2deck) << endl;

        string currentFootprint = GetConfigurationFootprint(player1deck, player2deck);

        if (find(currentConfigurationFootprint.begin(), currentConfigurationFootprint.end(), currentFootprint) != currentConfigurationFootprint.end())
        {
            // game instantly ends in a win for player 1
            player1WinRound = true;
            cout << "STOP THE GAME !" << endl;
            break;
        }
        else
        {
            currentConfigurationFootprint.push_back(currentFootprint);
        }

        if (currentGameDone)
        {
            player1WinRound = !player1deck.empty();

            player1deck = savedConfigurationsPla1.front();
            savedConfigurationsPla1.pop();
            player2deck = savedConfigurationsPla2.front();
            savedConfigurationsPla2.pop();

            player1Card = player1Cards.front();
            player1Cards.pop();
            player2Card = player2Cards.front();
            player2Cards.pop();

            // Setup back footprints
            currentConfigurationFootprint = configurationFootprintsMet.front();
            configurationFootprintsMet.pop();

            gameIndex--;
            index = 1;
        }
        else
        {
            player1Card = player1deck.front();
            player2Card = player2deck.front();

            player1deck.pop();
            player2deck.pop();

            if (player1Card <= player1deck.size() && player2Card <= player2deck.size())
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

                configurationFootprintsMet.push(currentConfigurationFootprint);
                currentConfigurationFootprint = vector<string>();

                newGameStarted = true;
            }
            else
            {
                // Regular rounds
                player1WinRound = player1Card > player2Card;
            }
        }

        cout << "Player 1 plays: " << player1Card << endl;
        cout << "Player 2's deck: " << player2Card << endl;

        if (!newGameStarted)
        {
            if (player1WinRound)
            {
                player1deck.push(player1Card);
                player1deck.push(player2Card);
            }
            else
            {
                player2deck.push(player2Card);
                player2deck.push(player1Card);
            }
        }
        else
        {
            newGameStarted = false;
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
        int faqctor = player2deck.size();
        while (!player2deck.empty())
        {
            result += factor * player2deck.front();
            player2deck.pop();
            factor--;
        }
    }

    cout << "Part 1 result is " << result << endl;
}

int main()
{
    std::cout << "Crab Combat" << endl;
    Part1("example.txt");
}