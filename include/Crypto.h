#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <vector>

struct AESContext {
    std::vector<unsigned char> key; // 32字节
    std::vector<unsigned char> iv; // 12字节
};

class Crypto {
public:
    static std::vector<unsigned char> encryptAES(const std::string& plaintext, const std::vector<unsigned char>& key, const std::vector<unsigned char>& iv);
    static std::string decryptAES(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& key, const std::vector<unsigned char>& iv);

    // 随机生成AES Key + IV
    static AESContext generateAESKey();
};

#endif