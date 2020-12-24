// Day21-AllergenAssessment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// 1447 => too low

vector<string> FindIngredients(string line)
{
    vector<string> ingredients;

    int index = line.find(" ");
    while (index != string::npos && !line.empty())
    {
        ingredients.push_back(line.substr(0, index));
        line = line.substr(index+1, line.size());
        index = line.find(" ");
    }
    ingredients.push_back(line);

    return ingredients;
}

vector<string> FindAllergen(string line)
{
    vector<string> allergens;

    // Remove the contains and last parenthesis
    line = line.substr(9, line.size() - 10);

    int index = line.find(" ");
    while (index != string::npos && !line.empty())
    {
        // There is an extra comma in allergens
        allergens.push_back(line.substr(0, index-1));
        line = line.substr(index + 1, line.size());
        index = line.find(" ");
    }
    allergens.push_back(line);

    return allergens;
}

void Part1(string fileName)
{
    vector<string> allIngredientsListedWithoutAllergens = vector<string>();

    map<string, string> ingredientWithAllergens = map<string, string>();
    map<string, vector<string>> possibleAllergensMapping = map<string, vector<string>>();

    std::ifstream file;
    file.open(fileName);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            int index = line.find("(");
            vector<string> ingredients = FindIngredients(line.substr(0, index - 1));
            vector<string> allergens = FindAllergen(line.substr(index + 1, line.size() - 1));

            for (size_t i = 0; i < ingredients.size(); i++)
            {
                allIngredientsListedWithoutAllergens.push_back(ingredients[i]);
            }

            //cout << "Ingredients" << endl;
            //for (size_t i = 0; i < ingredients.size(); i++)
            //{
            //    cout << ingredients[i] << endl;
            //}
            //cout << "===========================" << endl;

            //cout << "Allergens" << endl;
            //for (size_t i = 0; i < allergens.size(); i++)
            //{
            //    cout << allergens[i] << endl;
            //}
            //cout << "===========================" << endl;

            for (size_t i = 0; i < allergens.size(); i++)
            {
                string currentAllergen = allergens[i];
                for (size_t i = 0; i < ingredients.size(); i++)
                {
                    if (ingredientWithAllergens.find(ingredients[i]) == ingredientWithAllergens.end())
                    {
                        //vector<string> possibilities = possibleAllergensMapping[currentAllergen];
                        if (find(possibleAllergensMapping[currentAllergen].begin(), 
                            possibleAllergensMapping[currentAllergen].end(), ingredients[i]) == possibleAllergensMapping[currentAllergen].end())
                        {
                            possibleAllergensMapping[currentAllergen].push_back(ingredients[i]);
                        }
                        else
                        {
                            cout << "Jaackpot" << endl;
                            ingredientWithAllergens.insert(make_pair(ingredients[i], currentAllergen));
                            possibleAllergensMapping[currentAllergen].clear();
                            possibleAllergensMapping[currentAllergen].push_back(ingredients[i]);

                            // Update all other mapping
                            for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
                            {
                                for (size_t k = 0; k < it->second.size(); k++)
                                {
                                    if (it->second[k] == ingredients[i])
                                    {
                                        it->second.erase(it->second.begin() + k);
                                    }
                                }

                                // Associate possible allergens if only possibilities left.
                                if (it->second.size() == 1)
                                {
                                    string singleIngredient = possibleAllergensMapping[it->first][0];
                                    ingredientWithAllergens.insert(make_pair(singleIngredient, it->first));

                                    possibleAllergensMapping[it->first].clear();
                                    possibleAllergensMapping[it->first].push_back(singleIngredient);
                                }
                            }

                            // Move on to the next allergens
                            break;
                        }
                    }

                    //for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
                    //{
                    //    cout << it->first << " ";
                    //    for (size_t i = 0; i < it->second.size(); i++)
                    //    {
                    //        cout << it->second[i] << " ";
                    //    }
                    //    cout << endl;
                    //}
                    //cout << "------" << endl;
                    //for (auto it = ingredientWithAllergens.begin(); it != ingredientWithAllergens.end(); ++it)
                    //{
                    //    cout << it->first << " " << it->second << endl;
                    //}
                }

                //for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
                //{
                //    cout << it->first << " ";
                //    for (size_t i = 0; i < it->second.size(); i++)
                //    {
                //        cout << it->second[i] << " ";
                //    }
                //    cout << endl;
                //}
            }
        }

        for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
        {
            cout << it->first << " =====> ";
            for (size_t i = 0; i < it->second.size(); i++)
            {
                cout << it->second[i] << " ";
            }
            cout << endl;
        }

        cout << "------" << endl;
        for (auto it = ingredientWithAllergens.begin(); it != ingredientWithAllergens.end(); ++it)
        {
            cout << it->first << " " << it->second << endl;
        }
    }

    unsigned long long result = 0;
    for (size_t i = 0; i < allIngredientsListedWithoutAllergens.size(); i++)
    {
        if (ingredientWithAllergens.find(allIngredientsListedWithoutAllergens[i]) == ingredientWithAllergens.end())
        {
            result++;
        }
    }

    cout << "Nb of ingredients = " << allIngredientsListedWithoutAllergens.size() << endl;
    std::cout << "Result for part 1 is " << result << std::endl;
}

int main()
{
    cout << "Allergen Assessment" << endl;
    Part1("input.txt");
}