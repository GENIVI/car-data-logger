#ifndef CLIENTAUTHENTICATIONDECRYPTIONHANDLER_H
#define CLIENTAUTHENTICATIONDECRYPTIONHANDLER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class ClientAuthenticationDecryptionHandler
{
public:
    ClientAuthenticationDecryptionHandler();
    virtual ~ClientAuthenticationDecryptionHandler();

private:
    void init();
    vector<string> stringSplit(string key, string delimiter);

public:
    virtual string decodePrivateKey(string privateKey);

private:
    map<int, char> m_keyMapTable;
};

#endif // CLIENTAUTHENTICATIONDECRYPTIONHANDLER_H
