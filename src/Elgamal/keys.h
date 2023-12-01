#ifndef CRYPTO_ALGO_KEYS_H
#define CRYPTO_ALGO_KEYS_H

#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

class PublicKey {
private:
    cpp_int y;
    cpp_int g;
    cpp_int p;

public:
    PublicKey(cpp_int p_y, cpp_int p_g, cpp_int p_p);
};

class PrivateKey {
private:
    cpp_int x;
    cpp_int g;
    cpp_int p;

public:
    PrivateKey(cpp_int p_x, cpp_int p_g, cpp_int p_p);
};



#endif //CRYPTO_ALGO_KEYS_H
