// Day21-AllergenAssessment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void RunDay21(string fileName);

int main()
{
    cout << "Day 21 - Allergen Assessment" << endl;
    //Tests();
    RunDay21("input.txt");
}

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

void RunDay21(string fileName)
{
    vector<string> allIngredientsListedWithoutAllergens = vector<string>();
    vector<string> cumulatedSafeFood = vector<string>();
    map<string, vector<string>> possibleAllergensMapping = map<string, vector<string>>();

    std::ifstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

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

        for (size_t i = 0; i < allergens.size(); i++)
        {
            string currentAllergen = allergens[i];

            if (possibleAllergensMapping[currentAllergen].size() <= 0)
            {
                possibleAllergensMapping[currentAllergen] = ingredients;
            }

            vector<string> candidateForAllergen = IntersectionVectors(ingredients, possibleAllergensMapping[currentAllergen]);
            vector<string> safeFood = DifferenceVectors(ingredients, possibleAllergensMapping[currentAllergen]);
            cumulatedSafeFood = ConcatVectorsWithoutDuplicates(cumulatedSafeFood, safeFood);  

            possibleAllergensMapping[currentAllergen] = candidateForAllergen;
        }

        // Update the final list
        for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
        {
            cumulatedSafeFood = RemoveFromFirstVector(cumulatedSafeFood, it->second);
        }
    }

    map<string, string> ingredientWithAllergens = map<string, string>();
    for (auto it = possibleAllergensMapping.begin(); it != possibleAllergensMapping.end(); ++it)
    {
        if (it->second.size() == 1)
        {
            string ingredientFound = it->second[0];
            ingredientWithAllergens.insert(make_pair(it->first, ingredientFound));

            // Remove the ingredient from all lists.
            for (auto it2 = possibleAllergensMapping.begin(); it2 != possibleAllergensMapping.end(); ++it2)
            {
                auto index = find(it2->second.begin(), it2->second.end(), ingredientFound);
                if (index != it2->second.end())
                {
                    it2->second.erase(index);
                }
            }

            // Start over
            it = possibleAllergensMapping.begin();
        }
    }

    unsigned long long result = 0;
    for (size_t i = 0; i < allIngredientsListedWithoutAllergens.size(); i++)
    {
        if (find(cumulatedSafeFood.begin(), cumulatedSafeFood.end(), allIngredientsListedWithoutAllergens[i]) != cumulatedSafeFood.end())
        {
            result++;
        }
    }

    std::cout << "Result for part 1 is " << result << std::endl;
    std::cout << "Canonical dangerous ingredient list is ";
    for (auto it = ingredientWithAllergens.begin(); it != ingredientWithAllergens.end(); ++it)
    {
        cout << it->second << ",";
    }
    cout << endl;
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