/**
 * @file DES.h
 * @brief Implementation of the Data Encryption Standard (DES) algorithm for encryption and decryption.
 *
 * This file contains the core functions needed to implement the DES algorithm, including:
 * - Initial and final permutations.
 * - Expansion, substitution, permutation, and XOR operations for the Feistel rounds.
 * - Key scheduling for generating 16 round keys.
 * - Padding for input data not divisible by 64 bits.
 * - File handling for encryption and decryption of files.
 *
 * DES Process Overview:
 * ---------------------
 * 1. **Initial Permutation (IP)**: 
 *    - The 64-bit plaintext block undergoes an initial permutation that rearranges the bits 
 *      according to a predefined table.
 *
 * 2. **Key Scheduling**:
 *    - A 64-bit encryption key is processed through Permuted Choice 1 (PC-1) to produce a 56-bit key.
 *    - The key is split into two 28-bit halves, and 16 different round keys are generated through 
 *      circular left shifts and Permuted Choice 2 (PC-2).
 *
 * 3. **16 Rounds of Feistel Structure**:
 *    - In each round:
 *      - The right half of the block is expanded from 32 bits to 48 bits (using the Expansion E-box).
 *      - The expanded right half is XORed with the round key.
 *      - The result is passed through the 8 substitution boxes (S-boxes), which compress the 48 bits 
 *        back to 32 bits.
 *      - The result is permuted (P-box) and XORed with the left half.
 *      - The halves are swapped after each round (except the last round).
 *
 * 4. **Final Permutation (FP)**:
 *    - After 16 rounds, the left and right halves are recombined and passed through a final permutation,
 *      which is the inverse of the initial permutation.
 *
 * 5. **Encryption/Decryption of Files**:
 *    - If the input data (e.g., a file) is not a multiple of 64 bits, padding is added to ensure all 
 *      blocks are 64 bits. This padding is removed after decryption.
 *
 * 6. **Decryption**:
 *    - Decryption is performed using the same process as encryption, but the round keys are applied in 
 *      reverse order.
 *
 * Usage:
 * ------
 * The DES implementation can be used to encrypt or decrypt files. Ensure that the key is properly 
 * formatted (64-bit key), and if handling files, ensure that padding is added and removed where needed.
 *
 * Functions Included:
 * -------------------
 * - initialPermutation
 * - finalPermutation
 * - expansion
 * - sBoxSubstitution
 * - pBoxPermutation
 * - xorWithKey
 * - generateRoundKeys
 * - desRound
 * - encryptBlock, decryptBlock
 * - padData, unpadData
 * - encryptFile, decryptFile
 *
 * @author Alexander DeJesus
 * @date 10/21/2024
 */

#include "DES.h"
#include <bitset>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>

// Permutation and Transformation Functions
std::bitset<64> initialPermutation(const std::bitset<64>& block);
std::bitset<64> finalPermutation(const std::bitset<64>& block);
std::bitset<48> expansion(const std::bitset<32>& half);
std::bitset<32> pBoxPermutation(const std::bitset<32>& input);
std::bitset<32> sBoxSubstitution(const std::bitset<48>& input);

// XOR Operation with Round Key
std::bitset<48> xorWithKey(const std::bitset<48>& expandedHalf, const std::bitset<48>& roundKey);

// Key Scheduling Functions
std::vector<std::bitset<48>> generateRoundKeys(const std::bitset<64>& key);
std::bitset<28> leftCircularShift(const std::bitset<28>& half, int shift);

// Block Processing Functions
void splitBlock(const std::bitset<64>& block, std::bitset<32>& left, std::bitset<32>& right);
void desRound(std::bitset<32>& left, std::bitset<32>& right, const std::bitset<48>& roundKey);
std::bitset<64> combineBlock(const std::bitset<32>& left, const std::bitset<32>& right);

// Core Encryption and Decryption Functions
std::bitset<64> encryptBlock(const std::bitset<64>& block, const std::vector<std::bitset<48>>& roundKeys);
std::bitset<64> decryptBlock(const std::bitset<64>& block, const std::vector<std::bitset<48>>& roundKeys);

