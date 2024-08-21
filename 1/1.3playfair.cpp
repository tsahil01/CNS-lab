#include <bits/stdc++.h>

using namespace std;

// Function to generate the key matrix
vector<vector<char>> generateKeyMatrix(const string& key) {
    string filteredKey;
    vector<vector<char>> matrix(5, vector<char>(5));
    vector<bool> used(26, false);

    // Process the key
    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';  // Treat 'J' as 'I'
        if (isalpha(c) && !used[c - 'A']) {
            filteredKey += c;
            used[c - 'A'] = true;
        }
    }

    // Fill filteredKey with remaining letters
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            filteredKey += c;
        }
    }

    // Fill the matrix
    size_t index = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            matrix[i][j] = filteredKey[index++];
        }
    }

    return matrix;
}

// Function to display the key matrix
void displayKeyMatrix(const vector<vector<char>>& matrix) {
    cout << "Key Matrix:" << endl;
    for (const auto& row : matrix) {
        for (char c : row) {
            cout << c << ' ';
        }
        cout << endl;
    }
}

// Function to format the text
string formatText(const string& text) {
    string formattedText;
    char prevChar = '\0';

    for (char c : text) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (isalpha(c)) {
            if (c == prevChar) formattedText += 'X';
            formattedText += c;
            prevChar = c;
        }
    }

    if (formattedText.size() % 2 != 0) {
        formattedText += 'X';
    }

    return formattedText;
}

// Function to find the position of a character in the matrix
pair<int, int> findPosition(const vector<vector<char>>& matrix, char c) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};  // This should not happen if the matrix is correctly generated
}

// Function to encrypt or decrypt a pair of characters
string processPair(char a, char b, const vector<vector<char>>& matrix, bool encrypt) {
    auto [row1, col1] = findPosition(matrix, a);
    auto [row2, col2] = findPosition(matrix, b);

    if (row1 == row2) {
        // Same row
        return string(1, matrix[row1][(col1 + (encrypt ? 1 : 4)) % 5]) +
               matrix[row2][(col2 + (encrypt ? 1 : 4)) % 5];
    } else if (col1 == col2) {
        // Same column
        return string(1, matrix[(row1 + (encrypt ? 1 : 4)) % 5][col1]) +
               matrix[(row2 + (encrypt ? 1 : 4)) % 5][col2];
    } else {
        // Rectangle
        return string(1, matrix[row1][col2]) + matrix[row2][col1];
    }
}

// Function to perform Playfair cipher encryption or decryption
string playfairCipher(const string& text, const string& key, bool encrypt) {
    vector<vector<char>> matrix = generateKeyMatrix(key);
    string formattedText = formatText(text);
    string result;

    for (size_t i = 0; i < formattedText.size(); i += 2) {
        result += processPair(formattedText[i], formattedText[i + 1], matrix, encrypt);
    }

    return result;
}

int main() {
    string key, plaintext;

    // Get key and plaintext from the user
    cout << "Enter the key: ";
    getline(cin, key);
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    // Remove spaces and punctuation from plaintext
    plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), [](char c) {
        return !isalpha(c);
    }), plaintext.end());

    vector<vector<char>> matrix = generateKeyMatrix(key);
    displayKeyMatrix(matrix);

    string ciphertext = playfairCipher(plaintext, key, true);
    string decryptedText = playfairCipher(ciphertext, key, false);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Decrypted: " << decryptedText << endl;

    return 0;
}
