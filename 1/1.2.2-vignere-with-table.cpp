#include <bits/stdc++.h>
using namespace std;

void printTable(vector<char> pt, vector<int> pt_values, vector<int> k_values, vector<char> ct) {
    cout << "PT:      ";
    for (char c : pt) cout << c << "  ";
    cout << endl;

    cout << "Value:   ";
    for (int val : pt_values) cout << setfill('0') << setw(2) << val << " ";
    cout << endl;

    cout << "K Value: ";
    for (int val : k_values) cout << setfill('0') << setw(2) << val << " ";
    cout << endl;

    cout << "CT:      ";
    for (char c : ct) cout << c << "  ";
    cout << endl;
}

string vignereCipher(string text, string keyword, bool encrypt) {
    string ans = "";
    int n = text.size();
    int m = keyword.size();

    vector<char> pt(text.begin(), text.end());
    vector<int> pt_values;
    vector<int> k_values;
    vector<char> ct;

    for (int i = 0; i < n; i++) {
        int val = int(text[i] - 97); // Convert plaintext character to 0-25
        pt_values.push_back(val);
        int k = int(keyword[i % m] - 65); // Convert keyword character to 0-25
        k_values.push_back(k);
        val = encrypt ? ((val + k) % 26) : ((val - k + 26) % 26); // Ensure positive result for decryption
        ct.push_back(char(val + 65)); // Convert back to character
    }

    printTable(pt, pt_values, k_values, ct);

    for (char c : ct) ans += c;
    return ans;
}

int main() {
    string text = "";
    string keyword = "";
    int encrypt = 0;

    cout << "Text: ";
    cin >> text;

    cout << "Keyword: ";
    cin >> keyword;

    cout << "1 for Encryption, 2 for Decryption: ";
    cin >> encrypt;

    transform(text.begin(), text.end(), text.begin(), ::tolower);
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::toupper);

    string ans = (encrypt == 1) ? vignereCipher(text, keyword, true) : vignereCipher(text, keyword, false);
    cout << "Final Text: "<< ans << endl;

    return 0;
}
