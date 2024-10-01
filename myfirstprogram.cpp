#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to encrypt/decrypt a file using XOR encryption
void xorEncryptDecrypt(const string& inputFilePath, const string& outputFilePath, char key) {
    ifstream inputFile(inputFilePath, ios::binary); // Open file in binary mode
    ofstream outputFile(outputFilePath, ios::binary); // Create output file in binary mode

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error: Could not open file(s)." << endl;
        return;
    }

    char c;
    while (inputFile.get(c)) {
        char encryptedChar = c ^ key; // XOR encryption
        outputFile.put(encryptedChar); // Write encrypted character to output file
    }

    inputFile.close();
    outputFile.close();
    cout << "File has been processed and saved to " << outputFilePath << endl;
}

int main() {
    string inputFile, outputFile;
    char key;

    cout << "Enter the path of the file to encrypt/decrypt: ";
    cin >> inputFile;

    cout << "Enter the path where the output should be saved: ";
    cin >> outputFile;

    cout << "Enter a single character key for encryption/decryption: ";
    cin >> key;

    // Call the encryption/decryption function
    xorEncryptDecrypt(inputFile, outputFile, key);

    return 0;
}
