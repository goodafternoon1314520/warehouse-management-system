#include "../include/RSAManager.h"

#include <iostream>

int main() {
    bool ok = RSAManager::generateKeyPair("../keys/server_public.pem", "../keys/server_private.pem");

    if (ok)
        std::cout << "RSA key pair generated\n";
    else
        std::cout << "Generate failed\n";

    return 0;
}