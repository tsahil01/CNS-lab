#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

const int MAX_ROWS = 3;
const int MAX_COLS = 100; 

void splitStringToInt(const string& str, char delimiter, int key[], int& keySize) {
    stringstream ss(str);
    string item;
    keySize = 0;
    while (getline(ss, item, delimiter)) {
        key[keySize++] = stoi(item);
    }
}

void fillTableRowWise(char table[MAX_ROWS][MAX_COLS], const string& text, int numCols) {
    int index = 0;
    for (int r = 0; r < MAX_ROWS; ++r) {
        for (int c = 0; c < numCols; ++c) {
            if (index < text.size()) {
                table[r][c] = text[index++];
            } else {
                table[r][c] = ' ';
            }
        }
    }
}

void permuteColumns(char table[MAX_ROWS][MAX_COLS], int key[], int keySize) {
    int order[keySize];
    iota(order, order + keySize, 0);

    sort(order, order + keySize, [&key](int a, int b) {
        return key[a] < key[b];
    });

    char permutedTable[MAX_ROWS][MAX_COLS];
    for (int c = 0; c < keySize; ++c) {
        for (int r = 0; r < MAX_ROWS; ++r) {
            permutedTable[r][c] = table[r][order[c]];
        }
    }

    for (int r = 0; r < MAX_ROWS; ++r) {
        for (int c = 0; c < keySize; ++c) {
            table[r][c] = permutedTable[r][c];
        }
    }
}

string readTableColumnWise(const char table[MAX_ROWS][MAX_COLS], int numCols) {
    string result;
    for (int c = 0; c < numCols; ++c) {
        for (int r = 0; r < MAX_ROWS; ++r) {
            if (table[r][c] != ' ') {
                result += table[r][c];
            }
        }
    }
    return result;
}

int main() {
    string text, keyStr;
    char table[MAX_ROWS][MAX_COLS];
    int key[MAX_COLS], keySize;
    int numCols;

    cout << "Enter plaintext: ";
    getline(cin, text);

    cout << "Enter numerical key (e.g., 2 0 1): ";
    getline(cin, keyStr);

    splitStringToInt(keyStr, ' ', key, keySize);

    numCols = (text.length() + MAX_ROWS - 1) / MAX_ROWS;

    if (numCols != keySize) {
        cout << "Error: The number of columns does not match the length of the key." << endl;
        return 1;
    }

    fillTableRowWise(table, text, numCols);

    cout << "Table after row-wise filling:" << endl;
    for (int r = 0; r < MAX_ROWS; ++r) {
        for (int c = 0; c < numCols; ++c) {
            cout << table[r][c] << " ";
        }
        cout << endl;
    }

    permuteColumns(table, key, keySize);

    cout << "Table after column permutation:" << endl;
    for (int r = 0; r < MAX_ROWS; ++r) {
        for (int c = 0; c < numCols; ++c) {
            cout << table[r][c] << " ";
        }
        cout << endl;
    }

    string ciphertext = readTableColumnWise(table, numCols);

    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}
