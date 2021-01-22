// Day19-MonsterMessages.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>

using namespace std;

int CountMessageMatchingRuleZero(string fileName);

/// <summary>
/// WARNING: For this solution you need to edit your input.
/// 
/// Basically, adding regexp pattern directy or pattern to be able to add some later on.
/// Take a look at inputModified.txt and the two line specified in the problem statement to know the modification needed.
/// </summary>
int main()
{
    cout << "Day 19 - Monster Messages" << endl;

    int result = CountMessageMatchingRuleZero("input.txt");
    std::cout << "Result for part 1 is " << result << std::endl;

    result = CountMessageMatchingRuleZero("inputModified.txt");
    std::cout << "Result for part 2 is " << result << std::endl;
}

string SanitizeRule(string rule)
{
    string ruleSanitized("");
    for (size_t i = 0; i < rule.size(); i++)
    {
        if (rule[i] != '\"')
        {
            ruleSanitized += rule[i];
        }
    }

    return ruleSanitized;
}

map<int, vector<string>> ExtractRuleFromFile(ifstream* file)
{
    map<int, vector<string>> inputRules;

    string line;
    while (getline(*file, line) && !line.empty())
    {
        int index = line.find(":");
        int key = atoi(line.substr(0, index).c_str());

        string allRules = line.substr(index + 2);
        vector<string> subRules;
        bool done = false;
        do
        {
            int spaceIndex = allRules.find(" ");

            if (spaceIndex != string::npos)
            {
                subRules.push_back(SanitizeRule(allRules.substr(0, spaceIndex)));
                allRules = allRules.substr(spaceIndex + 1, allRules.size());
            }
            else
            {
                subRules.push_back(SanitizeRule(allRules));
                done = true;
            }
        }
        while (!done && !allRules.empty());

        inputRules.insert(make_pair(key, subRules));
    }

    return inputRules;
}


vector<string> BuildRules(ifstream* file)
{
    vector<string> rules;
    map<int, vector<string>> inputRules = ExtractRuleFromFile(file);
    
    for (size_t i = 0; i < inputRules.size(); i++)
    {
        bool finished = false;
        while (!finished)
        {
            finished = true;

            // deal with the current rule
            for (size_t j = 0; j < inputRules[i].size(); j++)
            {
                if (inputRules[i][j] != " ")
                {
                    // if this is a subrule
                    string s = inputRules[i][j];
                    int key = atoi(s.c_str());

                    if (key > 0)
                    {
                        auto it = inputRules.find(key);
                        if (it != inputRules.end())
                        {
                            finished = false;

                            if (find(it->second.begin(), it->second.end(), "|") != it->second.end())
                            {
                                inputRules[i].erase(inputRules[i].begin() + j);
                                
                                inputRules[i].insert(inputRules[i].begin() + j, ")");
                                for (int k = it->second.size()-1; k >= 0; k--)
                                {
                                    inputRules[i].insert(inputRules[i].begin() + j, it->second[k]);
                                }

                                inputRules[i].insert(inputRules[i].begin() + j, "(");

                            }
                            else
                            {
                                inputRules[i].erase(inputRules[i].begin() + j);
                                for (int k = it->second.size() - 1; k >= 0; k--)
                                {
                                    inputRules[i].insert(inputRules[i].begin() + j, it->second[k]);
                                }
                            }
                        }
                        
                    }
                }
            }
        }
    }

    for (std::map<int, vector<string>>::iterator it = inputRules.begin(); it != inputRules.end(); ++it)
    {
        string currentRule("");
        for (size_t k = 0; k < it->second.size(); k++)
        {
            currentRule += it->second[k];
        }
        rules.push_back(currentRule);
    }

    return rules;
}

int CountMessagesMatchingRule(ifstream* file, vector<string> rules, int ruleIndex)
{
    int result = 0;

    string line;
    while (getline(*file, line))
    {
        bool matched = false;

        int i = 1;
        int nbCombi = 15;
        while (i <= nbCombi && !matched)
        {
            string currentRule = rules[ruleIndex];

            int index = currentRule.find("@");
            if (index != string::npos)
            {
                currentRule.replace(index, 1, to_string(i));
            }
            
            index = currentRule.find("@", index + 1);
            if (index != string::npos)
            {
                currentRule.replace(index, 1, to_string(i));
            }

            matched = std::regex_match(line, regex(currentRule));
            i++;
        }

        if (matched)
        {
            result++;
        }
    }

    return result;
}

int CountMessageMatchingRuleZero(string fileName)
{
    std::ifstream file;

    int result = 0;
    file.open(fileName);
    if (!file.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    // Build rules with first part of the file.
    vector<string> rules = BuildRules(&file);

    // Study each messages with the rest of the file.
    result = CountMessagesMatchingRule(&file, rules, 0);

    return result;
}