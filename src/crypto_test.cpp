#include "../include/Crypto.h"

#include <iostream>
#include <openssl/rand.h>

int main() {
    std::vector<unsigned char> key(32);
    std::vector<unsigned char> iv(12);

    RAND_bytes(key.data(), key.size());
    RAND_bytes(iv.data(), iv.size());

    std::string text = "admin:123456";

    auto encrypted = Crypto::encryptAES(text, key, iv);
    auto decrypted = Crypto::decryptAES(encrypted, key, iv);

    std::cout << decrypted << std::endl;
}