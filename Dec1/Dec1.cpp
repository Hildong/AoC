#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <unordered_map>
#include "../utils/Split.h"

// Part 1
void calculateDistance(std::vector<int> &lListVector, std::vector<int> &rListVector)
{
    int distance = 0;
    std::vector<int> lListVectorCopy = lListVector;
    std::vector<int> rListVectorCopy = rListVector;

    while (lListVectorCopy.size() > 0 && rListVectorCopy.size() > 0)
    {
        std::make_heap(lListVectorCopy.begin(), lListVectorCopy.end(), std::greater<>());
        std::make_heap(rListVectorCopy.begin(), rListVectorCopy.end(), std::greater<>());

        pop_heap(lListVectorCopy.begin(), lListVectorCopy.end(), std::greater<>());
        pop_heap(rListVectorCopy.begin(), rListVectorCopy.end(), std::greater<>());

        distance += std::abs(std::max(lListVectorCopy.back(), rListVectorCopy.back()) - std::min(lListVectorCopy.back(), rListVectorCopy.back()));

        lListVectorCopy.pop_back();
        rListVectorCopy.pop_back();
    }

    std::cout << "Distance: " << distance << '\n';
}

// Part 2
void calculateSimilarityPoints(std::vector<int> &lListVector, std::vector<int> &rListVector)
{
    int similarityPoints = 0;
    std::unordered_map<std::string, int> rListMap;

    for (int i = 0; i < rListVector.size(); i++)
    {
        rListMap[std::to_string(rListVector[i])] += 1;
    }

    for (int i = 0; i < lListVector.size(); i++)
    {
        int timesCurrentNumIsInRList = 0;

        if (rListMap.find(std::to_string(lListVector[i])) != rListMap.end())
            timesCurrentNumIsInRList = rListMap[std::to_string(lListVector[i])];

        similarityPoints += timesCurrentNumIsInRList * lListVector[i];
    }

    std::cout << "Similarity Points: " << similarityPoints << '\n';
}

int main(int argc, char *argv[])
{

    if (argc < 2 || argc > 3)
    {
        std::cerr << "Usage: " << argv[0] << " <inputfile.extension> \n";
        std::cerr << "or\n";
        std::cerr << "Usage: " << argv[0] << " <inputfile.extension> <inputfile.extension> \n";
        return 1;
    }

    const std::string inputFileName = argv[1];

    std::ifstream file(inputFileName);
    std::string line;

    std::vector<int> lListVector;
    std::vector<int> rListVector;

    if (file.is_open())
    {
        std::string fileLine;
        while (getline(file, fileLine))
        {
            std::vector<std::string> splitUpStringArr;

            getStringsSplitBySpaces(fileLine, splitUpStringArr);

            if (splitUpStringArr.size() > 2 || splitUpStringArr.size() < 1)
            {
                std::cerr << "Inputfile is invalid. Maximum 2 and Minimum 1 string separated by spaces per line!\n";
                return 1;
            }

            lListVector.push_back(std::stoi(splitUpStringArr[0]));
            if (splitUpStringArr.size() == 2)
                rListVector.push_back(std::stoi(splitUpStringArr[1]));
        }
        file.close();
    }

    calculateDistance(lListVector, rListVector);

    if (argc == 3)
    {
        calculateSimilarityPoints(lListVector, rListVector);
    }

    return 0;
}