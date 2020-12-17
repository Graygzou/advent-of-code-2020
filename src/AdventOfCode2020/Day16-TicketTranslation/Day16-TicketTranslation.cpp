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
            cout << "ici" << atoi(str.substr(0, nextDelimiterIndex).c_str()) << endl;
            results.push_back(atoi(str.substr(0, nextDelimiterIndex).c_str()));
        }
        else
        {
            cout << "la" << atoi(str.c_str()) << endl;
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
                    // TODO later
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

                        for (size_t i = 0; i < numbers.size(); i++)
                        {
                            cout << numbers[i] << endl;
                            bool isLegit = false;
                            for (size_t j = 0; !isLegit && j < rules.size(); j++)
                            {
                                for (size_t k = 0; !isLegit && k < rules[j].size(); k++)
                                {
                                    if (numbers[i] >= rules[j][k].first && numbers[i] <= rules[j][k].second)
                                    {
                                        isLegit = true;
                                    }
                                }
                            }

                            if (!isLegit)
                            {
                                //cout << "Add number " << numbers[i] << "to result " << endl;
                                finalNumbers.push_back(numbers[i]);
                            }
                            else
                            {
                                
                            }
                        }
                    }
                    else
                    {
                        // We already know all the rules so create the finding structure
                        for (size_t i = 0; i < rules.size(); i++)
                        {
                            possibilitiesPerSpot.push_back(vector<bool>(rules.size(), true));
                        }

                        skipedHeader = true;
                    }
                }
            }
        }
    }

    int sum = 0;
    for (size_t i = 0; i < finalNumbers.size(); i++)
    {
        sum += finalNumbers[i];
    }

    cout << "Result is " << sum << endl;
}