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

int main()
{
    ifstream file;
    string line;

    string startingNumbers("");

    bool gatherRules = true;
    bool myTicket = true;
    bool otherTickets = true;
    bool skipedHeader = false;

    vector<vector<pair<int, int>>> rules;
    vector<vector<bool>> possibilitiesPerSpot;

    vector<int> finalNumbers = vector<int>();

    vector<int> myTicketNumbers;

    file.open("input.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.empty())
            {
                skipedHeader = false;
                if (myTicket && gatherRules == false)
                {
                    myTicket = false;
                }

                if (gatherRules)
                {
                    gatherRules = false;
                }
            }
            else
            {
                if (gatherRules)
                {
                    cmatch cm;
                    regex e("(?:[^[:digit:]]*)([[:digit:]]*)-([[:digit:]]*)(?: or )([[:digit:]]*)-([[:digit:]]*)");
                    regex_match(line.c_str(), cm, e);

                    cout << "Rules one " << cm[1] << " - " << cm[2] << endl;
                    cout << "Rules two " << cm[3] << " - " << cm[4] << endl;

                    vector<pair<int, int>> newRules = vector<pair<int, int>>();

                    newRules.push_back(make_pair(atoi(cm[1].str().c_str()), atoi(cm[2].str().c_str())));
                    newRules.push_back(make_pair(atoi(cm[3].str().c_str()), atoi(cm[4].str().c_str())));
                    rules.push_back(newRules);
                }
                else if (myTicket)
                {
                    myTicketNumbers = SplitWithDelimiter(line, ",");
                }
                else if (otherTickets)
                {
                    if (skipedHeader)
                    {
                        string delimiter(",");
                        vector<int> numbers = SplitWithDelimiter(line, delimiter);

                        for (size_t i = 0; i < numbers.size(); i++)
                        {
                            cout << numbers[i] << ", ";
                        }
                        cout << endl;

                        for (size_t i = 0; i < numbers.size(); i++)
                        {
                            cout << numbers[i] << endl;
                            bool respectOneRule = false;
                            for (size_t j = 0; j < rules.size(); j++)
                            {
                                bool isLegit = false;
                                for (size_t k = 0; k < rules[j].size(); k++)
                                {
                                    if (numbers[i] >= rules[j][k].first && numbers[i] <= rules[j][k].second)
                                    {
                                        isLegit = true;
                                        respectOneRule = true;
                                    }
                                }

                                if (!isLegit && respectOneRule)
                                {
                                    cout << numbers[i] << " is not legit for the rule " << (j + 1) << endl;
                                    possibilitiesPerSpot[i][j] = false;
                                }
                            }

                            if (!respectOneRule)
                            {
                                //cout << "Add number " << numbers[i] << "to result " << endl;
                                finalNumbers.push_back(numbers[i]);
                            }
                        }
                    }
                    else
                    {
                        // We already know all the rules so create the finding structure
                        int rulesSize = rules.size();
                        for (size_t i = 0; i < rulesSize; i++)
                        {
                            possibilitiesPerSpot.push_back(vector<bool>(rulesSize, true));
                        }

                        skipedHeader = true;
                    }
                }
            }
        }
    }

    // Visualization
    for (size_t i = 0; i < possibilitiesPerSpot.size(); i++)
    {
        cout << "ticket  | ";
        for (size_t j = 0; j < possibilitiesPerSpot[i].size(); j++)
        {
            cout << possibilitiesPerSpot[i][j] << " | ";
        }
        cout << endl;
    }
    cout << endl;

    // Part 2
    // ticket => rule index
    //map<int, int> rulesRespectedPerTicket;
    map<int, int> finalRules = map<int, int>();
    int i = 0;
    while (finalRules.size() < possibilitiesPerSpot.size())
    {
        int sum = 0;
        int lastPositiveIndex = 0;
        for (size_t j = 0; j < possibilitiesPerSpot.size(); j++)
        {
            sum += possibilitiesPerSpot[j][i];
            
            if (possibilitiesPerSpot[j][i])
            {
                lastPositiveIndex = j;
            }
            //if (possibilitiesPerSpot[j][i])
            //{
            //    //rulesRespectedPerTicket.insert(j, i);
            //}
        }

        cout << "SUM " << sum << " with last index " << lastPositiveIndex << endl;

        if (sum == 1)
        { 
            finalRules.insert( pair<int,int>(i, lastPositiveIndex));

            // Update all other tickets with false
            for (size_t k = 0; k < possibilitiesPerSpot.size(); k++)
            {
                possibilitiesPerSpot[lastPositiveIndex][k] = false;
            }
        }

        // Visualization
        for (size_t i = 0; i < possibilitiesPerSpot.size(); i++)
        {
            cout << "ticket  | ";
            for (size_t j = 0; j < possibilitiesPerSpot[i].size(); j++)
            {
                cout << possibilitiesPerSpot[i][j] << " | ";
            }
            cout << endl;
        }
        cout << endl;


        i++;
        i %= possibilitiesPerSpot.size();
    }

    // Part 2
    for (std::map<int, int>::iterator it = finalRules.begin(); it != finalRules.end(); ++it)
        std::cout << "field " << it->first << " => " << "rule " << it->second << '\n';

    // Part 1
    int sum = 0;
    for (size_t i = 0; i < finalNumbers.size(); i++)
    {
        sum += finalNumbers[i];
    }

    cout << "Result pat 1 is " << sum << endl;
}