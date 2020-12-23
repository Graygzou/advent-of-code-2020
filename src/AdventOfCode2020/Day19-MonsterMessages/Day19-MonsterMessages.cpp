// Day19-MonsterMessages.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>

using namespace std;

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
        std::cout << line << std::endl;

        int index = line.find(":");

        int key = atoi(line.substr(0, index).c_str());

        string allRules = line.substr(index + 2);
        vector<string> subRules;
        bool done = false;
        do
        {
            int spaceIndex = allRules.find(" ");

            //cout << allRules << "  " << spaceIndex << endl;

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

        for (size_t i = 0; i < subRules.size(); i++)
        {
            cout << "Test " << subRules[i] << endl;
        }

        inputRules.insert(make_pair(key, subRules));
    }

    for (std::map<int, vector<string>>::iterator it = inputRules.begin(); it != inputRules.end(); ++it)
    {
        std::cout << it->first << " => ";
        for (size_t k = 0; k < it->second.size(); k++)
        {
            cout << it->second[k] << "//";
        }
        cout << endl;
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
        int loopIndex = 0;
        int maxLoop = 1000;
        while (!finished && loopIndex < maxLoop)
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
                        //cout << key << endl;
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

            loopIndex++;
        }
    }

    cout << "++++++++++++++++++" << endl;
    for (std::map<int, vector<string>>::iterator it = inputRules.begin(); it != inputRules.end(); ++it)
    {
        string currentRule("");
        std::cout << it->first << " => " ;
        for (size_t k = 0; k < it->second.size(); k++)
        {
            std::cout << it->second[k];
            currentRule += it->second[k];
        }
        std::cout << endl;

        rules.push_back(currentRule);
    }

    return rules;
}

int NbMessageMatchRule(ifstream* file, vector<string> rules, int ruleIndex)
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
            currentRule.replace(index, 1, to_string(i));
            index = currentRule.find("@", index + 1);
            currentRule.replace(index, 1, to_string(i));

            //cout << currentRule << endl;

            matched = std::regex_match(line, regex(currentRule));
            i++;
        }

        if (matched)
        {
            std::cout << "string object matched\n";
            result++;
        }
    }

    return result;
}

void Part1(string fileName)
{
    std::ifstream file;

    file.open(fileName);
    if (file.is_open())
    {
        vector<string> rules = BuildRules(&file);

        cout << "============" << endl;
        /*for (size_t i = 0; i < rules.size(); i++)
        {
            cout << "at index " << i << " " <<< endl;
        }
        cout << "============" << endl;*/

        int result = NbMessageMatchRule(&file, rules, 0);

        std::cout << "Result for part 1 is " << result << std::endl;
    }
}

int main()
{
    cout << "Monster Messages" << endl;
    Part1("inputModified.txt");

}