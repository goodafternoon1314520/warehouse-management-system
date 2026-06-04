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
    // 随机生成AES Key + IV
    static AESContext generateAESKey();

    static bool encryptAES_GCM(const std::string& plaintext, const std::vector<unsigned char>& key, std::vector<unsigned char>& iv, std::vector<unsigned char>& ciphertext, std::vector<unsigned char>& tag);
    static bool decryptAES_GCM(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& key, const std::vector<unsigned char>& iv, const std::vector<unsigned char>& tag, std::string& plaintext);
};

#endif