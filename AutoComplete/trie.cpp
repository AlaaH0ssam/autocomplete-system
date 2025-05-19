#include "trie.h"
#include"string"
#include<iostream>
#include <queue>
#include <fstream>
#include <stack>
#include <unordered_map>
#include "Validator.h"
#include <limits> 
#include <algorithm>

using namespace std;
Validator validator;

trie::trie() {
	root = new trie_node();
}

string trie::to_lower_case(const string word) {
	string lower_word;
	for (char ch : word) {
		lower_word += tolower(ch);
	}
	return lower_word;
}

void trie::insert(const string& word, int freq) {

	string lower_word = validator.cleanAndPrepare(word);
	if (lower_word.empty())
		return;

	trie_node* temp = root;

	for (char ch : lower_word) {
		if (temp->children.find(ch) == temp->children.end()) {
			temp->children[ch] = new trie_node();
		}
		temp = temp->children[ch];
	}

	temp->end_of_word = true;
	temp->frequency = freq;
}
//loop char char on the whole word if char not exit return false if char exit move to the next char chex if it is a word
bool trie::search(const string word) {
	if (!validator.InputValidator(word)) {
		return false;
	}
	string lower_word = validator.to_lower_case(word);
	trie_node* current = root;
	for (char ch : lower_word) {
		if (current->children.find(ch) == current->children.end()) {
			return false;
		}
		current = current->children[ch];
	}
	return current->end_of_word;
}
void trie::load_from_file(const string& Dictionary) {
	ifstream file(Dictionary);
	if (!file.is_open()) {
		cout << "Error: Could not open file: " << Dictionary << endl;
		return;
	}

	string word;
	int freq;
	while (file >> word >> freq) {
		if (validator.InputValidator(word)) {
			insert(word, freq);
			global_frequency_map[to_lower_case(word)] = freq;
		}
		else {
			cout << " Skipping invalid word in file: '" << word << endl;
		}
	}
	file.close();
}
vector<string> trie::bfs(const string& prefix) {
	vector<string> suggestions;
	string lower_prefix = validator.cleanAndPrepare(prefix);

	trie_node* current = root;

	// Navigate to the prefix node
	for (char ch : lower_prefix) {
		if (current->children.find(ch) == current->children.end())
			return suggestions;
		current = current->children[ch];
	}

	queue<pair<trie_node*, string>> q;
	q.push(make_pair(current, lower_prefix));

	while (!q.empty()) {
		pair<trie_node*, string> front = q.front();
		q.pop();

		trie_node* node = front.first;
		string word = front.second;

		if (node->end_of_word) {
			suggestions.push_back(word);
		}


		for (auto& it : node->children) {
			char ch = it.first;
			trie_node* child = it.second;
			q.push(make_pair(child, word + ch));
		}

	}

	return suggestions;
}


vector<string> trie::dfs(const string& prefix) {
	vector<string> suggestions;
	string lower_prefix = validator.to_lower_case(prefix);
	trie_node* current = root;

	for (char ch : lower_prefix) {
		if (current->children.find(ch) == current->children.end()) {
			return suggestions;
		}
		current = current->children[ch];
	}

	stack<pair<trie_node*, string>> st;
	st.push({ current, lower_prefix });

	while (!st.empty()) {
		pair<trie_node*, string> top_element = st.top();
		trie_node* node = top_element.first;
		string word = top_element.second;
		st.pop();

		if (node->end_of_word) {
			suggestions.push_back(word);
		}

		for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
			st.push({ it->second, word + it->first });
		}
	}

	return suggestions;
}

void trie::save_to_file(const string& filename) {
	ofstream file(filename);
	if (!file.is_open()) {
		cout << "Error: Could not open file for saving: " << filename << endl;
		return;
	}

	dfs_save(root, "", file);
	file.close();
}
void trie::dfs_save(trie_node* node, string current_word, ofstream& file) {
	stack<pair<trie_node*, string>> st;
	st.push({ node, current_word });

	while (!st.empty()) {
		pair<trie_node*, string> top_element = st.top();
		trie_node* current = top_element.first;
		string word = top_element.second;
		st.pop();

		if (current->end_of_word) {
			file << word << " " << current->frequency << endl;
		}

		//  lexicographic order 
		for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
			st.push({ it->second, word + it->first });
		}
	}
}

