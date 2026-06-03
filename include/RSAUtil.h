#ifndef RSAUTIL_H
#define RSAUTIL_H

#include <string>

class RSAUtil {
public:
    // RAS加密
    static std::string encrypt(const std::string& plainText, const std::string& publicKeyPath);
    // RAS解密
    static std::string decrypt(const std::string& cipherText, const std::string& privateKeyPath);
};

#endif