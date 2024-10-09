#include <iostream>
#include <vector>
#include <string>

void swapHalves(std::vector<bool>& word) {
    int n = word.size();
    std::vector<bool> swappedWord(n);

    for (int i = 0; i < n / 2; i++) {
        swappedWord[i] = word[i + n / 2];
        swappedWord[i + n / 2] = word[i];
    }
    word = swappedWord;
}

int main() {
    std::string input;
    std::cout << "Enter a binary word (even length): ";
    std::cin >> input;

    std::vector<bool> word;
    for (char bit : input) {
        if (bit == '0') {
            word.push_back(0);
        } else if (bit == '1') {
            word.push_back(1);
        } else {
            std::cerr << "Invalid input." << std::endl;
            return 1;
        }
    }

    if (word.size() % 2 != 0) {
        std::cerr << "The length must be even." << std::endl;
        return 1;
    }

    swapHalves(word);

    std::cout << "Swapped Word: ";
    for (bool bit : word) {
        std::cout << bit;
    }
    std::cout << std::endl;

    return 0;
}
