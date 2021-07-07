#include "CServiceA.h"
#include <cstring>
#include <iostream>

CServiceA_i::CServiceA_i()
{
}

CServiceA_i::~CServiceA_i()
{
}

char *CServiceA_i::HelloWorld(const char *)
{
    return CORBA::string_dup("Hello, world!");
}

CORBA::Boolean CServiceA_i::Div(CORBA::Long a, CORBA::Long b, CORBA::Long &r)
{
    r = 0;
    if (b == 0)
    {
        r = 0;
        return false; // error
    }
    r = a / b;
    return true; // success
}

void CServiceA_i::CaesarCipher(char *&str, CORBA::Short k)
{
    for (size_t i = 0, size = strlen(str); i < size; ++i)
    {
        bool lower = ('a' <= str[i] && str[i] <= 'z');
        bool upper = ('A' <= str[i] && str[i] <= 'Z');
        if (lower || upper)
        {
            short t = ('a' ^ (upper ? 32 : 0));
            str[i] = static_cast<char>((str[i] - t + k) % ('z' - 'a' + 1) + t);
        }
    }
}
