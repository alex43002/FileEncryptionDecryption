#include "Help.h"
#include <iostream>

void displayHelp() {
    std::cout << "Usage: encryption_tool.exe [options] <encryption_type> <encryption_key> <input_file> <output_file>\n";
    std::cout << "\nOptions:\n";
    std::cout << "  --help                            Show this help message and exit.\n";
    std::cout << "  --encrypt                         Encrypt the specified input file.\n";
    std::cout << "  --decrypt                         Decrypt the specified input file.\n";
    std::cout << "\nArguments:\n";
    std::cout << "  <encryption_type>                 The encryption algorithm to use (e.g., DES).\n";
    std::cout << "  <encryption_key>                  The key used for encryption or decryption.\n";
    std::cout << "  <input_file>                      The file to encrypt or decrypt.\n";
    std::cout << "  <output_file>                     The output file where the result will be saved.\n";
    std::cout << "\nExamples:\n";
    std::cout << "  encryption_tool.exe --encrypt DES my_secret_key input.txt encrypted_output.txt\n";
    std::cout << "  encryption_tool.exe --decrypt DES my_secret_key encrypted_output.txt decrypted_output.txt\n";
}
