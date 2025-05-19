#pragma once
#include"trie_node.h"
#include<vector>
#include<string>
#include "Validator.h"
class trie
{
private:
	trie_node* root;
	void dfs_helper(trie_node* node, string current_word, vector<string>& suggestions);
    unordered_map<string, int> global_frequency_map;
    bool deleteHelper(trie_node* node, const string& word, int depth);
public:
    trie();
    ~trie();
    void insert(const string& word, int freq);
    bool search(const string word);
    string to_lower_case(const string word);
    void load_from_file(const string& filename);
    vector<string> bfs(const string& prefix);
    vector<string> dfs(const string& prefix);
    void save_to_file(const string& filename);
    void dfs_save(trie_node* node, string current_word, ofstream& file);
    void deleteWord();
    void track_and_insert(const string& word);
    unordered_map<string, int> user_input_frequency;
    int get_frequency(const string& word) const;
    vector<pair<string, bool>> getSuggestions(trie& myTrie, const string& input, int& sortType);
    void highlightMatch(const vector<pair<string, bool>>& suggestions);
    void show_suggestions(trie& t, const string& prefix);
    void clear(trie_node* node);
    bool deleteWordGUI(const std::string& word);
    std::vector<std::string> getAllWords();
    //friend class DeleteScreen;
};


