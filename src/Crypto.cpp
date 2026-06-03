#include "../include/Crypto.h"

#include <openssl/evp.h>
#include <openssl/rand.h>

#include <vector>
#include <stdexcept>
#include <cstring>

// 加密函数
std::vector<unsigned char> Crypto::encryptAES(const std::string& plaintext, const std::vector<unsigned char>& key, const std::vector<unsigned char>& iv) {
    // 创建上下文
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx)
        throw std::runtime_error("Create cipher ctx failed");

    // 初始化
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encrypt init failed");
    }

    // 设置IV长度
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Set IV length failed");
    }

    if (EVP_EncryptInit_ex(ctx, nullptr, nullptr, key.data(),iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encrypt init key/iv failed");
    }

    // 准备输出
    std::vector<unsigned char> ciphertext(plaintext.size());

    // 加密
    int len = 0;

    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encrypt update failed");
    }

    // 记录长度
    int ciphertextLen = len;

    // 裁剪
    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encrypt final failed");
    }

    ciphertextLen += len;
    ciphertext.resize(ciphertextLen);

    // 获取tag
    unsigned char tag[16];

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Get tag failed");
    }

    EVP_CIPHER_CTX_free(ctx);

    ciphertext.insert(ciphertext.end(), tag, tag + 16);
    return ciphertext;
}

// 解密函数
std::string Crypto::decryptAES(const std::vector<unsigned char>& ciphertextWithTag, const std::vector<unsigned char>& key, const std::vector<unsigned char>& iv) {
    if (ciphertextWithTag.size() < 16)
        throw std::runtime_error("Ciphertext too short");

    size_t cipherLen = ciphertextWithTag.size() - 16;
    const unsigned char* tag = (ciphertextWithTag.data() + cipherLen);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        throw std::runtime_error("Create cipher ctx failed");

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1) {
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

    std::vector<unsigned char> plaintext(cipherLen);
    int len = 0;
    if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertextWithTag.data(), cipherLen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Decrypt update failed");
    }

    int plaintextLen = len;

    // 设置tag
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, const_cast<unsigned char*>(tag)) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Set tag failed");
    }

    int ret = EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);
    EVP_CIPHER_CTX_free(ctx);

    if (ret <= 0)
        throw std::runtime_error("Authentication failed");

    plaintextLen += ret;
    plaintext.resize(plaintextLen);

    return std::string(reinterpret_cast<char*>(plaintext.data()), plaintext.size());
}

/*
AESContext Crypto::generateAESKey() {
    AESContext ctx;

    unsigned char key[32];
    unsigned char iv[12];

    if (RAND_bytes(key, sizeof(key)) != 1)
        throw std::runtime_error("Generate AES key failed");

    if (RAND_bytes(iv, sizeof(key)) != 1)
        throw std::runtime_error("Generate AES iv failed");

    ctx.key.assign(reinterpret_cast<char*>(key), sizeof(key));
    ctx.iv.assign(reinterpret_cast<char*>(iv), sizeof(iv));

    return ctx;
}
*/