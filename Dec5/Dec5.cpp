#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include "../utils/Split.h"
#include <algorithm>
#include <deque>

int runPageUpdates(
    std::unordered_map<int, std::vector<int>> &pageOrderingMap,
    std::vector<std::vector<int>> &updates,
    std::vector<std::vector<int>> &uncorrectOrderedUpdates)
{
    int sum = 0;
    int numOfUnorderedUpdates = 0;

    for (int i = 0; i < updates.size(); i++)
    {
        std::vector<int> printedPages = {};
        bool printedInOrder = true;
        for (int j = 0; j < updates[i].size(); j++)
        {

            if (pageOrderingMap.find(updates[i][j]) == pageOrderingMap.end())
            {
                printedPages.push_back(updates[i][j]);
                continue;
            }

            std::vector<int> pageOrdering = pageOrderingMap.find(updates[i][j])->second;

            for (auto page : pageOrdering)
            {
                if (std::find(std::begin(printedPages), std::end(printedPages), page) != std::end(printedPages))
                {
                    if (printedInOrder)
                        uncorrectOrderedUpdates.push_back(std::vector<int>());

                    printedInOrder = false;
                    uncorrectOrderedUpdates[uncorrectOrderedUpdates.size() - 1] = updates[i];
                    break;
                }
            }

            printedPages.push_back(updates[i][j]);
        }

        if (!printedPages.empty() && printedInOrder)
        {
            int middleIndex = printedPages.size() / 2;

            sum += printedPages[middleIndex];
        }
    }

    return sum;
}

int runPageUpdatesOnUncorrectOrders(
    std::unordered_map<int, std::vector<int>> &pageOrderingMap,
    std::vector<std::vector<int>> &uncorrectOrderedUpdates)
{
    int sum = 0;
    std::vector<std::vector<int>> orderedUpdates;

    for (int i = 0; i < uncorrectOrderedUpdates.size(); i++)
    {
        orderedUpdates.push_back(std::vector<int>());
        std::vector<int> pages = uncorrectOrderedUpdates[i];
        std::vector<int> pagesWithoutRule = {};

        int pagesIndex = 0;
        bool foundNextSorted = true;
        while (!pages.empty())
        {

            if (pageOrderingMap.find(pages[pagesIndex]) == pageOrderingMap.end())
            {
                pagesWithoutRule.push_back(pages[pagesIndex]);
                pages.erase(pages.begin() + pagesIndex);
                pagesIndex = 0;
                continue;
            }

            for (int j = 0; j < pages.size(); j++)
            {
                if (pageOrderingMap.find(pages[j]) == pageOrderingMap.end() || pages[j] == pages[pagesIndex])
                    continue;

                std::vector<int> pageOrdering = pageOrderingMap.find(pages[j])->second;

                if (std::find(std::begin(pageOrdering), std::end(pageOrdering), pages[pagesIndex]) != std::end(pageOrdering))
                {
                    pagesIndex++;
                    foundNextSorted = false;
                    break;
                }
            }

            if (foundNextSorted)
            {
                orderedUpdates[orderedUpdates.size() - 1].push_back(pages[pagesIndex]);
                pages.erase(pages.begin() + pagesIndex);

                pagesIndex = 0;
            }
            else
            {
                foundNextSorted = true;
            }
        }

        for (int j = 0; j < pagesWithoutRule.size(); j++)
        {
            orderedUpdates[orderedUpdates.size() - 1].push_back(pagesWithoutRule[j]);
        }
    }

    sum = runPageUpdates(pageOrderingMap, orderedUpdates, uncorrectOrderedUpdates);
    return sum;
}

void handleFileLine(
    std::string &fileLine,
    std::unordered_map<int, std::vector<int>> &pageOrderingMap,
    std::vector<std::vector<int>> &updates)
{

    if (fileLine.empty())
    {
        return;
    }

    if (fileLine.find("|") != std::string::npos)
    {
        std::vector<std::string> splitUpStringArr = {};
        getStringsSplitByDelimiter(fileLine, splitUpStringArr, '|');

        const int key = std::stoi(splitUpStringArr[0]);
        const int value = std::stoi(splitUpStringArr[1]);

        pageOrderingMap[key].push_back(value);
    }
    else if (fileLine.find(",") != std::string::npos)
    {
        std::vector<std::string> splitUpStringArr = {};
        getStringsSplitByDelimiter(fileLine, splitUpStringArr, ',');
        updates.push_back(std::vector<int>());

        for (const auto &update : splitUpStringArr)
        {
            updates[updates.size() - 1].push_back(std::stoi(update));
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cout << argc << '\n';
        std::cout << "Usage: ./Dec5 <input_file> [OPTIONS=--with-conditional]\n";
        return 1;
    }

    const std::string inputFileName = argv[1];

    std::ifstream file = std::ifstream(inputFileName);
    std::unordered_map<int, std::vector<int>> pageOrderingMap = {};
    std::vector<std::vector<int>> updates;
    std::vector<std::vector<int>> uncorrectOrderedUpdates;

    if (!file)
    {
        std::cout << "Unable to open file" << '\n';
        return 1;
    }

    if (file.is_open())
    {
        std::string fileLine;
        int iterator = 0;
        while (getline(file, fileLine))
        {
            handleFileLine(fileLine, pageOrderingMap, updates);
        }

        file.close();
    }

    const int sum = runPageUpdates(pageOrderingMap, updates, uncorrectOrderedUpdates);
    const int sumWithCorrectOrder = runPageUpdatesOnUncorrectOrders(pageOrderingMap, uncorrectOrderedUpdates);

    std::cout << "Sum of all printed pages: " << sum << '\n';
    std::cout << "Sum of all unordered printed pages after ordering: " << sumWithCorrectOrder << '\n';

    return 0;
}