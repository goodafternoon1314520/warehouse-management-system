#ifndef RSAMANAGER_H
#define RSAMANAGER_H

#include <string>

class RSAManager {
public:
    static bool generateKeyPair(const std::string& publicKeyFile, const std::string& privateKeyFile);

    static std::string encrypt(const std::string& plaintext, const std::string& publicKeyFile);

    static std::string decrypt(const std::string& ciphertext, const std::string& privateKeyFile);
};


#endif