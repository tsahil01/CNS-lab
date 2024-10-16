#include<bits/stdc++.h>

using namespace std;

// AES S-box
const uint8_t Sbox[16][16] = {
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}};

// A 4x4 matrix representing the state
typedef uint8_t state_t[4][4];

// Function to convert hex string to byte
int hexToByte(const string &hexStr){
    int byte;
    stringstream ss;
    ss << hex << hexStr;
    ss >> byte;
    return byte;
}

void roundState(state_t &state){
    cout << "Enter the state matrix (4x4) in hexadecimal format (16 values):" << endl;
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) {
            string hexStr;
            cin >> hexStr;
            state[i][j] = static_cast<uint8_t>(hexToByte(hexStr));
        }
}

void roundRoundKey(uint8_t *roundKey){
    cout << "Enter the round key (16 bytes) in hexadecimal format (16 values):" << endl;
    for (int i = 0; i < 16; i++) {
        string hexStr;
        cin >> hexStr;
        roundKey[i] = static_cast<uint8_t>(hexToByte(hexStr));
    }
}

void SubBytes(state_t &state){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state[i][j] = Sbox[state[i][j] >> 4][state[i][j] & 0xF];
    
}

void transposeStateMatrix(state_t &state){
    state_t temp;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            temp[i][j] = state[j][i];
        
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            state[i][j] = temp[i][j];
}

void ShiftRows(state_t &state){
    transposeStateMatrix(state);
    uint8_t temp;

    // Rotate first row 1 columns to left
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    // Rotate second row 2 columns to left
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;

    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Rotate third row 3 columns to left
    temp = state[3][0];
    state[3][0] = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = temp;
    transposeStateMatrix(state);
}

// MixColumns step (performs mixing operation on each column)
uint8_t xtime(uint8_t x){
    return (x << 1) ^ (((x >> 7) & 1) * 0x1b);
}

void MixColumns(state_t &state){
    transposeStateMatrix(state);
    for (int i = 0; i < 4; i++){
        uint8_t t = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
        uint8_t temp0 = state[0][i];
        state[0][i] ^= xtime(state[0][i] ^ state[1][i]) ^ t;
        state[1][i] ^= xtime(state[1][i] ^ state[2][i]) ^ t;
        state[2][i] ^= xtime(state[2][i] ^ state[3][i]) ^ t;
        state[3][i] ^= xtime(state[3][i] ^ temp0) ^ t;
    }
    transposeStateMatrix(state);
}

void AddRoundKey(state_t &state, vector<vector<uint8_t>> xyz, int round){
    round++;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state[i][j] ^= xyz[round * 4 + i][j];
}

void PrintState(const state_t &state){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
            cout << hex << setw(2) << setfill('0') << (int)state[j][i] << " ";
        cout << endl;
    }
}


// Rcon array for round constants
const uint32_t Rcon[10] = {
    0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,
    0x20000000, 0x40000000, 0x80000000, 0x1B000000, 0x36000000};

// Function to rotate a word (RotWord)
uint32_t RotWord(uint32_t word){
    return (word << 8) | (word >> 24);
}

// Function to substitute a word using the AES S-box (SubWord)
uint32_t SubWord(uint32_t word){
    return (Sbox[(word >> 28) & 0xF][(word >> 24) & 0xF] << 24) |
           (Sbox[(word >> 20) & 0xF][(word >> 16) & 0xF] << 16) | 
           (Sbox[(word >> 12) & 0xF][(word >> 8) & 0xF] << 8) |  
           (Sbox[(word >> 4) & 0xF][word & 0xF]);                 
}

// Key expansion function for AES-128
vector<uint32_t> KeyExpansion(const uint8_t *inputKey){
    int cnt = 0;
    vector<uint32_t> expandedKeys(44); // 44 words for AES-128

    // Initialize the first 4 words with the original key
    for (int i = 0; i < 4; ++i)
        expandedKeys[i] = (inputKey[i * 4] << 24) |
                          (inputKey[i * 4 + 1] << 16) |
                          (inputKey[i * 4 + 2] << 8) |
                          inputKey[i * 4 + 3];

    // Key expansion loop
    for (int i = 4; i < 44; ++i){
        uint32_t temp = expandedKeys[i - 1];
        if (i % 4 == 0)
            temp = SubWord(RotWord(temp)) ^ Rcon[i / 4 - 1];
        expandedKeys[i] = expandedKeys[i - 4] ^ temp;
    }

    return expandedKeys;
}

int main(){
    // 00 04 12 14 12 04 12 00 0c 00 13 11 08 23 19 19  24 75 A2 B3 34 75 56 88 31 E2 12 00 13 AA 54 87
    state_t state = {
        {0x00, 0x04, 0x12, 0x14},
        {0x12, 0x04, 0x12, 0x00},
        {0x0c, 0x00, 0x13, 0x11},
        {0x08, 0x23, 0x19, 0x19}};

    // 24 75 A2 B3 34 75 56 88 31 E2 12 00 13 AA 54 87
    uint8_t roundKey[16] = {0x24, 0x75, 0xA2, 0xB3, 0x34, 0x75, 0x56, 0x88, 0x31, 0xE2, 0x12, 0x00, 0x13, 0xAA, 0x54, 0x87};
    vector<vector<uint8_t>> xyz;


    // -----------------------------------------------------------------------
    // Take user input
    // TODO : Uncomment this line
    // roundState(state);
    // roundRoundKey(roundKey);

    // Print initial state
    cout <<endl<< "Initial state:" << endl;
    PrintState(state);
    cout << endl;

    vector<uint32_t> expandedKeys = KeyExpansion(roundKey);

    cout << "Expanded keys:" << endl;
    for (int i = 0; i < 44; i++){
        cout << hex << setw(8) << setfill('0') << expandedKeys[i] << " ";
        if ((i + 1) % 4 == 0){
            cout << endl;
        }
    }
    // put expandedKeys into 2D array
    for (int i = 0; i < 44; i++){
        vector<uint8_t> temp;
        for (int j = 0; j < 4; j++)
            temp.push_back((expandedKeys[i] >> (24 - j * 8)) & 0xFF);
        xyz.push_back(temp);
    }

    // Pre-Round Transformation
    cout <<endl<< "After Pre-Round Transformation:" << endl;
    AddRoundKey(state, xyz, -1);
    PrintState(state);

    // Perform 10 AES rounds
    for (int round = 0; round <= 9; round++){
        cout << endl
             << endl
             << "Round " << hex << round << ":" << endl;
        
        cout << "------------------------------"<<endl;

        // SubBytes step
        SubBytes(state);
        cout << "After SubBytes:" << endl;
        PrintState(state);
        cout << endl;

        // ShiftRows step
        ShiftRows(state);
        cout << "After ShiftRows:" << endl;
        PrintState(state);
        cout << endl;

        // MixColumns step (skip on the last round)
        if (round < 9){
            MixColumns(state);
            cout << "After MixColumns:" << endl;
            PrintState(state);
            cout << endl;
        }

        // AddRoundKey step
        AddRoundKey(state, xyz, round);
        cout << "After AddRoundKey:" << endl;
        PrintState(state);
        cout << "------------------------------"<<endl;
    }

    return 0;
}