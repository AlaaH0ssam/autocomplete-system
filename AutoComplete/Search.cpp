#include "Search.h"
#include "trie.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<pair<string, bool>> getSuggestions(trie& myTrie, const string& input, int& sortType) {
    vector<pair<string, bool>> result;

    bool isExactMatch = myTrie.search(input);
    vector<string> suggestions;


    if (sortType == 1) {
        suggestions = myTrie.dfs(input);
    }
    else if (sortType == 2) {
        suggestions = myTrie.bfs(input);
    }
    /* else if (sortType == 3) {
        suggestions = myTrie.mostFrequent(input);
    }
     */
    else {
        cout << "Invalid choice, defaulting to alphabetical. \n";
        suggestions = myTrie.dfs(input);

    }


    for (const auto& word : suggestions) {
        bool match = (word == input && isExactMatch);
        result.push_back({ word, match });
    }

    return result;
}

void highlightMatch(const vector<pair<string, bool>>& suggestions) {
    if (!suggestions.empty()) {
        cout << "Suggestions:\n";
        for (const auto& pair : suggestions) {
            string word = pair.first;
            bool isExact = pair.second;

            cout << word;
            if (isExact) {
                cout << " <-- exact match";
            }
            cout << '\n';
        }
    }
    else {
        cout << "No suggestions found.\n";
    }
}
void promptUser(std::string& input, int& sortType) {
    cout << "Enter prefix to search: ";
    cin >> input;

    cout << "Choose sorting type: \n";
    cout << "1. Alphabetical (A-Z)\n";
    cout << "2. Shortest words first. \n";
    cout << "3. Most frequent first. \n";
    cout << "Enter option number (1-3): ";

    cin >> sortType;

}