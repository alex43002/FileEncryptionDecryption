#ifndef CRYPTO_ALGORITHM_H
#define CRYPTO_ALGORITHM_H

#include <string>

class CryptoAlgorithm {
protected:
    std::string key;  // Encryption key

public:
    virtual void encrypt(const std::string& inputFile, const std::string& outputFile) = 0;
    virtual void decrypt(const std::string& inputFile, const std::string& outputFile) = 0;
    
    // Set the encryption key
    virtual void setKey(const std::string& encryptionKey) {
        key = encryptionKey;
    }

    virtual ~CryptoAlgorithm() = default;
};

#endif // CRYPTO_ALGORITHM_H
