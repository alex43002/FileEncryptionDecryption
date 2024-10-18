#ifndef CRYPTO_ALGORITHM_H
#define CRYPTO_ALGORITHM_H

#include <string>

class CryptoAlgorithm {
public:
    virtual void encrypt(const std::string& inputFile) = 0;  // Pure virtual encryption method
    virtual void decrypt(const std::string& inputFile) = 0;  // Pure virtual decryption method
    virtual ~CryptoAlgorithm() = default;                    // Virtual destructor for proper cleanup
};

#endif // CRYPTO_ALGORITHM_H
