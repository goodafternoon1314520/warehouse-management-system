#include "../include/Crypto.h"
#include "../generated/proto/warehouse.pb.h"

#include <iostream>
#include <openssl/rand.h>

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // 1. 构造LoginRequest
    warehouse::LoginRequest req;
    req.set_username("admin");
    req.set_password("123456");

    std::string plaintext;
    if (!req.SerializeToString(&plaintext)) {
        std::cerr << "Serialize LoginRequest failed\n";
        return -1;
    }

    std::cout << "Original plaintext size: " << plaintext.size() << std::endl;

    // 2.生成随机AES Key
    AESContext aesKey = Crypto::generateAESKey();

    std::vector<unsigned char> cipher, iv, tag;

    // 3.加密
    if (!Crypto::encryptAES_GCM(plaintext, aesKey.key, iv, cipher, tag)) {
        std::cerr << "Encrypt failed\n";
        return -1;
    }

    std::cout << "Ciphertext size: " << cipher.size() << std::endl;

    // 4.解密
    std::string decrypted;
    if (!Crypto::decryptAES_GCM(cipher, aesKey.key, iv, tag, decrypted)) {
        std::cerr << "Decrypt failed\n";
        return -1;
    }

    // 5.解析Protobuf
    warehouse::LoginRequest req2;
    if (!req2.ParseFromString(decrypted)) {
        std::cerr << "Parse decrypted string failed\n";
        return -1;
    }

    // 6.输出结果
    std::cout << "Username: " << req2.username() << std::endl;
    std::cout << "Password: " << req2.password() << std::endl;

    return 0;
}