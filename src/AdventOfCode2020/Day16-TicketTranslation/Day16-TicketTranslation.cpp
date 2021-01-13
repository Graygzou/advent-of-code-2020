// Day16-TicketTranslation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

vector<int> SplitWithDelimiter(string str, string delimiter)
{
    vector<int> results = vector<int>();
    int startingIndex(0);
    bool done = false;
    while (str.size() > 0 && !done)
    {
        int nextDelimiterIndex = str.find(delimiter);
        if (nextDelimiterIndex != string::npos)
        {
            results.push_back(atoi(str.substr(0, nextDelimiterIndex).c_str()));
        }
        else
        {
            results.push_back(atoi(str.c_str()));
            done = true;
        }
        // Update everything
        str = str.substr(nextDelimiterIndex + 1, str.size() - 1);
    }
    return results;
}

void Display(vector<vector<bool>> possibilitiesPerSpot)
{
    for (size_t i = 0; i < possibilitiesPerSpot.size(); i++)
    {
        for (size_t j = 0; j < possibilitiesPerSpot[i].size(); j++)
        {
            cout << possibilitiesPerSpot[i][j] << " | ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<pair<int, int>>> GatherRules(ifstream *file)
{
    vector<vector<pair<int, int>>> rules;

    string line;
    while (getline(*file, line) && !line.empty())
    {
        cmatch cm;
        regex e("(?:[^[:digit:]]*)([[:digit:]]*)-([[:digit:]]*)(?: or )([[:digit:]]*)-([[:digit:]]*)");
        regex_match(line.c_str(), cm, e);

        vector<pair<int, int>> newRules = vector<pair<int, int>>();

        newRules.push_back(make_pair(atoi(cm[1].str().c_str()), atoi(cm[2].str().c_str())));
        newRules.push_back(make_pair(atoi(cm[3].str().c_str()), atoi(cm[4].str().c_str())));
        rules.push_back(newRules);
    }

    return rules;
}

vector<int> GetPersonalTicketInfos(ifstream* file)
{
    string line;
    // Skip the header
    getline(*file, line);

    // Retrieve the ticket
    getline(*file, line);
    return SplitWithDelimiter(line, ",");
}

vector<vector<int>> GatherAllOtherTickets(ifstream* file)
{
    vector<vector<int>> otherTickets;

    string line;

    // Skip the whitespace and the header
    getline(*file, line);
    getline(*file, line);

    // Gather them all
    while (getline(*file, line) && !line.empty())
    {
        string delimiter(",");
        vector<int> currentTicket = SplitWithDelimiter(line, delimiter);

        otherTickets.push_back(currentTicket);
    }

    return otherTickets;
}

bool IsRuleRespected(vector<pair<int, int>> rule, int value)
{
    bool currentRuleRespected = false;

    // Iterate over all the conditions
    for (size_t j = 0; j < rule.size() && !currentRuleRespected; j++)
    {
        currentRuleRespected |= (value >= rule[j].first && value <= rule[j].second);
    }

    return currentRuleRespected;
}

vector<bool> GetNonRespectedRules(size_t* nonRespectedRulesCount, int currentNumber, vector<vector<pair<int, int>>> rules)
{ 
    vector<bool> respectedRules(rules.size(), true);
    for (size_t i = 0; i < rules.size(); i++)
    {
        if (!IsRuleRespected(rules[i], currentNumber))
        {
            respectedRules[i] = false;
            (*nonRespectedRulesCount)++;
        }
    }

    return respectedRules;
}

vector<vector<bool>> FindPossibilitiesWithOtherTickets(vector<vector<pair<int, int>>> rules, vector<vector<int>> tickets, vector<int> *errors)
{
    vector<vector<bool>> possibilitiesPerSpot;

    // We already know all how many rules we have so create the finding structure
    int rulesSize = rules.size();
    for (size_t j = 0; j < rulesSize; j++)
    {
        possibilitiesPerSpot.push_back(vector<bool>(rulesSize, true));
    }

    for (size_t i = 0; i < tickets.size(); i++)
    {
        for (size_t j = 0; j < tickets[i].size(); j++)
        {
            int currentNumber = tickets[i][j];

            size_t* nonRespectedRulesCount = new size_t(0);
            vector<bool> respectedRules = GetNonRespectedRules(nonRespectedRulesCount, currentNumber, rules);

            if (*nonRespectedRulesCount == rules.size())
            {
                // Part 1.
                (*errors).push_back(currentNumber);
            }
            else
            {
                // Update the final structure for part 2
                for (size_t ind = 0; ind < respectedRules.size(); ind++)
                {
                    if (!respectedRules[ind])
                    {
                        possibilitiesPerSpot[j][ind] = false;
                    }
                }
            }
        }
    }

    return possibilitiesPerSpot;
}

map<int, int> MapPossibilitiesLeft(vector<vector<bool>> possibilitiesPerSpot)
{
    map<int, int> finalRules = map<int, int>();

    int i = 0;
    while (finalRules.size() < possibilitiesPerSpot.size())
    {
        int nbPossibilitiesLeft = 0;
        int lastPositiveIndex = 0;
        for (size_t j = 0; j < possibilitiesPerSpot.size(); j++)
        {
            nbPossibilitiesLeft += possibilitiesPerSpot[j][i];

            if (possibilitiesPerSpot[j][i])
            {
                lastPositiveIndex = j;
            }
        }

        if (nbPossibilitiesLeft == 1)
        {
            finalRules.insert(pair<int, int>(i, lastPositiveIndex));

            // Update all other tickets with false
            for (size_t k = 0; k < possibilitiesPerSpot.size(); k++)
            {
                possibilitiesPerSpot[lastPositiveIndex][k] = false;
            }
        }

        i = (i + 1) % possibilitiesPerSpot.size();
    }

    return finalRules;
}

int main()
{
    cout << "Day 16 - Ticket Translation" << endl;

    ifstream file;

    file.open("input.txt");
    if (!file.is_open())
    {
        return 0;
    }

    vector<vector<pair<int, int>>> rules = GatherRules(&file);
    vector<int> myTicketNumbers = GetPersonalTicketInfos(&file);
    vector<vector<int>> gatherAllOtherTickets = GatherAllOtherTickets(&file);

    vector<int> errors = vector<int>();
    vector<vector<bool>> possibilitiesPerSpot = FindPossibilitiesWithOtherTickets(rules, gatherAllOtherTickets, &errors);

    // Part 1
    int resultPart1 = 0;
    for (size_t i = 0; i < errors.size(); i++)
    {
        resultPart1 += errors[i];
    }
    cout << "Result part 1 is " << resultPart1 << endl;

    // Part 2
    // rule => ticket index
    map<int, int> finalRules = MapPossibilitiesLeft(possibilitiesPerSpot);

    unsigned long long resultPart2 = 1;
    for (std::map<int, int>::iterator it = finalRules.begin(); it != finalRules.end(); ++it)
    {
        // Luckily, The first 6 rules are the one with the word "departure"
        if (it->first < 6)
        {
            resultPart2 *= myTicketNumbers[it->second];
        }
    }
    cout << "Result part 2 is " << resultPart2 << endl;
}