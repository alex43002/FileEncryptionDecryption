#ifndef DES_H
#define DES_H

#include "../CryptoAlgorithm.h"
#include <string>
#include <iostream>

class DES : public CryptoAlgorithm {
public:
    void encrypt(const std::string& inputFile) override;  // Override the base class's encrypt method
    void decrypt(const std::string& inputFile) override;  // Override the base class's decrypt method
};

#endif // DES_H
