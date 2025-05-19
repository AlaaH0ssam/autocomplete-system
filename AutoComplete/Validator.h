#pragma once
#include <string>
#include <set>
using namespace std;

class Validator {
private:
    static bool LettersChecker(const string& word);
    static string CleaningInput(const string& word, set<char>& invalid_chars);

public:
    static string to_lower_case(const string& word);
    static bool isEmpty(const string& word);
    static bool InputValidator(const string& word);
    static string cleanAndPrepare(const string& word);
};
