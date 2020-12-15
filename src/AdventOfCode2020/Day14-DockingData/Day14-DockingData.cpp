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

const int BITMASK_SIZE = 36;

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
            //cout << "Half " << half << endl;
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

        //cout << "Intermediate result " << endl;
        //for (size_t acc = 0; acc < results.size(); acc++)
        //{
        //    cout << results[acc] << endl;
        //}
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
        else
        {
            // floating value
            //bitmaskApplied[i] = 'X';
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


int main()
{
    vector<string> indexes = vector<string>();
    map<string, unsigned long long> adresses = map<string, unsigned long long>();

    string line;
    ifstream  myfile;

    cout << (ConvertNumberToBitset(11).to_string() == "000000000000000000000000000000001011") << endl;
    cout << (ConvertNumberToBitset(101).to_string() == "000000000000000000000000000001100101") << endl;
    cout << (ConvertNumberToBitset(349000485).to_string() == "000000010100110011010101001100100101") << endl;
    cout << (ConvertNumberToBitset(517650454).to_string() == "000000011110110110101011100000010110") << endl;

    unsigned long long result = 0;
    myfile.open("input.txt");
    if (myfile.is_open())
    {

        bitset<BITMASK_SIZE> bitmask = 0;
        string bitmaskStr = "";

        int lineIndex = 0;
        while (getline(myfile, line))
        {
            size_t pos;
            if ((pos = line.find("mask")) != string::npos)
            {
                //replace(line.begin(), line.end(), 'X', '0');
                bitmaskStr = line.substr(pos + 7);
                //cout << "MASK IS =>         "<< bitmaskStr << endl;
            }
            else
            {
                cmatch cm;
                regex e("(?:mem.)([0-9]*)(?:. = )([0-9]*)");
                regex_match(line.c_str(), cm, e);

                unsigned long long storageAddr = _atoi64(cm[1].str().c_str());
                unsigned long long numberToStore = _atoi64(cm[2].str().c_str());

                cout << "Found " << storageAddr << ", " << numberToStore << endl;

                bitset<BITMASK_SIZE> comvertedBitsetAddr = ConvertNumberToBitset(storageAddr);
                cout << "Value              " << comvertedBitsetAddr << endl;
                cout << "bitSet defined     " << bitmaskStr << endl;

                string bitmaskApplied = comvertedBitsetAddr.to_string();
                for (size_t i = 0; i < bitmaskStr.size(); i++)
                {
                    if (bitmaskStr[i] == '0')
                    {
                        // unchanged
                        //bitmaskApplied[i] = '0';
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

                //bitset<BITMASK_SIZE> bitmaskApplied = comvertedBitset | bitmask;
                cout << "Final bitmask      " << bitmaskApplied << endl;
                //cout << "Converted value is " << bitmaskApplied.to_ullong() << endl;
                adresses[bitmaskApplied] = numberToStore;
                indexes.push_back(bitmaskApplied);
            }
        }
    }
    myfile.close();

    string concatenedFloatingAddress = "";
    for (int i = indexes.size() - 1; i >= 0; i--)
    {
        std::cout << i << endl;

        auto it = adresses.find(indexes[i]);
        std::cout << it->first << "  =>    " << it->second << endl;
        std::cout << CountNumberOfX(it->first) << endl;
        unsigned long long nbFloatingValues = pow(2, CountNumberOfX(it->first));

        //std::cout << "Nb floating values " << nbFloatingValues << endl;

        vector<string> possibilitiesLeft = vector<string>(nbFloatingValues);
        ComputeAllPossibilities(it->first, nbFloatingValues, &possibilitiesLeft);

       /* cout << "Nb possibilities is " << possibilitiesLeft.size() << endl;
        for (size_t acc = 0; acc < possibilitiesLeft.size(); acc++)
        {
            cout << possibilitiesLeft[acc] << endl;
        }
        cout << endl;*/


        //bool hasCommunAdresses = false;
        //int sumOfAllCommunX = 0;
        for (size_t j = indexes.size() - 1; j > i; j--)
        {
            auto it2 = adresses.find(indexes[j]);
            if (ContainsCommunAdresses(it->first, it2->first))
            {
                int nbPoss = pow(2, CountNumberOfX(it2->first));

                vector<string> possibilities = vector<string>(nbPoss);
                ComputeAllPossibilities(it2->first, nbPoss, &possibilities);
                int nbDuplicated = RemoveCommunAddresses(&possibilitiesLeft, possibilities);

                std::cout << "nb duplicate found are " << nbDuplicated << endl;
                //hasCommunAdresses = true;

                //sumOfAllCommunX += CountNumberOfCommunX(it->first, it2->first);
            }
        }
        //std::cout << "Contains commun addresses is " << hasCommunAdresses << " / And Sum of commun X = " << sumOfAllCommunX << endl;

        //unsigned long long nbAddressesAlreadyAssigned = 0;
        //if (hasCommunAdresses)
        //{
        //    nbAddressesAlreadyAssigned = pow(2, sumOfAllCommunX);
        //}
        cout << "Final nb possibilities is " << possibilitiesLeft.size() << endl;

        unsigned long long finalNumberOfAddressed = possibilitiesLeft.size();

        //std::cout << "final number of addresses impacted " << finalNumberOfAddressed << endl;
        //std::cout << "Final value added " << it->second * finalNumberOfAddressed << endl;
        result += it->second * finalNumberOfAddressed;

        // Concatenated
        //concatenedFloatingAddress = Concat(concatenedFloatingAddress, it->first);
    }

    cout << "Result is : " << result << endl;
}