// Day7-HandyHaversacks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <map>

using namespace std;

int main()
{
    int nbPassportsValid = 0;

    map<string, vector<string>> colors;

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
            if (colors.find(currentColor) == colors.end())
            {
                colors.insert(pair<string, vector<string>>(currentColor, vector<string>()));
            }

            std::string delimiter = ", ";

            size_t pos = 0;
            std::string token;
            while ((pos = containedColors.find(delimiter)) != std::string::npos) {
                token = containedColors.substr(0, pos);
                //std::cout << token << std::endl;

                cmatch cm;
                regex e("([1-9]) ([\ a-z]*) bags?\.?");
                regex_match(token.c_str(), cm, e);

                token = cm[2];
                //std::cout << "Token parsed  " << token << std::endl;

                if (colors.find(token) == colors.end())
                {
                    colors.insert(pair<string, vector<string>>(token, vector<string>()));
                }
                colors[token].push_back(currentColor);

                containedColors.erase(0, pos + delimiter.length());
            }

            //std::cout << "END" << containedColors << std::endl;

            e = "([1-9]) ([\ a-z]*) bags?\.?";
            if (regex_match(containedColors.c_str(), cm, e))
            {
                containedColors = cm[2];
                //std::cout << "Token parsed" << containedColors << std::endl;

                if (colors.find(containedColors) == colors.end())
                {
                    colors.insert(pair<string, vector<string>>(containedColors, vector<string>()));
                }
                colors[containedColors].push_back(currentColor);
            }

            cout << "here" << endl;
        }

        // Display everything
        for (std::map<string, vector<string>>::iterator it = colors.begin(); it != colors.end(); ++it)
        {
            std::cout << it->first << " => " << it->second.size() << " : ";

            for (std::vector<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                std::cout << it2->c_str() << ", ";
            }

            std::cout << endl;
        }

        system("pause");

        // result part 1
        int result = 0;
        vector<string> colorLeft({ "shiny gold" });
        vector<string> visitedColor = vector<string>();

        //std::vector<string>::iterator it = colorLeft.begin();
        while (!colorLeft.empty())
        //for (auto it = colorLeft.begin(); it != colorLeft.end(); ++it)
        {
            string lastColor = colorLeft[colorLeft.size() - 1];

            cout << "Current color is " << lastColor << endl;

           /* if (find(visitedColor.begin(), visitedColor.end(), lastColor) == visitedColor.end())
            {
                result += colors[lastColor].size();
            }*/

            cout << "Result is " << result << endl;

            visitedColor.push_back(lastColor);
            colorLeft.pop_back();
            
            //bool updated = false;
            for (std::vector<string>::iterator it2 = colors[lastColor].begin(); it2 != colors[lastColor].end(); ++it2)
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
                    //updated = true;
                    colorLeft.push_back(nextColor);
                    //it = colorLeft.begin();
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

        cout << "Result is " << result << endl;
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
