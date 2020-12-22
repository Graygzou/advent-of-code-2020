// Day18-OperationOrder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

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

std::string AddParenthesis(std::string expression, char ope)
{
    std::map<int, int> lastOperandsIndexes = std::map<int, int>();
    std::vector<int> rightParenthesis = std::vector<int>();
    int currentLevel = 0;

    for (size_t i = 0; i < expression.size(); i++)
    {
        if (expression[i] != ' ' && expression[i] != '*')
        {
            if (expression[i] == ope)
            {
                // 1.
                if (lastOperandsIndexes.find(currentLevel + 1) == lastOperandsIndexes.end())
                {
                    lastOperandsIndexes.insert(std::make_pair(currentLevel + 1, lastOperandsIndexes[currentLevel]));
                }
                else
                {
                    lastOperandsIndexes[currentLevel + 1] = lastOperandsIndexes[currentLevel];
                }

                // 2.
                expression.insert(lastOperandsIndexes[currentLevel], "(");
                i++;

                // 3. Update level
                currentLevel++;

                // 4.
                rightParenthesis.push_back(currentLevel);
            }
            else if (expression[i] == '(')
            {
                // 1. Update the last operand met
                if (lastOperandsIndexes.find(currentLevel) == lastOperandsIndexes.end())
                {
                    lastOperandsIndexes.insert(std::make_pair(currentLevel, i));
                }
                else
                {
                    lastOperandsIndexes[currentLevel] = i;
                }

                // 2. Update level
                currentLevel++;
            }
            else if (expression[i] == ')')
            {
                // 1. Update level
                currentLevel--;

                // 2. Add right parenthesis if we should
                auto it = find(rightParenthesis.begin(), rightParenthesis.end(), currentLevel);
                if (it != rightParenthesis.end())
                {
                    rightParenthesis.erase(it);
                    expression.insert(i+1, ")");
                }
            }
            else
            {
                // 1. Update the last operand met
                if (lastOperandsIndexes.find(currentLevel) == lastOperandsIndexes.end())
                {
                    lastOperandsIndexes.insert(std::make_pair(currentLevel, i));
                }
                else
                {
                    lastOperandsIndexes[currentLevel] = i;
                }
               
                // 2. Add right parenthesis if we should
                auto it = find(rightParenthesis.begin(), rightParenthesis.end(), currentLevel);
                if (it != rightParenthesis.end())
                {
                    rightParenthesis.erase(it);
                    expression.insert(i + 1, ")");
                }
            }

            //std::cout << "index of i " << i << std::endl;
/* for (auto it = indexes.begin(); it != indexes.end(); ++it)
     std::cout << it->first << " => " << it->second << '\n';*/
        }
    }

    return expression;
}

unsigned long long EvaluateExpressionPart2(std::string expression, int* offset)
{
    // Apply parenthesis to prioritise additions
    expression = AddParenthesis(expression, '+');

    return EvaluateExpressionPart2(expression, offset);
}

// 145610164171889 => too high
// 140338487202656 => too low


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
            line = AddParenthesis(line, '+');
            std::cout << line << std::endl;

            *offset = 0;
            unsigned long long currentResult = EvaluateExpression(line, offset);
            //std::cout << "Current Result is " << currentResult << std::endl;

            part1Result += currentResult;

            //std::cout << "Cumulated result is " << part1Result << std::endl;
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

void TestPart2()
{
    //std::cout << AddParenthesis("4 * 2 + 2", '+') << std::endl;
    //std::cout << AddParenthesis("4 * (2 + 2)", '+') << std::endl;
    //std::cout << AddParenthesis("3 + (4 * (2 + 2))", '+') << std::endl;
    //std::cout << AddParenthesis("4 * 2 * 1", '+') << std::endl;
    std::cout << AddParenthesis("2 + (3 + 3 + (9 + 3 * 4 * 9) + 2 + 5 * 7) * 7 * (3 * 6 * 5 * 9 + 6) + 6", '+') << std::endl;

    //int* offset = new int(0);
    //std::cout << (EvaluateExpression(AddParenthesis("1 + 2 * 3 + 4 * 5 + 6", '+'), offset) == 231 ? "true" : "false") << std::endl;
    //*offset = 0;
    ////std::cout << AddParenthesis("1 + (2 * 3) + (4 * (5 + 6))", '+') << std::endl;
    ////std::cout << (EvaluateExpression(AddParenthesis("1 + (2 * 3) + (4 * (5 + 6))", '+'), offset)) << std::endl;
    //std::cout << (EvaluateExpression(AddParenthesis("1 + (2 * 3) + (4 * (5 + 6))", '+'), offset) == 51 ? "true" : "false") << std::endl;
    //*offset = 0;
    ////std::cout << AddParenthesis("2 * 3 + (4 * 5)", '+') << std::endl;
    //std::cout << (EvaluateExpression(AddParenthesis("2 * 3 + (4 * 5)", '+'), offset) == 46 ? "true" : "false") << std::endl;
    //*offset = 0;
    //std::cout << (EvaluateExpression(AddParenthesis("5 + (8 * 3 + 9 + 3 * 4 * 3)", '+'), offset) == 1445 ? "true" : "false") << std::endl;
    //*offset = 0;
    //std::cout << (EvaluateExpression(AddParenthesis("5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))", '+'), offset) == 669060 ? "true" : "false") << std::endl;
    //*offset = 0;
    //std::cout << (EvaluateExpression(AddParenthesis("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2", '+'), offset) == 23340 ? "true" : "false") << std::endl;
    //*offset = 0;
    //std::cout << EvaluateExpression(AddParenthesis("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2", '+'), offset) << std::endl;


    std::cout << AddParenthesis("(2 + 4 * 9)", '+') << std::endl;
    std::cout << AddParenthesis("((2 + 4 * 9) + 6)", '+') << std::endl;
    std::cout << AddParenthesis("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2", '+') << std::endl;
    std::cout << AddParenthesis("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2", '+') << std::endl;
    std::cout << AddParenthesis("5 + (8 * 3 + 9 + 3 * 4 * 3)", '+') << std::endl;
}

int main()
{
    std::cout << "Operation Order" << std::endl;

    //TestPart2();
    Part1("input.txt");
}