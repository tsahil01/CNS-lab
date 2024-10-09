#include <iostream>
#include <vector>
#include <string>

using namespace std;

string pBoxPermutation(const string& input, const vector<int>& pBox) {
    string output(input.size(), '0');
    for (size_t i = 0; i < pBox.size(); ++i) {
        output[i] = input[pBox[i] - 1];
    }
    return output;
}

int main() {
    string input = "11001000"; // 8-bit input
    vector<int> pBox = {3, 1, 2, 6, 4, 8, 7, 5}; // P-box mapping

    string output = pBoxPermutation(input, pBox);

    cout << "Input:  " << input << endl;
    cout << "P-box:  ";
    for (size_t i = 0; i < pBox.size(); ++i) {
        cout << pBox[i] << (i < pBox.size() - 1 ? ", " : "");
    }
    cout << endl;
    cout << "Output: " << output << endl;


    return 0;
}
