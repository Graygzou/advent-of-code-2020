// Day18-OperationOrder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

enum CurrentOperation { NONE, ADD, MULT };

unsigned long long EvaluateExpression(std::string expression, int *offset)
{
    unsigned long long result = 0;
    //unsigned long long previousNumber = 0;
    unsigned long long subCalculation = 0;
    CurrentOperation ope = CurrentOperation::NONE;

    for (int i = *offset; i < expression.size(); i++)
    {
        //std::cout << expression[i] << std::endl;
        if (expression[i] != ' ')
        {
            if (expression[i] == '+')
            {
                ope = CurrentOperation::ADD;
            }
            else if (expression[i] == '*')
            {
                ope = CurrentOperation::MULT;
            }
            else if (expression[i] == '(')
            {
                *offset = i + 1;
                subCalculation = EvaluateExpression(expression, offset);
                //std::cout << "subCalculation" << subCalculation << std::endl;

                if (ope == CurrentOperation::NONE)
                {
                    result = subCalculation;
                    //std::cout << "NONE" << result << std::endl;
                }
                else if (ope == CurrentOperation::ADD)
                {
                    result += subCalculation;
                    //std::cout << "ADD" << result << std::endl;
                }
                else if (ope == CurrentOperation::MULT)
                {
                    result *= subCalculation;
                    //std::cout << "MULT" << result << std::endl;
                }
                //previousNumber = subCalculation;

                i = *offset;
            }
            else if (expression[i] == ')')
            {
                *offset = i;
                return result;
            }
            else
            {
                std::string numberStr(1, expression[i]);
                int currentNumber = atoi(numberStr.c_str());

                if (ope == CurrentOperation::NONE)
                {
                    result = currentNumber;
                    //std::cout << "NONE" << result << std::endl;
                }
                else if (ope == CurrentOperation::ADD)
                {
                    result += currentNumber;
                    //std::cout << "ADD" << result << std::endl;
                }
                else if (ope == CurrentOperation::MULT)
                {
                    result *= currentNumber;
                    //std::cout << "MULT" << result << std::endl;
                }
                //previousNumber = currentNumber;
            }
        }
    }

    *offset = expression.size();
    return result;
}

// 89770825571 => too low
// 7848476156

void Part1(std::string fileName)
{
    std::ifstream file;
    file.open(fileName);

    std::string line;
    if (file.is_open())
    {
        unsigned long long part1Result = 0;
        int* offset = new int(0);
        while (getline(file, line))
        {
            std::cout << line << std::endl;
            *offset = 0;
            unsigned long long currentResult = EvaluateExpression(line, offset);
            std::cout << "Current Result is " << currentResult << std::endl;

            part1Result += currentResult;

            std::cout << "Cumulated result is " << part1Result << std::endl;
        }

        std::cout << "Result for part 1 is " << part1Result << std::endl;
    }
}

void Tests()
{
    Part1("example.txt");
    int* offset = new int(0);
    std::cout << (EvaluateExpression("1 + 2 * 3 + 4 * 5 + 6", offset) == 71 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("1 + (2 * 3) + (4 * (5 + 6))", offset) == 51 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("2 * 3 + (4 * 5)", offset) == 26 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("5 + (8 * 3 + 9 + 3 * 4 * 3)", offset) == 437 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))", offset) == 12240 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2", offset) == 13632 ? "true" : "false") << std::endl;

    // My examples

    *offset = 0;
    std::cout << (EvaluateExpression("((1 + 2) * (3 + (4 * (5 + 6))))", offset) == 141 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("((6 + 2 * 7 + 2 + 9 * 5) * 5 * 9 + (7 * 7)) * 9 * 2 * 6 + 4", offset) == 1633396 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("4 * (2 + 2)", offset) == 16 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("5 * 6 + (2 + 8 + 9 + (6 + 8 + 3) * 2) + 8", offset) == 110 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("(4 + (6 * 5) + 4 + 7 + 7) + (2 + 3) * 2", offset) == 114 ? "true" : "false") << std::endl;
    *offset = 0;
    std::cout << (EvaluateExpression("(5 * (3 * 2 * 2 + 4 + 4) + 6 * (8 + 6 * 3 + 6)) * (3 * 7 * (5 * 9 * 7 + 5 * 6 * 2) + 6) + 2 + 8 * ((9 + 5 + 4 + 8 * 5 * 4) + 3) * 5", offset) == 114 ? "true" : "false") << std::endl;
}


int main()
{
    std::cout << "Operation Order" << std::endl;

    //Tests();
    Part1("input.txt");
}