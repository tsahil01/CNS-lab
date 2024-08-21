#include <iostream>
#include <algorithm>

using namespace std;

void invertKey(int key[], int invertedKey[], int length) {
    // Initialize the inverted key array with 0s
    for (int i = 0; i < length; ++i) {
        invertedKey[key[i] - 1] = i + 1;
    }
}

int main() {
    int encryptionKey[] = {3, 1, 4, 2};
    int length = sizeof(encryptionKey) / sizeof(encryptionKey[0]);
    int decryptionKey[length];

    invertKey(encryptionKey, decryptionKey, length);

    cout << "Encryption Key: ";
    for (int i = 0; i < length; ++i) {
        cout << encryptionKey[i] << " ";
    }
    cout << endl;

    cout << "Decryption Key: ";
    for (int i = 0; i < length; ++i) {
        cout << decryptionKey[i] << " ";
    }
    cout << endl;

    return 0;
}
