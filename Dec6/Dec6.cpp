#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

enum Directions : int
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
};

struct Position
{
    int x;
    int y;

    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }
};

int calculateVisitedPositions(
    const std::vector<std::vector<char>> &inputMap,
    Position guardPosition,
    bool bruteForceMode = false)
{
    bool outOfBounds = false;
    Directions currentDirection = Directions::UP;
    Position lastGuardPos = guardPosition;
    std::vector<Position> visitedPositions = {};
    int steps = 0;

    while (!outOfBounds && steps < 6000)
    {

        if (inputMap[guardPosition.x][guardPosition.y] == '#')
        {
            currentDirection = static_cast<Directions>((static_cast<int>(currentDirection) + 1) % 4);
            guardPosition = lastGuardPos;
        }

        if (!bruteForceMode)
        {
            if (std::find(visitedPositions.begin(), visitedPositions.end(), guardPosition) == visitedPositions.end())
            {
                visitedPositions.push_back(guardPosition);
            }
        }

        lastGuardPos = guardPosition;

        switch (currentDirection)
        {
        case Directions::UP:
            guardPosition.x -= 1;
            break;
        case Directions::RIGHT:
            guardPosition.y += 1;
            break;
        case Directions::DOWN:
            guardPosition.x += 1;
            break;
        default:
            guardPosition.y -= 1;
            break;
        }

        if (guardPosition.x < 0 || guardPosition.y < 0 || guardPosition.x >= inputMap.size() || guardPosition.y >= inputMap[guardPosition.x].size())
        {
            outOfBounds = true;
            break;
        }

        steps++;
    }

    return bruteForceMode ? steps : visitedPositions.size();
}

int calcMaxNumOfObs(const std::vector<std::vector<char>> &inputMap, Position &guardPos)
{
    int sum = 0;
    for (int i = 0; i < inputMap.size(); i++)
    {
        for (int j = 0; j < inputMap[i].size(); j++)
        {

            if (guardPos.x == i && guardPos.y == j)
                continue;

            if (i < 0 || j < 0 || i >= inputMap.size() || j >= inputMap[i].size())
                continue;

            std::vector<std::vector<char>> inputMapCopy = inputMap;

            inputMapCopy[i][j] = '#';

            if (calculateVisitedPositions(inputMapCopy, guardPos, true) >= 6000)
                sum++;
        }
    }

    return sum;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cout << argc << '\n';
        std::cout << "Usage: ./Dec6 <input_file> [OPTIONS=--with-conditional]\n";
        return 1;
    }

    const std::string inputFileName = argv[1];

    std::ifstream file(inputFileName);
    std::vector<std::vector<char>> inputMap = {};
    Position guardPosition = {0, 0};

    if (!file)
    {
        std::cout << "Unable to open file" << '\n';
        return 1;
    }

    char ch;
    int guardPositionX = 0;
    int guardPositionY = 0;
    while (file.get(ch))
    {
        if (ch == '\n')
        {
            inputMap.push_back({});
            guardPositionX++;
            guardPositionY = 0;
            continue;
        }

        if (ch == '^')
        {
            guardPosition = {guardPositionX, guardPositionY};
        }

        if (inputMap.empty())
            inputMap.push_back({});

        guardPositionY++;
        inputMap[inputMap.size() - 1].push_back(ch);
    }

    file.close();

    int visitedPositions = calculateVisitedPositions(inputMap, guardPosition);
    int maxPossibleNumberOfObstructions = calcMaxNumOfObs(inputMap, guardPosition);

    std::cout << "Visited positions: " << visitedPositions << '\n';
    std::cout << "Max possible number of obstructions: " << maxPossibleNumberOfObstructions << '\n';

    return 0;
}