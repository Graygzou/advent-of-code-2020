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

int main()
{
    map<string, unsigned long long> adresses = map<string, unsigned long long>();

    string line;
    ifstream  myfile;

    cout << (ConvertNumberToBitset(11).to_string() == "000000000000000000000000000000001011") << endl;
    cout << (ConvertNumberToBitset(101).to_string() == "000000000000000000000000000001100101") << endl;
    cout << (ConvertNumberToBitset(349000485).to_string() == "000000010100110011010101001100100101") << endl;
    cout << (ConvertNumberToBitset(517650454).to_string() == "000000011110110110101011100000010110") << endl;

    unsigned long long result = 0;
    myfile.open("example2.txt");
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
                cout << "MASK IS =>         "<< bitmaskStr << endl;
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
            }
        }
    }
    myfile.close();

    string concatenedFloatingAddress = "";
    for (auto it = adresses.begin(); it != adresses.end(); ++it)
    {
        cout << it->first << "  =>    " << it->second << endl;
        cout << CountNumberOfX(it->first) << endl;
        unsigned long long nbFloatingValues = pow(2, CountNumberOfX(it->first));

        cout << "Nb floating values " << nbFloatingValues << endl;

        int sumOfAllCommunX = 0;
        for (auto it2 = adresses.begin(); it2 != it; ++it2)
        {
            sumOfAllCommunX += CountNumberOfCommunX(it->first, it2->first);
        }
        cout << "Sum of commun X = " << sumOfAllCommunX << endl;

        unsigned long long nbAddressesAlreadyAssigned = 0;
        if (sumOfAllCommunX > 0)
        {
            nbAddressesAlreadyAssigned = pow(2, sumOfAllCommunX);
        }

        unsigned long long finalNumberOfAddressed = nbFloatingValues - nbAddressesAlreadyAssigned;

        cout << "final number of addresses impacted " << finalNumberOfAddressed << endl;
        cout << "Final value added " << it->second * finalNumberOfAddressed << endl;
        result += it->second * finalNumberOfAddressed;

        // Concatenated
        //concatenedFloatingAddress = Concat(concatenedFloatingAddress, it->first);
    }

    cout << "Result is : " << result << endl;
}