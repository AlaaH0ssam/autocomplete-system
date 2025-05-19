#pragma once
#include<map>
#include<iostream>
using namespace std;
class trie_node
{
public:
	map<char, trie_node*>children;
	bool end_of_word;
	int frequency;
	trie_node();
};