bool trie::deleteHelper(trie_node* node, const string& word, int depth) {
	if (!node) return false;

	if (depth == word.length()) {
		if (!node->end_of_word) {
			return false;
		}
		node->end_of_word = false;
		return node->children.empty();
	}

	char ch = tolower(word[depth]);
	auto it = node->children.find(ch);
	if (it == node->children.end())
		return false;

	bool shouldDelete = deleteHelper(it->second, word, depth + 1);
	if (shouldDelete) {
		delete it->second;
		node->children.erase(it);
		return node->children.empty() && !node->end_of_word;
	}

	return false;
}
void trie::deleteWord() {

	string input;
	int choice1;
	while (true) {
		cout << "Do you want to delete word by word or by prefix?\n"
			<< "1 - Word\n"
			<< "2 - Prefix\n";
		cin >> choice1;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice. Please enter 1 or 2.\n";
			continue;
		}

		if (choice1 == 1 || choice1 == 2)
			break;
		else
			cout << "Invalid choice. Please enter 1 or 2.\n";
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Enter a word or prefix to delete: ";
	getline(cin, input);
	if (validator.isEmpty(input)) {
		cout << "Input cannot be empty.\n";
		return;
	}
	if (!validator.InputValidator(input)) {
		return;
	}

	string deletedWord = validator.to_lower_case(input);
	vector<string> matches;

	if (choice1 == 1) {
		matches = dfs("");
		bool isExactWord = false;
		for (auto& word : matches) {
			if (word == deletedWord) {
				isExactWord = true;
				break;
			}
		}
		if (isExactWord) {
			deleteHelper(root, deletedWord, 0);
			cout << "Word: " << deletedWord << " deleted successfully\n" << endl;
		}
		else {
			cout << "Word not found.\n";
		}
	}
	else if (choice1 == 2) {
		matches = dfs(deletedWord);
		if (matches.empty()) {
			cout << "No words found with that prefix.\n";
			return;
		}

		cout << "Choose word to delete:\n";
		for (int i = 0; i < matches.size(); ++i)
			cout << i + 1 << ". " << matches[i] << endl;

		int choice2;
		while (true) {
			cout << "Enter the number of the word you want to delete: ";
			cin >> choice2;
			if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a valid number.\n";
			continue;
		}
		
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  

			if (choice2 >= 1 && choice2 <= matches.size()) {
				break;
			}
			else {
				cout << "Invalid choice. Please enter a number between 1 and " << matches.size() << ".\n";
			}
		}

		deleteHelper(root, matches[choice2 - 1], 0);
		cout << "Word: " << matches[choice2 - 1] << " deleted successfully\n" << endl;
	}
}
void trie::track_and_insert(const string& word) {
	string lower_word = to_lower_case(word);
	user_input_frequency[lower_word]++;

	//update the frequency
	if (search(lower_word)) {
		trie_node* current = root;
		for (char ch : lower_word) {
			current = current->children[ch];
		}
		current->frequency++;
	}
	//add after 3 times
	else if (user_input_frequency[lower_word] >= 3) {
		insert(lower_word, 1);
		cout << "New word '" << lower_word << "' added to dictionary after 3 searches.\n";
		user_input_frequency.erase(lower_word); //reset
	}
}
int trie::get_frequency(const std::string& word) const {
	auto it = global_frequency_map.find(word);
	if (it != global_frequency_map.end()) {
		return it->second;
	}
	return 0;
}
void trie::show_suggestions(trie& t, const string& prefix) {
	int choice;

	while (true) {
		cout << "Sort suggestions by:\n"
			<< "1. DFS (A-Z)\n"
			<< "2. BFS (Shortest words first)\n"
			<< "3. Most frequent first\n"
			<< "Enter option (1-3): ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number.\n";
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (choice >= 1 && choice <= 3) {
			break;
		}
		cout << "Invalid choice. Please enter 1, 2, or 3.\n";
	}

	vector<pair<string, bool>> suggestions = getSuggestions(t, prefix, choice);

	if (suggestions.empty()) {
		cout << "No suggestions found for '" << prefix << "'.\n";
	}
	else {
		highlightMatch(suggestions);
	}
}
vector<pair<string, bool>> trie::getSuggestions(trie& myTrie, const string& input, int& sortType) {
	vector<pair<string, bool>> result;

	bool isExactMatch = myTrie.search(input);
	vector<string> suggestions;

	if (sortType == 1) {
		suggestions = myTrie.dfs(input);
	}
	else if (sortType == 2) {
		suggestions = myTrie.bfs(input);
	}
	else if (sortType == 3) {
		suggestions = myTrie.bfs(input);
		sort(suggestions.begin(), suggestions.end(), [&](const string& a, const string& b) {
			return myTrie.get_frequency(a) > myTrie.get_frequency(b);
			});
	}

	for (const auto& word : suggestions) {
		result.push_back({ word, word == input });
	}
	return result;
}


void trie::highlightMatch(const vector<pair<string, bool>>& suggestions) {
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
trie::~trie() {
	clear(root);
}

void trie::clear(trie_node* node) {
	if (!node)
		return;
	for (auto& child : node->children) {
		clear(child.second);
	}
	delete node;
}
