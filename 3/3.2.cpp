#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

const int MOD = 26;

int modInverse(int a, int m) {
    for (int x = 1; x < m; ++x) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    throw invalid_argument("Modular inverse does not exist.");
}

int determinant(int a, int b, int c, int d) {
    return (a * d - b * c + MOD) % MOD;
}

bool invertMatrix(const vector<int>& key, vector<int>& inv) {
    int det = determinant(key[0], key[1], key[2], key[3]);
    if (det == 0) return false;

    int invDet = modInverse(det, MOD);
    inv[0] = (key[3] * invDet) % MOD;
    inv[1] = (-key[1] * invDet + MOD) % MOD;
    inv[2] = (-key[2] * invDet + MOD) % MOD;
    inv[3] = (key[0] * invDet) % MOD;

    return true;
}

void encryptBlock(const vector<int>& key, const string& block, string& cipher) {
    vector<int> key_matrix = key;
    int x[2] = { block[0] - 'A', block[1] - 'A' };
    int y[2];
    y[0] = (key_matrix[0] * x[0] + key_matrix[1] * x[1]) % MOD;
    y[1] = (key_matrix[2] * x[0] + key_matrix[3] * x[1]) % MOD;
    cipher = string(1, 'A' + y[0]) + string(1, 'A' + y[1]);
}

void decryptBlock(const vector<int>& inv_key, const string& block, string& plain) {
    int x[2] = { block[0] - 'A', block[1] - 'A' };
    int y[2];
    y[0] = (inv_key[0] * x[0] + inv_key[1] * x[1]) % MOD;
    y[1] = (inv_key[2] * x[0] + inv_key[3] * x[1]) % MOD;
    if (y[0] < 0) y[0] += MOD;
    if (y[1] < 0) y[1] += MOD;
    plain = string(1, 'A' + y[0]) + string(1, 'A' + y[1]);
}

int main() {
    vector<int> key(4);
    cout << "Enter the 2x2 key matrix (4 integers, space-separated): ";
    for (int& k : key) {
        cin >> k;
        if (k < 0 || k >= MOD) {
            cerr << "Error: Key matrix values must be in the range 0 to " << (MOD - 1) << "." << endl;
            return 1;
        }
    }

    string plaintext;
    cout << "Enter the plaintext (uppercase letters only): ";
    cin >> plaintext;

    if (plaintext.length() % 2 != 0) {
        plaintext += 'X';
    }

    string ciphertext;
    for (size_t i = 0; i < plaintext.length(); i += 2) {
        string block = plaintext.substr(i, 2);
        string enc_block;
        encryptBlock(key, block, enc_block);
        ciphertext += enc_block;
    }

    cout << "Encrypted data: " << ciphertext << endl;

    vector<int> inv_key(4);
    if (!invertMatrix(key, inv_key)) {
        cerr << "Error: Key matrix is not invertible." << endl;
        return 1;
    }

    string decrypted;
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        string block = ciphertext.substr(i, 2);
        string dec_block;
        decryptBlock(inv_key, block, dec_block);
        decrypted += dec_block;
    }

    if (decrypted.back() == 'X') {
        decrypted.pop_back();
    }

    cout << "Decrypted data: " << decrypted << endl;

    return 0;
}
