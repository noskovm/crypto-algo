#ifndef CRYPTO_ALGO_KEYS_H
#define CRYPTO_ALGO_KEYS_H

#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

struct Keys {
    cpp_int x;
    cpp_int y;
    cpp_int g;
    cpp_int p;
};


#endif //CRYPTO_ALGO_KEYS_H