// Padding Functions (for non-64-bit multiple inputs)
std::string padData(const std::string& data);
std::string unpadData(const std::string& data);

// File Handling Functions
void encryptFile(const std::string& inputFile, const std::string& outputFile, const std::bitset<64>& key);
void decryptFile(const std::string& inputFile, const std::string& outputFile, const std::bitset<64>& key);

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

std::bitset<32> sBoxSubstitution(const std::bitset<48>& input) {
    static const int S[8][4][16] = {
        /* S1 */
        {{14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7},
         { 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8},
         { 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0},
         {15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13}},
        /* S2 - S8... */
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

std::bitset<48> xorWithKey(const std::bitset<48>& expandedHalf, const std::bitset<48>& roundKey) {
    return expandedHalf ^ roundKey;
}


std::vector<std::bitset<48>> generateRoundKeys(const std::bitset<64>& key) {
    static const int PC1[56] = {
        57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18, 10,  2, 59, 51, 43, 35, 27, 19,
        11,  3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22, 14,  6,
        61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
    };
    static const int PC2[48] = {
        14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10, 23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
    };
    static const int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

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
        left = leftCircularShift(left, shifts[i]);
        right = leftCircularShift(right, shifts[i]);

        std::bitset<56> combinedKey;
        for (int j = 0; j < 28; ++j) {
            combinedKey[j] = right[j];
            combinedKey[j + 28] = left[j];
        }

        std::bitset<48> roundKey;
        for (int j = 0; j < 48; ++j) {
            roundKey[47 - j] = combinedKey[56 - PC2[j]];
        }
        roundKeys.push_back(roundKey);
    }

    return roundKeys;
}

void desRound(std::bitset<32>& left, std::bitset<32>& right, const std::bitset<48>& roundKey) {
    std::bitset<48> expandedRight = expansion(right);
    std::bitset<48> xorResult = xorWithKey(expandedRight, roundKey);
    std::bitset<32> substituted = sBoxSubstitution(xorResult);
    std::bitset<32> permuted = pBoxPermutation(substituted);
    left ^= permuted;
}

// Left Circular Shift for 28-bit keys
std::bitset<28> leftCircularShift(const std::bitset<28>& half, int shift) {
    std::bitset<28> shifted;
    for (int i = 0; i < 28; ++i) {
        shifted[i] = half[(i + shift) % 28];  // Circular shift
    }
    return shifted;
}

// PKCS#5/7 Padding function for DES encryption
std::string padData(const std::string& data) {
    size_t padLen = 8 - (data.size() % 8);  // Calculate padding size (PKCS#5/7)
    return data + std::string(padLen, static_cast<char>(padLen));  // Append padding
}

// PKCS#5/7 Unpadding function for DES decryption
std::string unpadData(const std::string& data) {
    char padLen = data.back();  // Get the value of the padding
    return data.substr(0, data.size() - padLen);  // Remove the padding
}

// Function to encrypt a single 64-bit block using DES
std::bitset<64> encryptBlock(const std::bitset<64>& block, const std::vector<std::bitset<48>>& roundKeys) {
    std::bitset<64> permutedBlock = initialPermutation(block);

    // Split block into left and right halves
    std::bitset<32> left, right;
    splitBlock(permutedBlock, left, right);

    // Perform 16 rounds of DES encryption
    for (int i = 0; i < 16; ++i) {
        desRound(left, right, roundKeys[i]);
        if (i != 15) {
            std::swap(left, right);  // Swap halves except in the last round
        }
    }

    // Combine the left and right halves and apply the final permutation
    std::bitset<64> combinedBlock = combineBlock(left, right);
    return finalPermutation(combinedBlock);
}

// Function to decrypt a single 64-bit block using DES
std::bitset<64> decryptBlock(const std::bitset<64>& block, const std::vector<std::bitset<48>>& roundKeys) {
    std::bitset<64> permutedBlock = initialPermutation(block);

    // Split block into left and right halves
    std::bitset<32> left, right;
    splitBlock(permutedBlock, left, right);

    // Perform 16 rounds of DES decryption (apply round keys in reverse order)
    for (int i = 15; i >= 0; --i) {
        desRound(left, right, roundKeys[i]);
        if (i != 0) {
            std::swap(left, right);  // Swap halves except in the last round
        }
    }

    // Combine the left and right halves and apply the final permutation
    std::bitset<64> combinedBlock = combineBlock(left, right);
    return finalPermutation(combinedBlock);
}

// Function to split a 64-bit block into two 32-bit halves
void splitBlock(const std::bitset<64>& block, std::bitset<32>& left, std::bitset<32>& right) {
    for (int i = 0; i < 32; ++i) {
        left[i] = block[i + 32];  // Left half is the higher 32 bits
        right[i] = block[i];      // Right half is the lower 32 bits
    }
}

// Function to combine two 32-bit halves into a 64-bit block
std::bitset<64> combineBlock(const std::bitset<32>& left, const std::bitset<32>& right) {
    std::bitset<64> combined;
    for (int i = 0; i < 32; ++i) {
        combined[i] = right[i];         // Lower 32 bits from the right half
        combined[i + 32] = left[i];     // Upper 32 bits from the left half
    }
    return combined;
}

// Encrypt function (DES encryption)
void DES::encrypt(const std::string& inputFile, const std::string& outputFile) {
    std::cout << "Encrypting " << inputFile << " using DES with key: " << key << std::endl;

    // Open the input file
    std::ifstream input(inputFile, std::ios::binary);
    if (!input) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        return;
    }

    // Read input file data into a string
    std::string fileData((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();

    // Pad the input data to a multiple of 8 bytes (64 bits)
    std::string paddedData = padData(fileData);

    // Open the output file for writing the encrypted data
    std::ofstream output(outputFile, std::ios::binary);
    if (!output) {
        std::cerr << "Error: Could not open output file " << outputFile << std::endl;
        return;
    }

    // Convert the key to a 64-bit bitset
    std::bitset<64> keyBits(std::stoull(key, nullptr, 16));  // Assuming key is a hex string

    // Generate round keys
    std::vector<std::bitset<48>> roundKeys = generateRoundKeys(keyBits);

    // Encrypt each 64-bit block
    for (size_t i = 0; i < paddedData.size(); i += 8) {
        uint64_t* blockPtr = reinterpret_cast<uint64_t*>(paddedData.data() + i);  // Correct cast
        std::bitset<64> block(*blockPtr);
        std::bitset<64> ciphertext = encryptBlock(block, roundKeys);
        output.write(reinterpret_cast<const char*>(&ciphertext), sizeof(ciphertext));
    }

    output.close();
    std::cout << "Encryption complete. Ciphertext written to " << outputFile << std::endl;
}

// Decrypt function (DES decryption)
void DES::decrypt(const std::string& inputFile, const std::string& outputFile) {
    std::cout << "Decrypting " << inputFile << " using DES with key: " << key << std::endl;

    // Open the input file
    std::ifstream input(inputFile, std::ios::binary);
    if (!input) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        return;
    }

    // Read input file data into a string
    std::string fileData((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();

    // Open the output file for writing the decrypted data
    std::ofstream output(outputFile, std::ios::binary);
    if (!output) {
        std::cerr << "Error: Could not open output file " << outputFile << std::endl;
        return;
    }

    // Convert the key to a 64-bit bitset
    std::bitset<64> keyBits(std::stoull(key, nullptr, 16));  // Assuming key is a hex string

    // Generate round keys
    std::vector<std::bitset<48>> roundKeys = generateRoundKeys(keyBits);

    // Decrypt each 64-bit block
    std::string decryptedData;
    for (size_t i = 0; i < fileData.size(); i += 8) {
        uint64_t* blockPtr = reinterpret_cast<uint64_t*>(fileData.data() + i);  // Correct cast
        std::bitset<64> block(*blockPtr);
        std::bitset<64> plaintext = decryptBlock(block, roundKeys);
        decryptedData.append(reinterpret_cast<const char*>(&plaintext), 8);
    }

    // Remove padding after decryption
    std::string unpaddedData = unpadData(decryptedData);
    output.write(unpaddedData.data(), unpaddedData.size());

    output.close();
    std::cout << "Decryption complete. Plaintext written to " << outputFile << std::endl;
}

