
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
    set<char> invalid_chars;
    string cleaned = CleaningInput(word, invalid_chars);
    if (isEmpty(word)) {
        cerr << " Input is empty!" << endl;
        return false;
    }
    if (!invalid_chars.empty()) {
        cerr << "Input contains invalid characters: ";
        for (char ch : invalid_chars) {
            cerr << ch << ' ';
        }
        cerr << endl;
        return false;
    }
    return true;
}
string Validator::CleaningInput(const string& word, set<char>& invalid_chars) {
    string cleaned_word;
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
    set<char> invalid_chars;
    string cleaned = CleaningInput(word, invalid_chars);
    return to_lower_case(cleaned);
}
