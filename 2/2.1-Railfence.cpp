#include <iostream>
#include <vector>
#include <string>

using namespace std;

void encryption()
{
    string plain;
    int rails;
    cout << "Enter the plain text: ";
    cin.ignore();  
    getline(cin, plain); 
    cout << "Enter the number of rails: ";
    cin >> rails;
    if (rails <= 1) {
        cout << "Number of rails must be greater than 1." << endl;
        return;}
    int n = plain.length();
    vector<vector<char>> array(rails, vector<char>(n, ' ')); 

    int row = 0;
    bool goingDown = false;
    for (int i = 0; i < n; i++)
    {
        array[row][i] = plain[i];

        if (row == 0 || row == rails - 1)
            goingDown = !goingDown;

        row += goingDown ? 1 : -1;
    }
    cout << "Encrypted text: ";
    for (int r = 0; r < rails; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (array[r][c] != ' ')
                cout << array[r][c];
        }
    }
    cout << endl;
}

void decryption()
{
    string cipher;
    int rails;
    cout << "Enter the cipher text: ";
    cin.ignore();  
    getline(cin, cipher);  
    cout << "Enter the number of rails: ";
    cin >> rails;
    if (rails <= 1) {
        cout << "Number of rails must be greater than 1." << endl;
        return;
    }
    int n = cipher.length();
    vector<vector<char>> array(rails, vector<char>(n, ' '));  
    vector<vector<bool>> zigzag(rails, vector<bool>(n, false));
    int row = 0;
    bool goingDown = false;
    for (int i = 0; i < n; i++)
    {
        zigzag[row][i] = true;
        if (row == 0 || row == rails - 1)
            goingDown = !goingDown;

        row += goingDown ? 1 : -1;
    }
    int index = 0;
    for (int r = 0; r < rails; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (zigzag[r][c])
            {
                array[r][c] = cipher[index++];
            }
        }
    }
    string decrypted;
    row = 0;
    goingDown = false;

    for (int i = 0; i < n; i++)
    {
        decrypted += array[row][i];
        if (row == 0 || row == rails - 1)
            goingDown = !goingDown;

        row += goingDown ? 1 : -1;
    }

    cout << "Decrypted text: " << decrypted << endl;
}



int main()
{
    int choice;
    cout << "1. Encryption" << endl;
    cout << "2. Decryption" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    
    if (choice == 1)
    {
        encryption();
    }
    else if (choice == 2)
    {
       decryption();
    }
    
    return 0;
}
