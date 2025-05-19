#pragma once
#include <string>

using namespace std;

class Validator {
public:
    static string to_lower_case(const string& word);
    static bool isEmpty(const string& word);
    static bool LettersChecker(const string& word);
    static bool InputValidator(const string& word);
   static string CleaningInput(const string& word);
   static string cleanAndPrepare(const string& word);
};
