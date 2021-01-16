// Day14-DockingData.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

const int MASK_TEXT = 7;
const int BITMASK_SIZE = 36;

vector<string> CompleteProgram(string fileName, map<string, unsigned long long>* adresses, int decoderVersion);
unsigned long long SumValuesInMemory(vector<string> memory, map<string, unsigned long long> adresses);

int main()
{
    cout << "Day 14 - Docking Data" << endl;

    string fileName = "input.txt";
    map<string, unsigned long long> adresses = map<string, unsigned long long>();

    vector<string> memory = CompleteProgram(fileName, &adresses, 1);
    unsigned long long resultPart1 = SumValuesInMemory(memory, adresses);
    cout << "Result for part 1 is : " << resultPart1 << endl;

    // Reset
    adresses.clear();

    memory = CompleteProgram(fileName, &adresses, 2);
    unsigned long long resultPart2 = SumValuesInMemory(memory, adresses);
    cout << "Result for part 2 is : " << resultPart2 << endl;
}

#pragma region Helpers
bitset<BITMASK_SIZE> ConvertNumberToBitset(unsigned long long number)
{
    std::bitset<BITMASK_SIZE> bitmask;

    int index = 0;
    while (number != 0)
    {
        unsigned long long currentByte = number % 2;
        number /= 2;
        bitmask.set(index, currentByte);
        index++;
    }

    return bitmask;
}

int CountNumberOfX(string adresse)
{
    int result = 0;
    for (size_t i = 0; i < adresse.size(); i++)
    {
        if (adresse[i] == 'X')
        {
            result++;
        }
    }

    return result;
}

void ComputeAllPossibilities(string addr, int nbPossibilities, vector<string> *res)
{
    vector<string> results = vector<string>(nbPossibilities);

    int nbXMeet = 0;
    for (int i = 0; i < addr.size(); i++)
    {
        char c = addr[i];

        if (c == 'X')
        {
            int half = nbPossibilities / pow(2, nbXMeet + 1);
            int end = nbPossibilities / pow(2, nbXMeet);

            // Duplicated all possibilities and add 0 to half of them and 1 to the other half
            for (size_t j = 0; j < half; j++)
            {
                results[j].push_back('0');
            }
            for (size_t j = half; j < end; j++)
            {
                results[j].push_back('1');
            }

            if (end != nbPossibilities)
            {
                // Mirror
                int mirrorIndex = end;
                while (mirrorIndex != nbPossibilities)
                {
                    int copyIndex = mirrorIndex % end;
                    results[mirrorIndex].push_back(results[copyIndex][results[copyIndex].size() - 1]);

                    mirrorIndex++;
                }
            }

            nbXMeet++;
        }
        else
        {
            // Add the number to all possibilities
            for (size_t j = 0; j < results.size(); j++)
            {
                results[j].push_back(c);
            }
        }
    }

    *res = results;
}

bool ContainsCommunAdresses(string addr1, string addr2)
{
    bool hasCommunAddresses = true;
    for (size_t i = 0; i < addr1.size(); i++)
    {
        if (addr1[i] != 'X' && addr2[i] != 'X' && addr1[i] != addr2[i])
        {
            hasCommunAddresses = false;
        }
    }

    return hasCommunAddresses;
}

int CountNumberOfCommunX(string addr1, string addr2)
{
    int result = 0;
    for (size_t i = 0; i < addr1.size(); i++)
    {
        if (addr1[i] == 'X' && addr2[i] == 'X')
        {
            result++;
        }
    }

    return result;
}

string Concat(string addr1, string addr2)
{
    string result = "";
    for (size_t i = 0; i < addr1.size(); i++)
    {
        if (addr1[i] == 'X' || addr2[i] == 'X')
        {
            result[i] = 'X';
        }
        else if (addr1[i] == addr2[i])
        {
            result[i] = addr1[i];
        }
    }

    return result;
}

int RemoveCommunAddresses(vector<string> *possibilitiesLeft, vector<string> possibilitieFound)
{
    int nbDuplicateFound = 0;

    vector<string> temp = *possibilitiesLeft;
    int i = 0;
    while (i < temp.size() && temp.size() > 0)
    {
        bool found = false;

        for (size_t j = 0; j < possibilitieFound.size(); j++)
        {
            if (temp[i] == possibilitieFound[j])
            {
                found = true;
                temp.erase(temp.begin()+i);
                nbDuplicateFound++;
                break;
            }
        }

        if (!found)
        {
            i++;
        }
    }

    *possibilitiesLeft = temp;
    return nbDuplicateFound;
}
#pragma endregion

