// Day16-TicketTranslation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    ifstream file;
    string line;

    string startingNumbers("");

    bool gatherRules = true;
    bool myTicket = true;
    bool otherTickets = true;

    file.open("input.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.empty())
            {
                if (gatherRules)
                {
                    gatherRules = false;
                }

                if (myTicket && gatherRules == false)
                {
                    myTicket = false;
                }
            }

            if (gatherRules)
            {
                // TODO
            }
            else if (myTicket)
            {
                // TODO later
            }
            else if(otherTickets)
            {
                    // TODO
            }

            startingNumbers = line;
        }
    }


}