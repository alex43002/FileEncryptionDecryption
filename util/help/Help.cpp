#include "Help.h"
#include <iostream>

void displayHelp() {
    std::cout << "Usage: encryption_tool [options] [arguments]\n";
    std::cout << "\nOptions:\n";
    std::cout << "  --help                Show this help message and exit.\n";
    std::cout << "  --encrypt <file>     Encrypt the specified file.\n";
    std::cout << "  --decrypt <file>     Decrypt the specified file.\n";
    std::cout << "\nThis tool provides encryption and decryption functionalities.\n";
}
