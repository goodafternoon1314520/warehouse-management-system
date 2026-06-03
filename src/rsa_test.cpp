#include "../include/RSAUtil.h"

#include <iostream>

int main() {
    std::string text = "Hello AES Key";

    auto encrypted = RSAUtil::encrypt(text, "../certs/public.pem");
    auto decrypted = RSAUtil::decrypt(encrypted, "../certs/private.pem");

    std::cout << decrypted << std::endl;

    return 0;
}