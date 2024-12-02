#include "Split.h"
#include <vector>
#include <string>

void getStringsSplitBySpaces(const std::string &str, std::vector<std::string> &splitUpStringArr)
{
    std::string word;

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '\n')
            break;

        if (str[i] == ' ')
        {
            if (!word.empty())
            {
                splitUpStringArr.push_back(word);
                word.clear();
            }
        }
        else
        {
            word += str[i];
        }
    }

    if (!word.empty())
    {
        splitUpStringArr.push_back(word);
        word.clear();
    }
}
