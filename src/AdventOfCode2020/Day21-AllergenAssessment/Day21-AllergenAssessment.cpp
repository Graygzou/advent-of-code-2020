// Day21-AllergenAssessment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<string> RemoveFromFirstVector(vector<string> vec1, vector<string> vec2)
{
    vector<string> updateVec = vec1;
    for (size_t i = 0; i < vec2.size(); i++)
    {
        auto it = find(updateVec.begin(), updateVec.end(), vec2[i]);
        if (it != updateVec.end())
        {
            updateVec.erase(it);
        }
    }

    return updateVec;
}

vector<string> ConcatVectorsWithoutDuplicates(vector<string> vec1, vector<string> vec2)
{
    vector<string> concat = vec1;
    for (size_t i = 0; i < vec2.size(); i++)
    {
        if (find(concat.begin(), concat.end(), vec2[i]) == concat.end())
        {
            concat.push_back(vec2[i]);
        }
    }

    return concat;
}

// If an element is in both vector
vector<string> IntersectionVectors(vector<string> vec1, vector<string> vec2)
{
    vector<string> merged = vector<string>();
    for (size_t i = 0; i < vec1.size(); i++)
    {
        if (find(vec2.begin(), vec2.end(), vec1[i].c_str()) != vec2.end())
        {
            merged.push_back(vec1[i]);
        }
    }

    return merged;
}

