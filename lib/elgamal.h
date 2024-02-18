//
// Created by noskovm on 12/2/2023.
//

#ifndef CRYPTO_ALGO_ELGAMAL_H
#define CRYPTO_ALGO_ELGAMAL_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "keys.h"
#include <climits>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using boost::multiprecision::cpp_int;

class Elgamal {
public:
//    Elgamal();
//    class KeyGen {
//    public:
//        KeyGen() = default;
//        enum PrimeTest {
//            FERMAT,
//            SOLOVAYSTRASSEN,
//            MILLERRABIN
//        };
//    private:
//        PrimeTest primeTest;
//        double minProb;
//        int keyBitLength;
//    };

    // key generation
    Keys keygen();

    // opentext, y, g, p
    std::pair<cpp_int, cpp_int> encrypt(cpp_int M, cpp_int y, cpp_int g, cpp_int p);

    // a,b,x,p
    cpp_int decrypt(cpp_int a, cpp_int b, cpp_int x, cpp_int p);
};

#endif //CRYPTO_ALGO_ELGAMAL_H
