#include "../include/RSAManager.h"

#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

#include <vector>
#include <stdexcept>

bool RSAManager::generateKeyPair(const std::string& publicKeyFile, const std::string& privateKeyFile) {
    EVP_PKEY* pkey = nullptr;
    EVP_PKEY_CTX* ctx = nullptr;

    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    if (!ctx)
        return false;

    if (EVP_PKEY_keygen_init(ctx) <= 0)
        return false;

    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0)
        return false;

    if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
        return false;

    FILE* pubFile = fopen(publicKeyFile.c_str(), "wb");
    FILE* priFile = fopen(privateKeyFile.c_str(), "wb");

    if (!pubFile || !priFile)
        return false;

    PEM_write_PUBKEY(pubFile, pkey);
    PEM_write_PrivateKey(priFile, pkey, nullptr, nullptr, 0, nullptr, nullptr);

    fclose(pubFile);
    fclose(priFile);

    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);

    return true;
}

std::string RSAManager::encrypt(const std::string& plaintext, const std::string& publicKeyFile) {
    FILE* pubFile = fopen(publicKeyFile.c_str(), "rb");
    if (!pubFile)
        throw std::runtime_error("Cannot open public key file");

    EVP_PKEY* pubKey = PEM_read_PUBKEY(pubFile, nullptr, nullptr, nullptr);
    fclose(pubFile);

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pubKey, nullptr);
    if (!ctx)
        throw std::runtime_error("Create context failed");

    if (EVP_PKEY_encrypt_init(ctx) <= 0)
        throw std::runtime_error("Encrypt init failed");

    size_t outLen = 0;
    if (EVP_PKEY_encrypt(ctx, nullptr, &outLen, reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size()) <= 0)
        throw std::runtime_error("Determine buffer length failed");

    std::vector<unsigned char> out(outLen);

    if (EVP_PKEY_encrypt(ctx, out.data(), &outLen, reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size()) <= 0)
        throw std::runtime_error("Encrypt failed");

    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pubKey);

    return std::string(out.begin(), out.begin() + outLen);
}

std::string RSAManager::decrypt(const std::string& ciphertext, const std::string& privateKeyFile) {
    FILE* priFile = fopen(privateKeyFile.c_str(), "rb");
    if (!priFile)
        throw std::runtime_error("Cannot open private key file");

    EVP_PKEY* priKey = PEM_read_PrivateKey(priFile, nullptr, nullptr, nullptr);
    fclose(priFile);

    if (!priKey)
        throw std::runtime_error("Read private key failed");

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(priKey, nullptr);
    if (!ctx)
        throw std::runtime_error("Create context failed");

    if (EVP_PKEY_decrypt_init(ctx) <= 0)
        throw std::runtime_error("Decrypt init failed");

    size_t outLen = 0;
    if (EVP_PKEY_decrypt(ctx, nullptr, &outLen, reinterpret_cast<const unsigned char*>(ciphertext.data()), ciphertext.size()) <= 0)
        throw std::runtime_error("Determine plaintext length failed");

    std::vector<unsigned char> out(outLen);

    if (EVP_PKEY_decrypt(ctx, out.data(), &outLen, reinterpret_cast<const unsigned char*>(ciphertext.data()), ciphertext.size()) <= 0)
        throw std::runtime_error("Decrypt failed");

    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(priKey);

    return std::string(out.begin(), out.begin() + outLen);
}