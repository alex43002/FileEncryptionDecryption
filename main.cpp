#include <iostream>
#include <string>
#include "util/help/Help.h"

void processCommandLineArguments(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No arguments provided. Use --help for usage information." << std::endl;
        return;
    }

    std::string action = argv[1];

    if (action == "--help") {
        displayHelp();
    } else if (action == "--encrypt") {
        if (argc < 3) {
            std::cerr << "Error: No file specified for encryption." << std::endl;
            return;
        }
        // Call encrypt function (not implemented yet)
    } else if (action == "--decrypt") {
        if (argc < 3) {
            std::cerr << "Error: No file specified for decryption." << std::endl;
            return;
        }
        // Call decrypt function (not implemented yet)
    } else {
        std::cerr << "Error: Unknown action '" << action << "'. Use --help for usage information." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    processCommandLineArguments(argc, argv);
    return 0;
}
