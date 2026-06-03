#include "../include/RSAUtil.h"

#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

#include <vector>
#include <stdexcept>

std::string RSAUtil::encrypt(const std::string& plainText, const std::string& publicKeyPath) {
    FILE* fp = fopen(publicKeyPath.c_str(), "r");

    if (!fp)
        throw std::runtime_error("Cannot open public key");

    EVP_PKEY* pkey = PEM_read_PUBKEY(fp, nullptr, nullptr, nullptr);

    fclose(fp);

    if (!pkey)
        throw std::runtime_error("Read public key failed");

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);

    if (!ctx) {
        EVP_PKEY_free(pkey);
        throw std::runtime_error("Create ctx failed");
    }

    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);

        throw std::runtime_error("Encrypt init failed");
    }

    size_t outLen = 0;

    EVP_PKEY_encrypt(ctx, nullptr, &outLen, reinterpret_cast<const unsigned char*>(plainText.data()), plainText.size());

    std::vector<unsigned char> out(outLen);

    if (EVP_PKEY_encrypt(ctx, out.data(), &outLen, reinterpret_cast<const unsigned char*>(plainText.data()), plainText.size()) <= 0) {
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);

        throw std::runtime_error("Encrypt failed");
    }

    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);

    return std::string(reinterpret_cast<char*>(out.data()), outLen);
}

std::string RSAUtil::decrypt(const std::string& cipherText, const std::string& privateKeyPath) {
    FILE* fp = fopen(privateKeyPath.c_str(), "r");

    if (!fp)
        throw std::runtime_error("Cannot open private key");

    EVP_PKEY* pkey = PEM_read_PrivateKey(fp, nullptr, nullptr, nullptr);
    fclose(fp);

    if (!pkey)
        throw std::runtime_error("Read private key failed");

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);

    if (!ctx) {
        EVP_PKEY_free(pkey);

        throw std::runtime_error("Create ctx failed");
    }

    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);

        throw std::runtime_error("Decrypt init failed");
    }

    size_t outLen = 0;

    EVP_PKEY_decrypt(ctx, nullptr, &outLen, reinterpret_cast<const unsigned char*>(cipherText.data()), cipherText.size());
    std::vector<unsigned char> out(outLen);

    if (EVP_PKEY_decrypt(ctx, out.data(), &outLen, reinterpret_cast<const unsigned char*>(cipherText.data()), cipherText.size()) <= 0) {
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);

        throw std::runtime_error("Decrypt failed");
    }

    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);

    return std::string(reinterpret_cast<char*>(out.data()), outLen);
}