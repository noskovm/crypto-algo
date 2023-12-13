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

    std::bitset<128> M(23423441);
    //std::cout << "Open text " << std::endl << M.to_string() << std::endl;
    std::bitset<64> key1(3242342);
    std::bitset<64> key2(562312);


    return 0;
}
