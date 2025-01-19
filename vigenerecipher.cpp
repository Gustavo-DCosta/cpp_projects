#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Function to extend the key to match the length of the text
string extendKey(const string& text, const string& key) {
    string extendedKey;
    int keyLength = key.length();
    int textLength = text.length();

    for (int i = 0; i < textLength; i++) {
        extendedKey += key[i % keyLength];
    }
    return extendedKey;
}

// Function to encode using the Vigenère cipher
string vigenereEncode(const string& text, const string& key) {
    string extendedKey = extendKey(text, key);
    string encodedText;

    for (size_t i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            encodedText += (text[i] - base + (extendedKey[i] - base)) % 26 + base;
        } else {
            encodedText += text[i]; // Keep non-alphabetic characters unchanged
        }
    }
    return encodedText;
}

// Function to decode using the Vigenère cipher
string vigenereDecode(const string& text, const string& key) {
    string extendedKey = extendKey(text, key);
    string decodedText;

    for (size_t i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            decodedText += (text[i] - base - (extendedKey[i] - base) + 26) % 26 + base;
        } else {
            decodedText += text[i]; // Keep non-alphabetic characters unchanged
        }
    }
    return decodedText;
}

// Function to read text from a file
string readFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        exit(EXIT_FAILURE);
    }
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return text;
}

// Function to write text to a file
void writeFile(const string& filePath, const string& text) {
    ofstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        exit(EXIT_FAILURE);
    }
    file << text;
    file.close();
}

int main() {
    int choice;
    cout << "Vigenère Cipher Program\n";
    cout << "1. Encode text\n";
    cout << "2. Decode text\n";
    cout << "Select an option (1 or 2): ";
    cin >> choice;

    cin.ignore(); // Clear newline character left by cin
    string key;
    cout << "Enter the key: ";
    getline(cin, key);

    for (auto& ch : key) {
        if (!isalpha(ch)) {
            cerr << "Error: Key must only contain alphabetic characters.\n";
            return 1;
        }
    }

    int inputChoice;
    cout << "Input source:\n";
    cout << "1. File\n";
    cout << "2. Direct input\n";
    cout << "Select an option (1 or 2): ";
    cin >> inputChoice;

    cin.ignore(); // Clear newline character left by cin
    string text;
    if (inputChoice == 1) {
        string filePath;
        cout << "Enter the file path: ";
        getline(cin, filePath);
        text = readFile(filePath);
    } else if (inputChoice == 2) {
        cout << "Enter the text: ";
        getline(cin, text);
    } else {
        cerr << "Invalid input choice.\n";
        return 1;
    }

    string result;
    if (choice == 1) {
        result = vigenereEncode(text, key);
    } else if (choice == 2) {
        result = vigenereDecode(text, key);
    } else {
        cerr << "Invalid choice.\n";
        return 1;
    }

    int outputChoice;
    cout << "Output destination:\n";
    cout << "1. File\n";
    cout << "2. Display on screen\n";
    cout << "Select an option (1 or 2): ";
    cin >> outputChoice;

    if (outputChoice == 1) {
        string filePath;
        cout << "Enter the output file path: ";
        cin.ignore(); // Clear newline character
        getline(cin, filePath);
        writeFile(filePath, result);
        cout << "Operation completed. Output saved to " << filePath << endl;
    } else if (outputChoice == 2) {
        cout << "Result:\n" << result << endl;
    } else {
        cerr << "Invalid output choice.\n";
        return 1;
    }

    return 0;
}