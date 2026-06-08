#ifndef SECURECHANNEL_H
#define SECURECHANNEL_H

#include <string>
#include <vector>

class SecureChannel {
public:
    static bool encryptMessage(const std::string& plaintext, const std::vector<unsigned char>& aesKey, std::string& secureData);

    static bool decryptMessage(const std::string& secureData, const std::vector<unsigned char>& aesKey, std::string& plaintext);
};


#endif