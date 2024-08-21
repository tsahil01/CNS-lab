#include <bits/stdc++.h>
using namespace std;

string vignereCipher(string text, string keyword, bool encrypt){
    string ans = "";
    int n = text.size();
    int m = keyword.size();

    for(int i = 0; i<n; i++){
        int val = int(text[i] - 97);
        int k  = int(keyword[i%m] - 65);
        val = encrypt ? ((val + k) % 26) : ((val - k) % 26);
        ans +=  char(val + 65);
    }
    return ans;
}

int main(){
    string text = "";
    string keyword = "";
    int encryt = 0;

    cout << "Text: ";
    cin >> text;

    cout << "Keyword: ";
    cin >> keyword;

    cout << "1 for Encryption. "
         << "2 for Decryption: ";
    cin >> encryt;

    string ans = (encryt == 1)? vignereCipher(text, keyword, true) : vignereCipher(text, keyword, false);
    cout<<ans;

    cout << endl;
    return 0;
}
