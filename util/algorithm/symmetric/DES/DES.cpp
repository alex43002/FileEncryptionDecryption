#include "DES.h"
#include <bitset>
#include <vector>
#include <fstream>
#include <iostream>

// Initial Permutation (IP)
std::bitset<64> initialPermutation(const std::bitset<64>& block);

// Final Permutation (FP)
std::bitset<64> finalPermutation(const std::bitset<64>& block);

// Expansion Function (E-box)
std::bitset<48> expansion(const std::bitset<32>& half);

// Permutation Function (P-box)
std::bitset<32> pBoxPermutation(const std::bitset<32>& input);

// Substitution Function (S-box)
std::bitset<32> sBoxSubstitution(const std::bitset<48>& input);

// XOR with the round key
std::bitset<48> xorWithKey(const std::bitset<48>& expandedHalf, const std::bitset<48>& roundKey);

// Generate Round Keys (Key Schedule)
std::vector<std::bitset<48>> generateRoundKeys(const std::bitset<64>& key);

// Left Circular Shift
std::bitset<28> leftCircularShift(const std::bitset<28>& half, int shift);

// Split 64-bit block into left and right halves
void splitBlock(const std::bitset<64>& block, std::bitset<32>& left, std::bitset<32>& right);

// DES Round Function
void desRound(std::bitset<32>& left, std::bitset<32>& right, const std::bitset<48>& roundKey);


// Initial Permutation (IP)
std::bitset<64> initialPermutation(const std::bitset<64>& block) {
    static const int IP[64] = {
        58, 50, 42, 34, 26, 18, 10,  2,
        60, 52, 44, 36, 28, 20, 12,  4,
        62, 54, 46, 38, 30, 22, 14,  6,
        64, 56, 48, 40, 32, 24, 16,  8,
        57, 49, 41, 33, 25, 17,  9,  1,
        59, 51, 43, 35, 27, 19, 11,  3,
        61, 53, 45, 37, 29, 21, 13,  5,
        63, 55, 47, 39, 31, 23, 15,  7
    };
    std::bitset<64> permuted;
    for (int i = 0; i < 64; ++i) {
        permuted[63 - i] = block[64 - IP[i]];
    }
    return permuted;
}

// Final Permutation (FP)
std::bitset<64> finalPermutation(const std::bitset<64>& block) {
    static const int FP[64] = {
        40,  8, 48, 16, 56, 24, 64, 32,
        39,  7, 47, 15, 55, 23, 63, 31,
        38,  6, 46, 14, 54, 22, 62, 30,
        37,  5, 45, 13, 53, 21, 61, 29,
        36,  4, 44, 12, 52, 20, 60, 28,
        35,  3, 43, 11, 51, 19, 59, 27,
        34,  2, 42, 10, 50, 18, 58, 26,
        33,  1, 41,  9, 49, 17, 57, 25
    };
    std::bitset<64> permuted;
    for (int i = 0; i < 64; ++i) {
        permuted[63 - i] = block[64 - FP[i]];
    }
    return permuted;
}

// Expansion Function (E-box)
std::bitset<48> expansion(const std::bitset<32>& half) {
    static const int E[48] = {
        32,  1,  2,  3,  4,  5,
         4,  5,  6,  7,  8,  9,
         8,  9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32,  1
    };
    std::bitset<48> expanded;
    for (int i = 0; i < 48; ++i) {
        expanded[47 - i] = half[32 - E[i]];
    }
    return expanded;
}

// Permutation Function (P-box)
std::bitset<32> pBoxPermutation(const std::bitset<32>& input) {
    static const int P[32] = {
        16,  7, 20, 21,
        29, 12, 28, 17,
         1, 15, 23, 26,
         5, 18, 31, 10,
         2,  8, 24, 14,
        32, 27,  3,  9,
        19, 13, 30,  6,
        22, 11,  4, 25
    };
    std::bitset<32> permuted;
    for (int i = 0; i < 32; ++i) {
        permuted[31 - i] = input[32 - P[i]];
    }
    return permuted;
}

