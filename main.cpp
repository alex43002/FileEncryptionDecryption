#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include "util/help/Help.h"
#include "util/algorithm/CryptoAlgorithm.h"
#include "util/algorithm/symmetric/DES/DES.h"

// Function to process encryption or decryption
void processFile(const std::string& action, const std::string& algorithm, const std::string& inputFile, const std::string& outputFile) {
    
    // Map of available encryption algorithms
    std::unordered_map<std::string, std::unique_ptr<CryptoAlgorithm>> algorithms;
    algorithms.emplace("DES", std::make_unique<DES>());

    // Check if the algorithm exists
    auto it = algorithms.find(algorithm);
    if (it == algorithms.end()) {
        std::cerr << "Error: Unknown encryption algorithm '" << algorithm << "'." << std::endl;
        return;
    }

    // Call the appropriate method based on the action
    if (action == "--encrypt") {
        it->second->encrypt(inputFile);  // Encrypt the input file
        std::cout << "Encrypted file saved to: " << outputFile << std::endl;
    } else if (action == "--decrypt") {
        it->second->decrypt(inputFile);  // Decrypt the input file
        std::cout << "Decrypted file saved to: " << outputFile << std::endl;
    } else {
        std::cerr << "Error: Unknown action '" << action << "'." << std::endl;
    }
}

// Function to validate and process the command-line arguments
void processCommandLineArguments(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Error: Invalid number of arguments." << std::endl;
        std::cerr << "Usage: encryption_tool.exe --[encrypt/decrypt] [encryption_type] [input_file] [output_file]" << std::endl;
        return;
    }

    std::string action = argv[1];
    std::string algorithm = argv[2];
    std::string inputFile = argv[3];
    std::string outputFile = argv[4];

    if (action == "--help") {
        displayHelp();
    } else if (action == "--encrypt" || action == "--decrypt") {
        processFile(action, algorithm, inputFile, outputFile);
    } else {
        std::cerr << "Error: Unknown action '" << action << "'." << std::endl;
        std::cerr << "Use --help for usage information." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    processCommandLineArguments(argc, argv);
    return 0;
}
