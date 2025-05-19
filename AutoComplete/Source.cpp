#include "trie.h"
#include "Validator.h"
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    trie t;
    Validator validator;
    t.load_from_file("dictionary.txt");

    while (true) {
        cout << "\n--- Auto-Complete Menu ---\n\n";
        cout << "1. Search Word/Prefix\n";
        cout << "2. Insert a new word\n";
        cout << "3. Delete a word\n";
        cout << "4. Save and Exit\n";
        cout << "Enter your choice: ";

        int option;
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        string input;
        switch (option) {
        case 1: {
            cout << "Enter a word or prefix to search: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, input);

            if (validator.isEmpty(input)) {
                cout << "Input cannot be empty.\n";
                break;
            }
            if (!validator.InputValidator(input)) {
                cout << "Invalid input.\n";
                break;
            }

            string lower_input = validator.to_lower_case(input);

            t.track_and_insert(lower_input);
            t.show_suggestions(t, lower_input);
            break;
        }

        case 2:
            cout << "Enter word to insert: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, input);

            if (validator.isEmpty(input) || !validator.InputValidator(input)) {
                cout << "Invalid word.\n";
                break;
            }

            t.insert(validator.to_lower_case(input), 1);
            cout << "Inserted successfully.\n";
            break;

        case 3:
            t.deleteWord();
            break;

        case 4:
            t.save_to_file("dictionary.txt");
            cout << "Saved and exiting...\n";
            return 0;

        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}