// Substitution Function (S-box)
std::bitset<32> sBoxSubstitution(const std::bitset<48>& input) {
    static const int S[8][4][16] = {
        /* S1 */
        {{14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7},
         { 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8},
         { 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0},
         {15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13}},
        //... Repeat for S2 to S8
    };
    std::bitset<32> output;
    for (int i = 0; i < 8; ++i) {
        int row = (input[47 - (i * 6)] << 1) + input[47 - (i * 6 + 5)];
        int col = (input[47 - (i * 6 + 1)] << 3) + (input[47 - (i * 6 + 2)] << 2) + (input[47 - (i * 6 + 3)] << 1) + input[47 - (i * 6 + 4)];
        int val = S[i][row][col];
        for (int j = 0; j < 4; ++j) {
            output[i * 4 + j] = (val >> j) & 1;
        }
    }
    return output;
}

// XOR with the round key
std::bitset<48> xorWithKey(const std::bitset<48>& expandedHalf, const std::bitset<48>& roundKey) {
    return expandedHalf ^ roundKey;
}

// Generate Round Keys (Key Schedule)
std::vector<std::bitset<48>> generateRoundKeys(const std::bitset<64>& key) {
    static const int PC1[56] = {
        57, 49, 41, 33, 25, 17,  9,
         1, 58, 50, 42, 34, 26, 18,
        10,  2, 59, 51, 43, 35, 27,
        19, 11,  3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
         7, 62, 54, 46, 38, 30, 22,
        14,  6, 61, 53, 45, 37, 29,
        21, 13,  5, 28, 20, 12,  4
    };
    static const int PC2[48] = {
        14, 17, 11, 24,  1,  5,
         3, 28, 15,  6, 21, 10,
        23, 19, 12,  4, 26,  8,
        16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };
    static const int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    // Apply PC1 to get the initial 56-bit key
    std::bitset<56> permutedKey;
    for (int i = 0; i < 56; ++i) {
        permutedKey[55 - i] = key[64 - PC1[i]];
    }

    std::bitset<28> left, right;
    for (int i = 0; i < 28; ++i) {
        left[i] = permutedKey[i + 28];
        right[i] = permutedKey[i];
    }

    std::vector<std::bitset<48>> roundKeys;
    for (int i = 0; i < 16; ++i) {
        // Perform left circular shift
        left = leftCircularShift(left, shifts[i]);
        right = leftCircularShift(right, shifts[i]);

        // Combine left and right into a 56-bit key
        std::bitset<56> combinedKey;
        for (int j = 0; j < 28; ++j) {
            combinedKey[j] = right[j];
            combinedKey[j + 28] = left[j];
        }

        // Apply PC2 to generate the 48-bit round key
        std::bitset<48> roundKey;
        for (int j = 0; j < 48; ++j) {
            roundKey[47 - j] = combinedKey[56 - PC2[j]];
        }
        roundKeys.push_back(roundKey);
    }

    return roundKeys;
}

// Left Circular Shift
std::bitset<28> leftCircularShift(const std::bitset<28>& half, int shift) {
    std::bitset<28> shifted;
    for (int i = 0; i < 28; ++i) {
        shifted[i] = half[(i + shift) % 28];
    }
    return shifted;
}

// Split 64-bit block into left and right halves
void splitBlock(const std::bitset<64>& block, std::bitset<32>& left, std::bitset<32>& right) {
    for (int i = 0; i < 32; ++i) {
        left[i] = block[i + 32];
        right[i] = block[i];
    }
}

