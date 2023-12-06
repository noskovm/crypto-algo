#ifndef CRYPTO_ALGO_KEYS_H
#define CRYPTO_ALGO_KEYS_H

#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

typedef struct Keys Keys;

struct Keys {
    cpp_int x;
    cpp_int y;
    cpp_int g;
    cpp_int p;
};

struct Ckeys {
    unsigned long long x;
    unsigned long long y;
    unsigned long long g;
    unsigned long long p;
};

#endif //CRYPTO_ALGO_KEYS_H