// Group element that are unique in each vector
vector<string> DifferenceVectors(vector<string> vec1, vector<string> vec2)
{
    vector<string> diff;
    for (size_t i = 0; i < vec1.size(); i++)
    {
        if (find(vec2.begin(), vec2.end(), vec1[i].c_str()) == vec2.end())
        {
            diff.push_back(vec1[i]);
        }
    }

    for (size_t i = 0; i < vec2.size(); i++)
    {
        if (find(vec1.begin(), vec1.end(), vec2[i]) == vec1.end())
        {
            diff.push_back(vec2[i]);
        }
    }

    return diff;
}

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
    vector<string> cumulatedSafeFood = vector<string>();

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

                if (possibleAllergensMapping[currentAllergen].size() <= 0)
                {
                    possibleAllergensMapping[currentAllergen] = ingredients;
                }

                cout << "???????" << endl;
                for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
                {
                    cout << it->first << " ";
                    for (size_t i = 0; i < it->second.size(); i++)
                    {
                        cout << it->second[i] << " ";
                    }
                    cout << endl;
                }
                cout << "???????" << endl;

                vector<string> candidateForAllergen = IntersectionVectors(ingredients, possibleAllergensMapping[currentAllergen]);

                vector<string> safeFood = DifferenceVectors(ingredients, possibleAllergensMapping[currentAllergen]);
                //safeFood = RemoveFromFirstVector(safeFood, candidateForAllergen);

                cumulatedSafeFood = ConcatVectorsWithoutDuplicates(cumulatedSafeFood, safeFood);
                cumulatedSafeFood = RemoveFromFirstVector(cumulatedSafeFood, candidateForAllergen);
                //cumulatedSafeFood = DifferenceVectors(cumulatedSafeFood, safeFood);

                
                possibleAllergensMapping[currentAllergen] = candidateForAllergen;
                // Update safe food
                //if (true)
                //{

                //}
                //cumulatedSafeFood = IntersectionVectors(cumulatedSafeFood, safeFood);
                //if (cumulatedSafeFood.size() <= 0)
                //{
                //    cumulatedSafeFood = safeFood;
                //}
                //cumulatedSafeFood = DifferenceVectors(cumulatedSafeFood, candidateForAllergen);

                cout << "Candidate for allergen" << endl;
                for (size_t i = 0; i < candidateForAllergen.size(); i++)
                {
                    cout << candidateForAllergen[i] << endl;
                }

                cout << "Safe food" << endl;
                for (size_t i = 0; i < safeFood.size(); i++)
                {
                    cout << safeFood[i] << endl;
                }
                cout << "OOF" << endl;
                for (size_t i = 0; i < cumulatedSafeFood.size(); i++)
                {
                    cout << cumulatedSafeFood[i] << endl;
                }
                cout << "==================" << endl;

                for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
                {
                    cout << it->first << " ";
                    for (size_t i = 0; i < it->second.size(); i++)
                    {
                        cout << it->second[i] << " ";
                    }
                    cout << endl;
                }

                //for (size_t i = 0; i < ingredients.size(); i++)
                //{
                //    //vector<string> possibilities = possibleAllergensMapping[currentAllergen];
                //    if (find(possibleAllergensMapping[currentAllergen].begin(), 
                //        possibleAllergensMapping[currentAllergen].end(), ingredients[i]) == possibleAllergensMapping[currentAllergen].end())
                //    {
                //        possibleAllergensMapping[currentAllergen].push_back(ingredients[i]);
                //    }
                //    else
                //    {
                //        cout << "Jaackpot" << endl;
                //        ingredientWithAllergens.insert(make_pair(ingredients[i], currentAllergen));
                //        possibleAllergensMapping[currentAllergen].clear();
                //        possibleAllergensMapping[currentAllergen].push_back(ingredients[i]);

                //        // Update all other mapping
                //        for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
                //        {
                //            for (size_t k = 0; k < it->second.size(); k++)
                //            {
                //                if (it->second[k] == ingredients[i])
                //                {
                //                    it->second.erase(it->second.begin() + k);
                //                }
                //            }

                //            // Associate possible allergens if only possibilities left.
                //            if (it->second.size() == 1)
                //            {
                //                string singleIngredient = possibleAllergensMapping[it->first][0];
                //                ingredientWithAllergens.insert(make_pair(singleIngredient, it->first));

                //                possibleAllergensMapping[it->first].clear();
                //                possibleAllergensMapping[it->first].push_back(singleIngredient);
                //            }
                //        }

                //        // Move on to the next allergens
                //        break;
                //    }
                //    

                //    //for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
                //    //{
                //    //    cout << it->first << " ";
                //    //    for (size_t i = 0; i < it->second.size(); i++)
                //    //    {
                //    //        cout << it->second[i] << " ";
                //    //    }
                //    //    cout << endl;
                //    //}
                //    //cout << "------" << endl;
                //    //for (auto it = ingredientWithAllergens.begin(); it != ingredientWithAllergens.end(); ++it)
                //    //{
                //    //    cout << it->first << " " << it->second << endl;
                //    //}
                //}

                
            }
        }


    }

    cout << "LALLA" << cumulatedSafeFood.size() << endl;
    for (size_t i = 0; i < cumulatedSafeFood.size(); i++)
    {
        cout << cumulatedSafeFood[i] << endl;
    }

    unsigned long long result = 0;
    for (size_t i = 0; i < allIngredientsListedWithoutAllergens.size(); i++)
    {
        if (find(cumulatedSafeFood.begin(), cumulatedSafeFood.end(), allIngredientsListedWithoutAllergens[i]) == cumulatedSafeFood.end())
        {
            result++;
        }
    }

    cout << "Nb of ingredients = " << allIngredientsListedWithoutAllergens.size() << endl;
    std::cout << "Result for part 1 is " << result << std::endl;
}

void Tests()
{
    vector<string> v1{ "a", "b", "c" };
    vector<string> v2{ "b", "c", "d" };
    vector<string> res1{ "b", "c" };
    vector<string> res2{ "a", "d" };
    cout << "Test => " << (IntersectionVectors(v1, v2) == res1) << endl;
    cout << "Test => " << (DifferenceVectors(v1, v2) == res2) << endl;
}

int main()
{
    cout << "Allergen Assessment" << endl;
    //Tests();
    Part1("example.txt");
}