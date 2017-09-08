#ifndef CLIENTAUTHENTICATIONENCRYPTIONHANDLER_H
#define CLIENTAUTHENTICATIONENCRYPTIONHANDLER_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class ClientAuthenticationEncryptionHandler
{
public:
    ClientAuthenticationEncryptionHandler();
    virtual ~ClientAuthenticationEncryptionHandler();

private:
    void init();

public:
    virtual string createPrivateKey(string publicKey);  //encryptionPublicKey

private:
    map<char, int> m_keyMapTable;
};

#endif // CLIENTAUTHENTICATIONENCRYPTIONHANDLER_H
