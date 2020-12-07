// Day7-HandyHaversacks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <map>

using namespace std;

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

#pragma region Part 1
// Part 1
int CountParentOfBagColor(string bagColor, map<string, vector<string>> bagColors)
{
    int result = 0;
    vector<string> colorLeft({ bagColor });
    vector<string> visitedColor = vector<string>();

    while (!colorLeft.empty())
    {
        string lastColor = colorLeft[colorLeft.size() - 1];
        cout << "Current color is " << lastColor << endl;

        visitedColor.push_back(lastColor);
        colorLeft.pop_back();

        for (std::vector<string>::iterator it2 = bagColors[lastColor].begin(); it2 != bagColors[lastColor].end(); ++it2)
        {
            string nextColor = it2->c_str();
            cout << "Next color is " << nextColor << endl;

            bool alreadyVisitedColor = find(visitedColor.begin(), visitedColor.end(), nextColor) != visitedColor.end();
            bool alreadyTagged = find(colorLeft.begin(), colorLeft.end(), nextColor) != colorLeft.end();

            cout << "Add color " << (find(visitedColor.begin(), visitedColor.end(), nextColor) == visitedColor.end()) << endl;
            cout << "Add color " << it2->c_str() << endl;

            if (!alreadyVisitedColor && !alreadyTagged)
            {
                result++;
                colorLeft.push_back(nextColor);
            }
        }

        /*if (colorLeft.size() <= 0)
        {
            break;
        }*/

        /*for (std::vector<string>::iterator it8 = visitedColor.begin(); it8 != visitedColor.end(); ++it8)
        {
            std::cout << it8->c_str() << '\n';
        }
        cout << "===========" << endl;*/
        for (std::vector<string>::iterator it8 = colorLeft.begin(); it8 != colorLeft.end(); ++it8)
        {
            std::cout << it8->c_str() << '\n';
        }
        //system("pause");

        cout << "COLOR LEFT SIZE = " << colorLeft.size() << endl;
    }

    return result;
}
#pragma endregion

#pragma region Part 2
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


int CountChildrenOfBagColor(string bagColor, map<string, vector<pair<int, string>>> bagColors)
{
    int result = 0;
    vector<pair<int, string>> colorLeft({ make_pair(1, bagColor) });
    //vector<string> visitedColor = vector<string>();

    while (!colorLeft.empty())
    {
        pair<int, string> lastColor = colorLeft[colorLeft.size() - 1];
        cout << "Current color is " << lastColor.second << "with factor " << lastColor.first << endl;

        //visitedColor.push_back(lastColor.second);
        colorLeft.pop_back();

        int sumOfChidren = 0;
        for (std::vector<pair<int, string>>::iterator it2 = bagColors[lastColor.second].begin(); it2 != bagColors[lastColor.second].end(); ++it2)
        {
            string nextColor = it2->second.c_str();
            cout << "Next color is " << nextColor << endl;

            sumOfChidren += it2->first;
            cout << "next value is " << it2->first * lastColor.first << endl;
            colorLeft.push_back(make_pair(it2->first * lastColor.first, nextColor));
        }

        cout << "Sum of children " << sumOfChidren << endl;
        result += (lastColor.first * sumOfChidren);
        cout << "Result is currently " << result << endl;

        /*if (colorLeft.size() <= 0)
        {
            break;
        }*/

        /*for (std::vector<string>::iterator it8 = visitedColor.begin(); it8 != visitedColor.end(); ++it8)
        {
            std::cout << it8->c_str() << '\n';
        }
        cout << "===========" << endl;*/
        for (std::vector<pair<int, string>>::iterator it8 = colorLeft.begin(); it8 != colorLeft.end(); ++it8)
        {
            std::cout << it8->second.c_str() << "with factor " << it8->first << '\n';
        }
        //system("pause");

        cout << "COLOR LEFT SIZE = " << colorLeft.size() << endl;
    }

    return result;
}


int main()
{
    map<string, vector<string>> colorsWithParents;
    map<string, vector<pair<int, string>>> colorsWithChildren;

    string line;
    ifstream  myfile;
    myfile.open("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            //cout << line.c_str() << endl;

            cmatch cm;
            //regex e("(.*) bags contain(?: ([1-9]) ([\ a-z]*) bags?(?:\,|\.))+");
            regex e("(.*) bags contain (.*)");
            if (!regex_match(line.c_str(), cm, e))
            {
                std::cout << "string object did not matched\n";
            }

            string currentColor = cm[1];
            string containedColors = cm[2];

            // Add the current color
            if (colorsWithParents.find(currentColor) == colorsWithParents.end())
            {
                colorsWithParents.insert(pair<string, vector<string>>(currentColor, vector<string>()));
                colorsWithChildren.insert(pair<string, vector<pair<int, string>>>(currentColor, vector<pair<int, string>>()));
            }

            std::string delimiter = ", ";

            size_t pos = 0;
            int quantity = 0;
            string token;
            while ((pos = containedColors.find(delimiter)) != std::string::npos) {
                token = containedColors.substr(0, pos);
                //std::cout << token << std::endl;

                cmatch cm;
                regex e("([1-9]) ([\ a-z]*) bags?\.?");
                regex_match(token.c_str(), cm, e);

                quantity = atoi(cm[1].str().c_str());
                token = cm[2];
                //std::cout << "Token parsed  " << token << std::endl;

                if (colorsWithParents.find(token) == colorsWithParents.end())
                {
                    colorsWithParents.insert(pair<string, vector<string>>(token, vector<string>()));
                    colorsWithChildren.insert(pair<string, vector<pair<int, string>>>(token, vector<pair<int, string>>()));
                }
                colorsWithParents[token].push_back(currentColor);

                // Part 2
                colorsWithChildren[currentColor].push_back(pair<int, string>(quantity, token));

                containedColors.erase(0, pos + delimiter.length());
            }

            //std::cout << "END" << containedColors << std::endl;

            e = "([1-9]) ([\ a-z]*) bags?\.?";
            if (regex_match(containedColors.c_str(), cm, e))
            {
                quantity = atoi(cm[1].str().c_str());
                containedColors = cm[2];
                //std::cout << "Token parsed" << containedColors << std::endl;

                if (colorsWithParents.find(containedColors) == colorsWithParents.end())
                {
                    colorsWithParents.insert(pair<string, vector<string>>(containedColors, vector<string>()));
                }
                colorsWithParents[containedColors].push_back(currentColor);

                // Part 2
                colorsWithChildren[currentColor].push_back(pair<int, string>(quantity, containedColors));
            }

            cout << "here" << endl;
        }

        // Display everything
        DisplayMap(colorsWithParents);
        DisplayMapPart2(colorsWithChildren);

        // result part 1
        //int resultPart1 = CountParentOfBagColor("shiny gold", colorsWithParents);
        int resultPart2 = CountChildrenOfBagColor("shiny gold", colorsWithChildren);

        //cout << "Result for part 1 is " << resultPart1 << endl;
        cout << "Result for part 2 is " << resultPart2 << endl;
    }

    myfile.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
