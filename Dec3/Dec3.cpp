#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string_view>
#include <algorithm>

int addAllMulCalls(const std::vector<std::string> &mulFuncCalls)
{
    int sum = 0;
    for (const auto &mulFuncCall : mulFuncCalls)
    {
        std::string firstNum = "";
        std::string secondNum = "";
        int i = 4;
        while (i < mulFuncCall.size() - 1 && mulFuncCall[i] != ',')
        {
            firstNum = firstNum + mulFuncCall[i];
            i++;
        }
        i++;
        while (i < mulFuncCall.size() - 1)
        {
            secondNum = secondNum + mulFuncCall[i];
            i++;
        }

        if (firstNum.empty() || secondNum.empty())
        {
            std::cout << "Error: Invalid mul function call " << mulFuncCall << '\n';
            continue;
        }

        sum += std::stoi(firstNum) * std::stoi(secondNum);
    }
    return sum;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cout << argc << '\n';
        std::cout << "Usage: ./Dec3 <input_file> [OPTIONS=--with-conditional]\n";
        return 1;
    }

    const std::string inputFileName = argv[1];

    std::ifstream file(inputFileName);
    std::vector<std::string> mulFuncCalls = {};

    if (!file)
    {
        std::cout << "Unable to open file" << '\n';
        return 1;
    }

    bool withConditional = false;
    if (argc == 3)
        withConditional = std::string(argv[2]) == "--with-conditional";

    constexpr char mulFuncSequence[6] = {'m', 'u', 'l', '(', ',', ')'};
    constexpr char conditionalFalseSequence[7] = {'d', 'o', 'n', '\'', 't', '(', ')'};
    constexpr char conditionalTrueSequence[4] = {'d', 'o', '(', ')'};
    int nextMalFuncCharIndex = 0;
    int nextConditionalCharIndex = 0;
    std::string tmpString = "";
    std::string conditionalTmpString = "";
    bool readSequence = true;

    char ch;
    while (file.get(ch))
    {
        if (ch == conditionalFalseSequence[nextConditionalCharIndex] && withConditional)
        {
            conditionalTmpString += ch;
            nextConditionalCharIndex++;
            if (nextConditionalCharIndex == 7)
            {
                readSequence = false;
                nextConditionalCharIndex = 0;
                conditionalTmpString = "";
            }
        }
        else if (ch == conditionalTrueSequence[nextConditionalCharIndex] && withConditional)
        {
            conditionalTmpString += ch;
            nextConditionalCharIndex++;
            if (nextConditionalCharIndex == 4)
            {
                readSequence = true;
                nextConditionalCharIndex = 0;
                conditionalTmpString = "";
            }
        }

        if (readSequence)
        {

            if (std::find(std::begin(mulFuncSequence), std::end(mulFuncSequence), ch) == std::end(mulFuncSequence) && !std::isdigit(ch))
            {
                nextMalFuncCharIndex = 0;
                tmpString = "";
            }

            if (ch == mulFuncSequence[nextMalFuncCharIndex])
            {
                tmpString += ch;
                nextMalFuncCharIndex++;

                if (nextMalFuncCharIndex == 6)
                {
                    mulFuncCalls.push_back(tmpString);
                    nextMalFuncCharIndex = 0;
                    tmpString = "";
                }
            }
            if ((mulFuncSequence[nextMalFuncCharIndex - 1] == mulFuncSequence[3] || mulFuncSequence[nextMalFuncCharIndex - 1] == mulFuncSequence[4]) && std::isdigit(ch))
            {
                tmpString += ch;
            }
        }
    }

    file.close();

    const int sumOfAllMultiplications = addAllMulCalls(mulFuncCalls);

    std::cout << "Sum of all multiplications: " << sumOfAllMultiplications << '\n';

    return 0;
}