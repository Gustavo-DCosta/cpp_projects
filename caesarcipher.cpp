#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Encrypt/Decrypt text using Caesar cipher
string encrypt(const string &text, int shift) {
    string result;
    for (char c : text) {
        if (isupper(c)) {
            result += char((c - 'A' + shift + 26) % 26 + 'A');
        } else if (islower(c)) {
            result += char((c - 'a' + shift + 26) % 26 + 'a');
        } else {
            result += c; // Non-alphabetic characters remain unchanged
        }
    }
    return result;
}

// Open and read file content
string read_file(const string &file_path) {
    ifstream MyReadFile(file_path);
    if (!MyReadFile) {
        cerr << "Error: Unable to open file at " << file_path << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(MyReadFile)), istreambuf_iterator<char>());
    MyReadFile.close();
    return content;
}

// Handle encoding or decoding based on user choice
void process_choice(int main_choice) {
    string choice, text, file_path;
    int shift = 3;

    cout << "!!Attention, shift value is 3!!" << endl;

    cout << "Do you want to encode/decode file content or text? (filecontent/text): ";
    cin >> choice;
    cin.ignore(); // Clear leftover newline

    if (choice == "filecontent") {
        cout << "Enter the file path: ";
        getline(cin, file_path);

        string content = read_file(file_path);
        if (content.empty()) return;

        if (main_choice == 2) shift = -shift; // Reverse shift for decoding

        string result = encrypt(content, shift);
        cout << "Processed file content:\n" << result << endl;
    } else if (choice == "text") {
        cout << "Enter the text: ";
        getline(cin, text);

        if (main_choice == 2) shift = -shift; // Reverse shift for decoding

        string result = encrypt(text, shift);
        cout << "Processed text:\n" << result << endl;
    } else {
        cerr << "Invalid choice!" << endl;
    }
}

int main() {
    int main_choice;
    cout << "Press 1 to encode\nPress 2 to decode:\n";
    cin >> main_choice;

    if (main_choice == 1 || main_choice == 2) {
        process_choice(main_choice);
    } else {
        cerr << "Invalid choice!" << endl;
    }

    return 0;
}