vector<string> CompleteProgram(string fileName, map<string, unsigned long long> *adresses, int decoderVersion)
{
    vector<string> indexes = vector<string>();
    
    ifstream  myfile;
    myfile.open(fileName);
    if (myfile.is_open())
    {
        bitset<BITMASK_SIZE> bitmask = 0;
        string bitmaskStr = "";
        
        string line;
        while (getline(myfile, line))
        {
            size_t pos;
            if ((pos = line.find("mask")) != string::npos)
            {
                bitmaskStr = line.substr(pos + MASK_TEXT);
            }
            else
            {
                cmatch cm;
                regex e("(?:mem.)([0-9]*)(?:. = )([0-9]*)");
                regex_match(line.c_str(), cm, e);

                unsigned long long storageAddr = _atoi64(cm[1].str().c_str());
                unsigned long long numberToStore = _atoi64(cm[2].str().c_str());

                bitset<BITMASK_SIZE> comvertedBitsetAddr;
                string bitmaskApplied;

                if (decoderVersion == 1)
                {
                    bitmaskApplied = to_string(storageAddr);
                    comvertedBitsetAddr = ConvertNumberToBitset(numberToStore);
                }
                else if (decoderVersion == 2)
                {
                    comvertedBitsetAddr = ConvertNumberToBitset(storageAddr);
                    bitmaskApplied = comvertedBitsetAddr.to_string();
                }

                for (size_t i = 0; i < bitmaskStr.size(); i++)
                {
                    if (decoderVersion == 1)
                    {
                        if (bitmaskStr[i] == '0')
                        {
                            comvertedBitsetAddr.set(bitmaskStr.size() - 1 - i, 0);
                        }
                        else if (bitmaskStr[i] == '1')
                        {
                            comvertedBitsetAddr.set(bitmaskStr.size() - 1 - i);
                        }
                        else
                        {
                            // Leave unchanged
                        }
                    }
                    else if (decoderVersion == 2)
                    {
                        if (bitmaskStr[i] == '0')
                        {
                            // unchanged
                        }
                        else if (bitmaskStr[i] == '1')
                        {
                            bitmaskApplied[i] = '1';
                        }
                        else
                        {
                            // floating value
                            bitmaskApplied[i] = 'X';
                        }
                    }
                }

                if (decoderVersion == 1)
                {
                    (*adresses)[bitmaskApplied] = comvertedBitsetAddr.to_ullong();
                    if (find(indexes.begin(), indexes.end(), bitmaskApplied) == indexes.end())
                    {
                        indexes.push_back(bitmaskApplied);
                    }
                }
                else if (decoderVersion == 2)
                {
                    (*adresses)[bitmaskApplied] = numberToStore;
                    indexes.push_back(bitmaskApplied);
                }
            }
        }
    }
    myfile.close();

    return indexes;
}

unsigned long long SumValuesInMemory(vector<string> memory, map<string, unsigned long long> adresses)
{
    unsigned long long result = 0;

    for (int i = memory.size() - 1; i >= 0; i--)
    {
        auto it = adresses.find(memory[i]);

        unsigned long long finalNumberOfAddressed = 1;

        int numberOfXs = CountNumberOfX(it->first);
        if (numberOfXs > 0)
        {
            unsigned long long nbFloatingValues = pow(2, numberOfXs);
            vector<string> possibilitiesLeft = vector<string>(nbFloatingValues);
            ComputeAllPossibilities(it->first, nbFloatingValues, &possibilitiesLeft);

            for (size_t j = memory.size() - 1; j > i; j--)
            {
                auto it2 = adresses.find(memory[j]);
                if (ContainsCommunAdresses(it->first, it2->first))
                {
                    int nbPoss = pow(2, CountNumberOfX(it2->first));

                    vector<string> possibilities = vector<string>(nbPoss);
                    ComputeAllPossibilities(it2->first, nbPoss, &possibilities);
                    int nbDuplicated = RemoveCommunAddresses(&possibilitiesLeft, possibilities);
                }
            }
            finalNumberOfAddressed = possibilitiesLeft.size();
        }

        result += it->second * finalNumberOfAddressed;
    }

    return result;
}

void Tests()
{
    cout << (ConvertNumberToBitset(11).to_string() == "000000000000000000000000000000001011") << endl;
    cout << (ConvertNumberToBitset(101).to_string() == "000000000000000000000000000001100101") << endl;
    cout << (ConvertNumberToBitset(349000485).to_string() == "000000010100110011010101001100100101") << endl;
    cout << (ConvertNumberToBitset(517650454).to_string() == "000000011110110110101011100000010110") << endl;
}