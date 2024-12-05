#ifndef SPLIT_H
#define SPLIT_H

#include <vector>
#include <string>

void getStringsSplitBySpaces(const std::string &str, std::vector<std::string> &splitUpStringArr);
void getStringsSplitByDelimiter(const std::string &str, std::vector<std::string> &splitUpStringArr, char delimiter);

#endif