void desRound(std::bitset<32>& left, std::bitset<32>& right, const std::bitset<48>& roundKey) {
    // Step 1: Expand the right half (32 bits to 48 bits)
    std::bitset<48> expandedRight = expansion(right);

    // Step 2: XOR with the round key
    std::bitset<48> xorResult = xorWithKey(expandedRight, roundKey);

    // Step 3: Apply S-box substitution (compress 48 bits to 32 bits)
    std::bitset<32> substituted = sBoxSubstitution(xorResult);

    // Step 4: Apply P-box permutation
    std::bitset<32> permuted = pBoxPermutation(substituted);

    // Step 5: XOR the result with the left half
    left ^= permuted;  // XOR the result with the left half of the block
}



// Encrypt function (DES encryption)
void DES::encrypt(const std::string& inputFile, const std::string& outputFile) {
    std::cout << "Encrypting " << inputFile << " using DES with key: " << key << std::endl;

    // Convert the key to a 64-bit bitset
    std::bitset<64> keyBits(std::stoull(key, nullptr, 16));  // Assuming key is a hex string
    
    // Read input file (assuming input is a single 64-bit block for simplicity)
    std::ifstream input(inputFile, std::ios::binary);
    if (!input) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return;
    }
    
    std::bitset<64> plaintext;
    input.read(reinterpret_cast<char*>(&plaintext), sizeof(plaintext));
    input.close();

    // Generate round keys
    std::vector<std::bitset<48>> roundKeys = generateRoundKeys(keyBits);

    // Initial permutation
    plaintext = initialPermutation(plaintext);

    // Split into left and right halves
    std::bitset<32> left, right;
    splitBlock(plaintext, left, right);

    // Perform 16 rounds of DES
    for (int i = 0; i < 16; ++i) {
        desRound(left, right, roundKeys[i]);
        if (i != 15) {
            std::swap(left, right);  // Swap halves except in the last round
        }
    }

    // Combine halves and apply final permutation
    std::bitset<64> ciphertext;
    for (int i = 0; i < 32; ++i) {
        ciphertext[i] = right[i];
        ciphertext[i + 32] = left[i];
    }
    ciphertext = finalPermutation(ciphertext);

    // Write output file
    std::ofstream output(outputFile, std::ios::binary);
    if (!output) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return;
    }
    output.write(reinterpret_cast<const char*>(&ciphertext), sizeof(ciphertext));
    output.close();

    std::cout << "Encryption complete. Ciphertext written to " << outputFile << std::endl;
}

// Decrypt function (DES decryption)
void DES::decrypt(const std::string& inputFile, const std::string& outputFile) {
    std::cout << "Decrypting " << inputFile << " using DES with key: " << key << std::endl;

    // Convert the key to a 64-bit bitset
    std::bitset<64> keyBits(std::stoull(key, nullptr, 16));  // Assuming key is a hex string
    
    // Read input file (assuming input is a single 64-bit block for simplicity)
    std::ifstream input(inputFile, std::ios::binary);
    if (!input) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return;
    }
    
    std::bitset<64> ciphertext;
    input.read(reinterpret_cast<char*>(&ciphertext), sizeof(ciphertext));
    input.close();

    // Generate round keys
    std::vector<std::bitset<48>> roundKeys = generateRoundKeys(keyBits);

    // Initial permutation
    ciphertext = initialPermutation(ciphertext);

    // Split into left and right halves
    std::bitset<32> left, right;
    splitBlock(ciphertext, left, right);

    // Perform 16 rounds of DES (in reverse order for decryption)
    for (int i = 15; i >= 0; --i) {
        desRound(left, right, roundKeys[i]);
        if (i != 0) {
            std::swap(left, right);  // Swap halves except in the last round
        }
    }

    // Combine halves and apply final permutation
    std::bitset<64> plaintext;
    for (int i = 0; i < 32; ++i) {
        plaintext[i] = right[i];
        plaintext[i + 32] = left[i];
    }
    plaintext = finalPermutation(plaintext);

    // Write output file
    std::ofstream output(outputFile, std::ios::binary);
    if (!output) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return;
    }
    output.write(reinterpret_cast<const char*>(&plaintext), sizeof(plaintext));
    output.close();

    std::cout << "Decryption complete. Plaintext written to " << outputFile << std::endl;
}
