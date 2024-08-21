#include <bits/stdc++.h>
using namespace std;

string ceasarCipher(string text, int k, bool encrypt){
    string ans = "";
    for (auto ch : text){
        int val = int(ch) - 97;
        val = encrypt ? ((val + k) % 26) : ((val - k) % 26);
        ans +=  char(val + 65);
    }
    return ans;
}

int main(){
    string text = "";
    int k = 0;
    int ceasar = 0;
    int encryt = 0;

    cout << "Text: ";
    cin >> text;

    cout << "1 for Ceasar Cipher. "
         << "2 for Modified Ceasar Cipher: ";
    cin >> ceasar;

    if (ceasar == 1){
        k = 3;
    } else{
        cout << "Value of k: ";
        cin >> k;
    }

    cout << "1 for Encryption. "
         << "2 for Decryption: ";
    cin >> encryt;

    string ans = (encryt == 1)? ceasarCipher(text, k, true) : ceasarCipher(text, k, false);
    cout<<"Final Text - "<<ans;

    cout << endl;
    return 0;
}
