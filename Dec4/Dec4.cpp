#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string_view>
#include <algorithm>
#include <set>

struct possibleWordDirection
{
    int x;
    int y;
    int timesToStep = 3;
};

int calculateXDashMasCount(
    const std::vector<std::vector<char>> &characterGridVector,
    std::string targetWord)
{
    int wordCount = 0;
    std::string reversedWord = targetWord;
    std::reverse(reversedWord.begin(), reversedWord.end());

    for (int i = 0; i < characterGridVector.size(); i++)
    {
        for (int j = 0; j < characterGridVector[i].size(); j++)
        {

            if (characterGridVector[i][j] == 'A')
            {

                int xBack = i - 1;
                int yBack = j - 1;
                int xForward = i + 1;
                int yForward = j + 1;

                if (xBack < 0 || yBack < 0 || xForward >= characterGridVector.size() || yForward >= characterGridVector[xForward].size())
                    continue;

                std::string diagWord1 = std::string(1, characterGridVector[xBack][yBack]) + 'A' + std::string(1, characterGridVector[xForward][yForward]);
                std::string diagWord2 = std::string(1, characterGridVector[xBack][yForward]) + 'A' + std::string(1, characterGridVector[xForward][yBack]);

                bool diagWord1Match = diagWord1 == targetWord || diagWord1 == reversedWord;
                bool diagWord2Match = diagWord2 == targetWord || diagWord2 == reversedWord;

                if (diagWord1Match && diagWord2Match)
                {
                    wordCount++;
                }
            }
        }
    }

    return wordCount;
}

int calculateXmasCount(
    const std::vector<std::vector<char>> &characterGridVector,
    const possibleWordDirection (&possibleWordDirections)[4],
    std::string targetWord)
{
    int wordCount = 0;

    for (int i = 0; i < characterGridVector.size(); i++)
    {
        for (int j = 0; j < characterGridVector[i].size(); j++)
        {
            std::string word = targetWord;
            if (characterGridVector[i][j] != word[0] && characterGridVector[i][j] != word[targetWord.size() - 1])
                continue;

            for (auto direction : possibleWordDirections)
            {
                int iteration = 0;
                int xDir = i;
                int yDir = j;
                int posSum = 0;

                if (characterGridVector[i][j] == word[targetWord.size() - 1])
                    std::reverse(word.begin(), word.end());

                std::string tmpStr = std::string(1, word[0]);

                while (iteration < direction.timesToStep)
                {
                    iteration++;
                    xDir = direction.x ? xDir + direction.x : xDir;
                    yDir = direction.y ? yDir + direction.y : yDir;

                    if (xDir < 0 || yDir < 0 || xDir >= characterGridVector.size() || yDir >= characterGridVector[xDir].size())
                        break;

                    if (characterGridVector[xDir][yDir] == word[iteration])
                    {
                        tmpStr += characterGridVector[xDir][yDir];
                        posSum += xDir + yDir;
                    }
                }

                if (tmpStr == word)
                {
                    wordCount++;
                }
            }
        }
    }

    return wordCount;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << argc << '\n';
        std::cout << "Usage: ./Dec4 <input_file> \n";
        return 1;
    }

    const std::string inputFileName = argv[1];
    std::ifstream file(inputFileName);
    std::vector<std::vector<char>> characterGridVector = {};

    if (!file)
    {
        std::cout << "Unable to open file" << '\n';
        return 1;
    }

    char ch;
    int iterator = 0;
    while (file.get(ch))
    {
        if (ch == '\n')
        {
            iterator++;
            characterGridVector.push_back({});
            continue;
        }

        if (characterGridVector.empty())
            characterGridVector.push_back({});

        characterGridVector[iterator].push_back(ch);
    }

    file.close();

    constexpr possibleWordDirection allWordDirections[4] = {
        {1, 0},
        {1, 1},
        {0, 1},
        {1, -1},
    };

    int xmasCount = calculateXmasCount(characterGridVector, allWordDirections, "XMAS");
    int xDashMasCount = calculateXDashMasCount(characterGridVector, "MAS");

    std::cout << "XMAS Count: " << xmasCount << '\n';
    std::cout << "X-MAS Count: " << xDashMasCount << '\n';

    return 0;
}