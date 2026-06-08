#include "../include/SecureChannel.h"
#include "../include/Crypto.h"
#include "../generated/proto/warehouse.pb.h"

bool SecureChannel::encryptMessage(const std::string& plaintext, const std::vector<unsigned char>& aesKey, std::string& secureData) {
    std::vector<unsigned char> iv;
    std::vector<unsigned char> cipher;
    std::vector<unsigned char> tag;

    Crypto::encryptAES_GCM(plaintext, aesKey, iv, cipher, tag);

    warehouse::SecureMessage secureMsg;

    secureMsg.set_iv(iv.data(), iv.size());
    secureMsg.set_tag(tag.data(), tag.size());
    secureMsg.set_cipher(cipher.data(), cipher.size());

    return secureMsg.SerializeToString(&secureData);
}

bool SecureChannel::decryptMessage(const std::string& secureData, const std::vector<unsigned char>& aesKey, std::string& plaintext) {
    warehouse::SecureMessage secureMsg;

    if (!secureMsg.ParseFromString(secureData))
        return false;

    std::vector<unsigned char> iv(secureMsg.iv().begin(), secureMsg.iv().end());
    std::vector<unsigned char> tag(secureMsg.tag().begin(), secureMsg.tag().end());
    std::vector<unsigned char> cipher(secureMsg.cipher().begin(), secureMsg.cipher().end());

    return Crypto::decryptAES_GCM(cipher, aesKey, iv, tag, plaintext);
}

