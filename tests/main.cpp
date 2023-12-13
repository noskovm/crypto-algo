#include <iostream>
#include <random>
#include <cmath>
#include <numeric>
#include "primality_test.h"
#include <boost/math/common_factor.hpp>
#include "elgamal.h"
#include "utils.h"
#include "magenta.h"
#include <string>
#include <cstdint>

int main() {
    setlocale(LC_ALL, "ru");
    system("chcp 65001");

    std::bitset<128> x("01101010110100110000011011100110111010011101010101010011101111000000000000000000000000000000000000000000001100010111100101100110");
    std::bitset<64> key1("11010101101001100000110111001101110");
    std::bitset<64> key2("1010100111011100010000000010000000");
    std::vector<std::bitset<8>> bytes1 = getByteArray8(x);

    std::bitset<128> KEY(key1.to_string() + key2.to_string());
    std::vector<std::bitset<8>> batck_key = getByteArray8(KEY);




    std::bitset<128> encrypted = encrypt(x, key1, key2);
    std::bitset<128> decrypted = decrypt(encrypted, key1, key2);

    std::cout << decrypted;


    return 0;
}
