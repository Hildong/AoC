#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "../utils/Split.h"

int reportIsSafeWithDamper(std::vector<int> &levels)
{
    for (int i = 0; i < levels.size() + 1; i++)
    {
        std::vector<int> levelsCopy = levels;

        if (i > 0)
            levelsCopy.erase(levelsCopy.begin() + i - 1);

        std::set<int> noneDuplicatesSet(levelsCopy.begin(), levelsCopy.end());

        if (noneDuplicatesSet.size() != levelsCopy.size() || levelsCopy.size() == 0)
        {
            continue;
        }

        if (!(std::is_sorted(levelsCopy.begin(), levelsCopy.end()) || std::is_sorted(levelsCopy.begin(), levelsCopy.end(), std::greater<>())))
        {
            continue;
        }

        int prevValue = levelsCopy[0];
        bool differenceMatchesCriteria = true;

        for (int i = 1; i < levelsCopy.size(); i++)
        {
            int difference = std::abs(std::max(prevValue, levelsCopy[i]) - std::min(prevValue, levelsCopy[i]));
            if (difference < 1 || difference > 3)
            {
                differenceMatchesCriteria = false;
            }
            prevValue = levelsCopy[i];
        }

        if (differenceMatchesCriteria)
        {
            return 1;
        }
    }

    return 0;
}

int reportIsSafe(std::vector<int> &levels)
{
    std::set<int> noneDuplicatesSet(levels.begin(), levels.end());

    if (noneDuplicatesSet.size() != levels.size() || levels.size() == 0)
    {
        return 0;
    }

    if (!(std::is_sorted(levels.begin(), levels.end()) || std::is_sorted(levels.begin(), levels.end(), std::greater<>())))
    {
        return 0;
    }

    int prevValue = levels[0];

    for (int i = 1; i < levels.size(); i++)
    {
        int difference = std::abs(std::max(prevValue, levels[i]) - std::min(prevValue, levels[i]));
        if (difference < 1 || difference > 3)
        {
            return 0;
        }
        prevValue = levels[i];
    }

    return 1;
}

int main(int argc, char *argv[])
{

    if (argc < 2 || argc > 3)
    {

        std::cout << argc << '\n';
        std::cout << "Usage: ./Dec2 <input_file> [OPTIONS=--with-damper]\n";
        return 1;
    }

    const std::string inputFileName = argv[1];

    std::ifstream file(inputFileName);
    std::string line;
    std::vector<std::vector<int>> reportsVector;

    if (file.is_open())
    {
        std::string fileLine;
        int iterator = 0;
        while (getline(file, fileLine))
        {
            std::vector<std::string> splitUpStringArr;

            getStringsSplitBySpaces(fileLine, splitUpStringArr);

            reportsVector.push_back(std::vector<int>());
            for (int level = 0; level < splitUpStringArr.size(); level++)
            {
                reportsVector[iterator].push_back(std::stoi(splitUpStringArr[level]));
            }
            iterator++;
        }

        file.close();
    }

    int safeReports = 0;
    for (int i = 0; i < reportsVector.size(); i++)
    {
        if (argc == 3 && std::string(argv[2]) == "--with-damper")
            safeReports += reportIsSafeWithDamper(reportsVector[i]);
        else
            safeReports += reportIsSafe(reportsVector[i]);
    }

    std::cout << "Safe Reports: " << safeReports << '\n';

    return 0;
}