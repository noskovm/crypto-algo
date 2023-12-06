//
// Created by noskovm on 12/2/2023.
//

#ifndef CRYPTO_ALGO_ELGAMAL_H
#define CRYPTO_ALGO_ELGAMAL_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "spdlog/spdlog.h"
#include "keys.h"
#include <climits>
#include <fstream>
#include <string>
#include <vector>

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
    Keys keygen();
    void encrypt(std::string filePath);
//    void decrypt();
    //std::pair<PublicKey, PrivateKey> keygen();
};

#endif //CRYPTO_ALGO_ELGAMAL_H
