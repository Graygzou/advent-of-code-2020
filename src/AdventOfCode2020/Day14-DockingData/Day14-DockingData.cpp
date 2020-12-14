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


int main()
{
    map<unsigned long long, unsigned long long> adresses = map<unsigned long long, unsigned long long>();

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

                bitset<BITMASK_SIZE> comvertedBitset = ConvertNumberToBitset(numberToStore);
                cout << "Value              " << comvertedBitset << endl;
                cout << "bitSet defined     " << bitmaskStr << endl;

                bitset<BITMASK_SIZE> bitmaskApplied = comvertedBitset;
                for (size_t i = 0; i < bitmaskStr.size(); i++)
                {
                    if (bitmaskStr[i] == '0')
                    {
                        bitmaskApplied.set(bitmaskStr.size() - 1 - i, 0);
                    }
                    else if (bitmaskStr[i] == '1')
                    {
                        bitmaskApplied.set(bitmaskStr.size() - 1 - i);
                    }
                    else
                    {
                        // Leave unchanged
                    }
                }

                //bitset<BITMASK_SIZE> bitmaskApplied = comvertedBitset | bitmask;
                cout << "Final bitmask      " << bitmaskApplied << endl;
                cout << "Converted value is " << bitmaskApplied.to_ullong() << endl;
                adresses[storageAddr] = bitmaskApplied.to_ullong();
            }
        }
    }
    myfile.close();

    for (std::map<unsigned long long, unsigned long long>::iterator it = adresses.begin(); it != adresses.end(); ++it)
    {
        cout << it->first << "=> " << it->second << endl;
        result += it->second;
    }

    cout << "Result is : " << result << endl;
}