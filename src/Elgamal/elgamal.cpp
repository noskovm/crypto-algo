#include "primality_test.h"
#include "elgamal.h"
#include "keys.h"
#include <iostream>

//
Elgamal::Elgamal() {

}

//TODO опять дублирование
Keys Elgamal::keygen() {
    Keys keys_set;
    cpp_int value = generateRandomFromRangeCPP_INT( (unsigned long long)(LLONG_MAX) + 1, ULLONG_MAX);

    SolovayStrassenTest test;
    while(!test.check_primary(value, 0.9)) {
        value = generateRandomFromRangeCPP_INT((unsigned long long)LLONG_MAX+1, ULLONG_MAX);
    }

    keys_set.p = value;
    keys_set.g = searchGroupGenerator(keys_set.p);

    keys_set.x = generateRandomFromRangeCPP_INT( (unsigned long long)(LLONG_MAX) + 1, ULLONG_MAX);
    // маловероятная ситуация, но все же
    while((keys_set.x == keys_set.y) || (keys_set.x == keys_set.g))
        keys_set.x = generateRandomFromRangeCPP_INT( (unsigned long long)(LLONG_MAX) + 1, ULLONG_MAX);

    keys_set.y = modPow(keys_set.g, keys_set.x, keys_set.p, true);

    return keys_set;
}


