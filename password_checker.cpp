#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For std::find
using namespace std;

// Function to check password strength
void check_strenght(const string& password, const vector<char>& alphabet_list, 
                    const vector<char>& special_characters_list, const vector<char>& numbers_list) {
    bool has_letter = false;
    bool has_special = false;
    bool has_number = false;

    // Check if the password contains at least one letter, special character, and number
    for (char ch : password) {
        if (find(alphabet_list.begin(), alphabet_list.end(), ch) != alphabet_list.end()) {
            has_letter = true;
        } else if (find(special_characters_list.begin(), special_characters_list.end(), ch) != special_characters_list.end()) {
            has_special = true;
        } else if (find(numbers_list.begin(), numbers_list.end(), ch) != numbers_list.end()) {
            has_number = true;
        }
    }

    // Assess password strength
    if (password.size() >= 5 && password.size() <= 7) {
        cout << "The password is easily crackable.\n";
    } else if (password.size() >= 10 && has_letter && has_special && has_number) {
        cout << "The password is very strong.\n";
    } else if (password.size() >= 10) {
        cout << "The password is strong, but it could be better with a mix of letters, numbers, and special characters.\n";
    } else {
        cout << "The password is medium strength.\n";
    }
}

int main() {
    // Create alphabet list
    vector<char> alphabet_list;
    for (char c = 'A'; c <= 'Z'; ++c) {
        alphabet_list.push_back(c); // Add uppercase letters
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        alphabet_list.push_back(c); // Add lowercase letters
    }

    // Create special characters list
    vector<char> special_characters_list = {'\'', '-', '&', '_', '!', ':', ';', ',', '*', '$', '^'};

    // Create numbers list
    vector<char> numbers_list;
    for (char c = '0'; c <= '9'; ++c) {
        numbers_list.push_back(c);
    }

    // Ask for password input
    string password;
    do {
        cout << "Please insert your password (at least 5 characters): ";
        cin >> password;

        if (password.size() < 5) {
            cout << "Password too short. Try again.\n";
        }
    } while (password.size() < 5); // Loop until password is at least 5 characters

    // Check password strength
    check_strenght(password, alphabet_list, special_characters_list, numbers_list);

    return 0;
}
