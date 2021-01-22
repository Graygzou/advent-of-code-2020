#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

/// <summary>
/// Warning: preambule is expected to be sorted here.
/// </summary>
bool PairFound(vector<long long> preambule, int number)
{
    for (size_t i = 0; i < preambule.size(); i++)
    {
        int secondaryNumberToFind = number - preambule[i];
        for (size_t j = i; j < preambule.size(); j++)
        {
            if (secondaryNumberToFind == preambule[j])
            {
                return true;
            }
            else if (secondaryNumberToFind < preambule[j])
            {
                // Sorted so don't need to go further
                break;
            }
        }
    }

    return false;
}

/// <summary>
/// Find the first number in the list (after the preamble) which is not the sum of two of the 25 numbers before it.
/// </summary>
/// <returns>The first number that does not have this property</returns>
int FindFirstNumberInListNotSumOfPrevious(vector<long long> numbers, int preambuleLength)
{
    vector<long long> preambule = vector<long long>();
    int result = 0;

    int index = 0;
    bool found = false;
    do
    {
        // Get current preambule
        preambule.clear();
        for (size_t i = index; i < index + preambuleLength; i++)
        {
            preambule.push_back(numbers[i]);
        }

        // Sort and Compute side to speed up with basic checks checks.
        sort(preambule.begin(), preambule.end());
        int minSum = preambule[0] + preambule[1];
        int maxSum = preambule[preambule.size() - 2] + preambule[preambule.size() - 1];

        // Check the current number
        // If min and max fits, check all the possibilities.
        int currentNumber = numbers[index + preambuleLength];
        if (currentNumber < minSum || currentNumber > maxSum || !PairFound(preambule, currentNumber))
        {
            found = true;
            result = currentNumber;
            break;
        }

        index++;
    } while (!found && index + preambuleLength < numbers.size());

    return result;
}

pair<int, int> FindMinAndMaxOfSerie(vector<long long> numbers, int i, int j)
{
    int min = numbers[j];
    int max = numbers[j];
    for (size_t k = j; k < i; k++)
    {
        min = min > numbers[k] ? numbers[k] : min;
        max = max < numbers[k] ? numbers[k] : max;
    }

    return make_pair(min, max);
}

/// <summary>
/// Find a contiguous set of at least two numbers in your list which sum to the invalid number from part 1.
/// </summary>
/// <returns>The sum of the smallest and largest number in this contiguous range</returns>
int FindEncryptionWeakness(vector<long long> numbers, int numberToDecomposed)
{
    int result = 0;

    // Find index of number
    vector<long long>::iterator it;
    it = find(numbers.begin(), numbers.end(), numberToDecomposed);
    if (it == numbers.end())
    {
        cout << "Element need to be include in numbers !" << std::endl;
        return -1;
    }

    bool found = false;
    size_t i = distance(numbers.begin(), it);
    while(!found && i > 0)
    {
        // try to add up following numbers until the sum is >= to the number we try to reach
        long long currentSum = 0;
        int j = i;
        do
        {
            j--;
            currentSum += numbers[j];
        } while (currentSum < numberToDecomposed && j > 0);

        if (currentSum == numberToDecomposed)
        {
            pair<int, int> minMax = FindMinAndMaxOfSerie(numbers, i, j);
            result = minMax.first + minMax.second;
            found = true;
        }

        i--;
    }

    return result;
}

int main()
{
    cout << "Day 9 - Encoding Error" << endl;
    
    const char* fileName = "input.txt";

    ifstream  myfile;
    myfile.open(fileName);
    if (!myfile.is_open())
    {
        std::cout << "Can't open the file: " << fileName << std::endl;
        exit(-1);
    }

    vector<long long> lines = vector<long long>();
    string line;
    while (getline(myfile, line))
    {
        lines.push_back(_atoi64(line.c_str()));
    }
    myfile.close();
    
    int preambuleLength = 25;
    int part1Result = FindFirstNumberInListNotSumOfPrevious(lines, preambuleLength);
    cout << "Result for part 1 is : " << part1Result << endl;

    int part2Result = FindEncryptionWeakness(lines, part1Result);
    cout << "Result for part 2 is : " << part2Result << endl;
}