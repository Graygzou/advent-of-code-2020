#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

bool PairFound(vector<long long> preambule, int number)
{
    for (size_t i = 0; i < preambule.size(); i++)
    {
        int secondaryNumberToFind = number - preambule[i];
        //cout << secondaryNumberToFind << endl;
        for (size_t j = i; j < preambule.size(); j++)
        {
            if (secondaryNumberToFind == preambule[j])
            {
                //cout << "Pair found : " << preambule[i] << ", " << preambule[j] << endl;
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

int Part1(vector<long long> numbers, int preambuleLength)
{
    vector<long long> preambule = vector<long long>();
    int result = 0;

    int index = 0;
    bool found = false;
    do
    {
        // Get preambule
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

int Part2(vector<long long> numbers, int numberToDecomposed)
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

    long long index = distance(numbers.begin(), it);

    bool found = false;
    size_t i = index;
    while(!found && i > 0)
    {
        // try to add up following number
        long long currentSum = 0;
        int j = i;
        do
        {
            j--;
            currentSum += numbers[j];
        } while (currentSum < numberToDecomposed && j > 0);

        if (currentSum == numberToDecomposed)
        {
            int min = numbers[j];
            int max = numbers[j];
            int sum = 0;
            for (size_t k = j; k < i; k++)
            {
                min = min > numbers[k] ? numbers[k] : min;
                max = max < numbers[k] ? numbers[k] : max;
                sum += numbers[k];
            }
            cout << "should be equals to zero = " << numberToDecomposed - sum << endl;

            result = min + max;
            found = true;
        }

        i--;
    }

    return result;
}

int main()
{
    vector<long long> lines = vector<long long>();

    string line;
    ifstream  myfile;

    myfile.open("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines.push_back(_atoi64(line.c_str()));
        }
    }
    myfile.close();
    
    int preambuleLength = 25;
    int part1Result = Part1(lines, preambuleLength);
    cout << "Result for part 1 is : " << part1Result << endl;

    int part2Result = Part2(lines, part1Result);
    cout << "Result for part 2 is : " << part2Result << endl;
}