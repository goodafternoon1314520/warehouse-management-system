#include <iostream>

#include "../include/RSAManager.h"

int main() {
    std::string plaintext = "Hello Warehouse AES Key!";
    std::cout << "Original: " << plaintext << std::endl;

    std::string cipher = RSAManager::encrypt(plaintext, "../keys/server_public.pem");

    std::cout << "Cipher size: " << cipher.size() << std::endl;

    std::string decrypted = RSAManager::decrypt(cipher, "../keys/server_private.pem");

    std::cout << "Decrypted: " << decrypted << std::endl;

    if (plaintext == decrypted)
        std::cout << "RSA Encrypt/Decrypt test PASSED!\n";
    else
        std::cout << "RSA Encrypt/Decrypt test FAILED!\n";

    return 0;
}