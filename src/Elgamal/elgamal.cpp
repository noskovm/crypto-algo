#include "primality_test.h"
#include "elgamal.h"
#include "keys.h"
#include <iostream>

// keygen
Keys Elgamal::keygen() {
    Keys keys_set;
    cpp_int value = generateRandomFromRangeCPP_INT( (unsigned long long)(LLONG_MAX) + 1, ULLONG_MAX);

    SolovayStrassenTest test;
    while(!test.check_primary(value, 0.9)) {
        value = generateRandomFromRangeCPP_INT((unsigned long long)LLONG_MAX+1, ULLONG_MAX);
    }

    keys_set.p = value;
    keys_set.g = searchGroupGenerator(keys_set.p);

    keys_set.x = generateRandomFromRangeCPP_INT( (unsigned long long)1, (unsigned long long)keys_set.g);
    // маловероятная ситуация, но все же
    while((keys_set.x == keys_set.y) || (keys_set.x == keys_set.g))
        keys_set.x = generateRandomFromRangeCPP_INT( (unsigned long long)1, (unsigned long long)keys_set.g);

    keys_set.y = modPow(keys_set.g, keys_set.x, keys_set.p, true);

    return keys_set;
}

std::pair<cpp_int, cpp_int> Elgamal::encrypt(cpp_int M, cpp_int y, cpp_int g, cpp_int p) {
    if (M > p) std::cout << "M must be small than p!";

    //cpp_int sessionKey = generateRandomFromRangeCPP_INT((unsigned long long)LLONG_MAX+1, ULLONG_MAX);
    cpp_int sessionKey = 13;
    cpp_int a =modPow(g, sessionKey, p, true);
    cpp_int b =((modPow(y, sessionKey, p, true)*M)%p);

    return std::pair<cpp_int, cpp_int>(a, b);
}

cpp_int Elgamal::decrypt(cpp_int a, cpp_int b, cpp_int x, cpp_int p) {
    return ((modPow(a, p - cpp_int(1) - x, p, true)*b%p));
}
