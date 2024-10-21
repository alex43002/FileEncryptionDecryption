#ifndef DES_H
#define DES_H

#include "../../CryptoAlgorithm.h"
#include <iostream>
#include <string>

class DES : public CryptoAlgorithm {
public:
    void encrypt(const std::string& inputFile, const std::string& outputFile) override;
    void decrypt(const std::string& inputFile, const std::string& outputFile) override;
};

#endif // DES_H
