#include <iostream>
#include <vector>
#include <string>

void split(const std::vector<bool>& word, std::vector<bool>& rightWord, std::vector<bool>& leftWord) {
    int n = word.size();
    rightWord.resize(n / 2);
    leftWord.resize(n / 2);

    for (int i = 0; i < n / 2; i++) {
        rightWord[i] = word[i];
        leftWord[i] = word[i + n / 2];
    }
}

int main() {
    std::string input;
    std::vector<bool> word;

    // input
    std::cout << "Enter a binary word : ";
    std::cin >> input;

    for (char bit : input) {
        if (bit == '0') {
            word.push_back(0);
        } else if (bit == '1') {
            word.push_back(1);
        } else {
            std::cerr << "Invalid input. Please enter a binary string." << std::endl;
            return 1;
        }
    }

    if (word.size() % 2 != 0) {
        std::cerr << "Invalid input. The length of the binary word must be even." << std::endl;
        return 1;
    }

    std::vector<bool> rightWord, leftWord;

    split(word, rightWord, leftWord);

    std::cout << "Right Word: ";
    for (bool bit : rightWord) {
        std::cout << bit;
    }
    std::cout << std::endl;

    std::cout << "Left Word: ";
    for (bool bit : leftWord) {
        std::cout << bit;
    }
    std::cout << std::endl;

    return 0;
}
