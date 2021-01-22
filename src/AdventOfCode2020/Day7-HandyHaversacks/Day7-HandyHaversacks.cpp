// Day7-HandyHaversacks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <map>

using namespace std;

void CreateColorsStructures(string fileName, map<string, vector<string>>* colorsWithParents, map<string, vector<pair<int, string>>>* colorsWithChildren);
int CountParentOfBagGivenColor(string bagColor, map<string, vector<string>> bagColors);
int CountChildrenOfBagColor(string bagColor, map<string, vector<pair<int, string>>> bagColors);

int main(int argc, char** argv)
{
    cout << "Day 7 - Handy Haversacks" << endl;
    
    const char* fileName = "input.txt";
    if (argc >= 2)
    {
        fileName = argv[1];
    }
    
    map<string, vector<string>> colorsWithParents;
    map<string, vector<pair<int, string>>> colorsWithChildren;

    CreateColorsStructures(fileName, &colorsWithParents, &colorsWithChildren);

    int resultPart1 = CountParentOfBagGivenColor("shiny gold", colorsWithParents);
    cout << "Result for part 1 is " << resultPart1 << endl;

    int resultPart2 = CountChildrenOfBagColor("shiny gold", colorsWithChildren);
    cout << "Result for part 2 is " << resultPart2 << endl;
}

#pragma region Helpers
void DisplayMap(map<string, vector<string>> structureToDisplay)
{
    for (std::map<string, vector<string>>::iterator it = structureToDisplay.begin(); it != structureToDisplay.end(); ++it)
    {
        std::cout << it->first << " => " << it->second.size() << " : ";

        for (std::vector<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            std::cout << it2->c_str() << ", ";
        }

        std::cout << endl;
    }

    system("pause");
}

void DisplayMapPart2(map<string, vector<pair<int, string>>> structureToDisplay)
{
    for (std::map<string, vector<pair<int, string>>>::iterator it = structureToDisplay.begin(); it != structureToDisplay.end(); ++it)
    {
        std::cout << it->first << " => " << it->second.size() << " : ";

        for (std::vector<pair<int, string>>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            std::cout << it2->first << " - " << it2->second.c_str() << ", ";
        }

        std::cout << endl;
    }

    system("pause");
}
#pragma endregion

/// <summary>
/// Count how many bag colors can eventually contain at least one bag of the specified color.
/// </summary>
int CountParentOfBagGivenColor(string bagColor, map<string, vector<string>> bagColors)
{
    int result = 0;
    vector<string> colorLeft({ bagColor });
    vector<string> visitedColor = vector<string>();

    while (!colorLeft.empty())
    {
        string lastColor = colorLeft[colorLeft.size() - 1];

        visitedColor.push_back(lastColor);
        colorLeft.pop_back();

        // Study all the parents of the current color
        for (vector<string>::iterator it2 = bagColors[lastColor].begin(); it2 != bagColors[lastColor].end(); ++it2)
        {
            string parentColor = it2->c_str();

            // We do not want to deal with the same color twice.
            bool alreadyVisitedColor = find(visitedColor.begin(), visitedColor.end(), parentColor) != visitedColor.end();
            // We do not want to add twice a color already queued.
            bool alreadyTagged = find(colorLeft.begin(), colorLeft.end(), parentColor) != colorLeft.end();

            if (!alreadyVisitedColor && !alreadyTagged)
            {
                result++;
                colorLeft.push_back(parentColor);
            }
        }
    }

    return result;
}

/// <summary>
/// Cout how many individual bags are required inside a bag of the given color.
/// </summary>
int CountChildrenOfBagColor(string bagColor, map<string, vector<pair<int, string>>> bagColors)
{
    int result = 0;
    vector<pair<int, string>> colorLeft({ make_pair(1, bagColor) });

    while (!colorLeft.empty())
    {
        pair<int, string> lastColor = colorLeft[colorLeft.size() - 1];
        colorLeft.pop_back();

        // Study the nested bags of the current bag-color.
        // We multiplied the amount a those bag by "lastColor.first" since we study, at the same time, all the bag of the same color.
        int sumOfChidren = 0;
        for (std::vector<pair<int, string>>::iterator it2 = bagColors[lastColor.second].begin(); it2 != bagColors[lastColor.second].end(); ++it2)
        {
            string nextColor = it2->second.c_str();
            colorLeft.push_back(make_pair(it2->first * lastColor.first, nextColor));

            sumOfChidren += it2->first;
        }

        result += lastColor.first * sumOfChidren;
    }

    return result;
}


void CreateColorsStructures(string fileName, map<string, vector<string>> *colorsWithParents, map<string, vector<pair<int, string>>> *colorsWithChildren)
{
    ifstream  myfile;
    myfile.open(fileName);
    if (myfile.is_open())
    {
        string line;
        while (getline(myfile, line))
        {
            cmatch cm;
            regex e("(.*) bags contain (.*)");
            if (!regex_match(line.c_str(), cm, e))
            {
                cout << "string object did not matched" << endl;
            }

            string currentColor = cm[1];
            string containedColors = cm[2];

            // Add the current color
            if (colorsWithParents->find(currentColor) == colorsWithParents->end())
            {
                colorsWithParents->insert(pair<string, vector<string>>(currentColor, vector<string>()));
                colorsWithChildren->insert(pair<string, vector<pair<int, string>>>(currentColor, vector<pair<int, string>>()));
            }

            string delimiter = ", ";

            size_t pos = 0;
            int quantity = 0;
            while (!containedColors.empty()) 
            {
                string subStr = "";
                if ((pos = containedColors.find(delimiter)) != std::string::npos)
                {
                    subStr = containedColors.substr(0, pos);
                    pos += delimiter.length();
                }
                else
                {
                    subStr = containedColors;
                    pos = containedColors.size();
                }

                cmatch cm;
                regex e("([1-9]) ([\ a-z]*) bags?\.?");
                regex_match(subStr.c_str(), cm, e);

                quantity = atoi(cm[1].str().c_str());
                string token = cm[2];

                if (colorsWithParents->find(token) == colorsWithParents->end())
                {
                    colorsWithParents->insert(pair<string, vector<string>>(token, vector<string>()));
                    colorsWithChildren->insert(pair<string, vector<pair<int, string>>>(token, vector<pair<int, string>>()));
                }

                (*colorsWithParents)[token].push_back(currentColor);
                (*colorsWithChildren)[currentColor].push_back(pair<int, string>(quantity, token));

                containedColors.erase(0, pos);
            }
        }
    }
    myfile.close();
}
