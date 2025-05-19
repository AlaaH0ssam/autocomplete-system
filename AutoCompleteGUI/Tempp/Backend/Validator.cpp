
#include "Validator.h"
#include <cctype>
#include <set>
#include <iostream>

using namespace std;

string Validator::to_lower_case(const string& word) {
    string lower_word;
    for (char ch : word) {
        lower_word += tolower(ch);
    }
    return lower_word;
}

bool Validator::isEmpty(const string& word) {
    return word.empty();
}

bool Validator::LettersChecker(const string& word) {
    for (char ch : word) {
        if (!isalpha(ch)) return false;
    }
    return true;
}
bool Validator::InputValidator(const string& word) {
    string cleaned = CleaningInput(word);
    if (isEmpty(word)) {
        cerr << " Input is empty!" << endl;
        return false;
    }
    if (!LettersChecker(word)) {
        cerr << "Input contains invalid characters!" << endl;
        return false;
    }
    return true;
}
string Validator::CleaningInput(const string& word) {
    string cleaned_word;
    set<char> invalid_chars;

    for (char ch : word) {
        if (!isalpha(ch)) {
            invalid_chars.insert(ch);
            continue;
        }
        cleaned_word += ch;
    }
    return cleaned_word;
}

string Validator::cleanAndPrepare(const string& word) {
    string cleaned = CleaningInput(word);
    return to_lower_case(cleaned);
}
