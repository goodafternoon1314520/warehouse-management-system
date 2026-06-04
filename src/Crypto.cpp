#include "../include/Crypto.h"

#include <openssl/evp.h>
#include <openssl/rand.h>

#include <stdexcept>
#include <cstring>

AESContext Crypto::generateAESKey() {
    AESContext ctx;
    ctx.key.resize(32);
    ctx.iv.resize(12);
    RAND_bytes(ctx.key.data(), ctx.key.size());
    RAND_bytes(ctx.iv.data(), ctx.iv.size());
    return ctx;
}

// 加密函数
bool Crypto::encryptAES_GCM(const std::string& plaintext, const std::vector<unsigned char>& key, std::vector<unsigned char>& iv, std::vector<unsigned char>& ciphertext, std::vector<unsigned char>& tag) {
    if (iv.empty()) {
        iv.resize(12);
        RAND_bytes(iv.data(), iv.size());
    }

    // 创建上下文
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx)
        throw std::runtime_error("Create cipher ctx failed");

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encrypt init failed");
    }

    ciphertext.resize(plaintext.size());
    tag.resize(16); // GCM Tag 长度固定16字节

    // 设置IV长度
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Set IV length failed");
    }

    if (EVP_EncryptInit_ex(ctx, nullptr, nullptr, key.data(),iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encrypt init key/iv failed");
    }

    // 加密
    int len = 0;

    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encrypt update failed");
    }

    int tmplen = 0;

    // 裁剪
    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &tmplen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encrypt final failed");
    }

    ciphertext.resize(len + tmplen);

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, tag.size(), tag.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Get tag failed");
    }

    EVP_CIPHER_CTX_free(ctx);

    return true;
}

// 解密函数
bool Crypto::decryptAES_GCM(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& key, const std::vector<unsigned char>& iv, const std::vector<unsigned char>& tag, std::string& plaintext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        throw std::runtime_error("Create cipher ctx failed");

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Decrypt init failed");
    }

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Set IV length failed");
    }

    if (EVP_DecryptInit_ex(ctx, nullptr, nullptr, key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Decrypt init key/iv failed");
    }

    plaintext.resize(ciphertext.size());
    int len = 0;
    if (EVP_DecryptUpdate(ctx, (unsigned char*)plaintext.data(), &len, ciphertext.data(), ciphertext.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Decrypt update failed");
    }

    // 设置tag
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, tag.size(), (void*)tag.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Set tag failed");
    }

    int tmplen = 0;
    if (EVP_DecryptFinal_ex(ctx, (unsigned char*)plaintext.data() + len, &tmplen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Authentication failed");
    }

    plaintext.resize(len + tmplen);

    EVP_CIPHER_CTX_free(ctx);
    return true;
}