 #pragma once
#include <string>
#include "trie.h"

vector<pair<string, bool>> getSuggestions(trie& myTrie, const std::string& input, int& sortType);
void highlightMatch(const vector<pair<string, bool>>& suggestions);
void promptUser(std::string& input, int& sortType);