#include <iostream>
#include <random>
#include <cmath>
#include <numeric>
#include "primality_test.h"
#include <boost/math/common_factor.hpp>
#include "elgamal.h"
#include "utils.h"
/*
 * rand() % 100 + 1;     // v2 in the range 1 to 100
 *
 * std::uniform_int_distribution<> distrib(1, 6); generated by gen into an int in [1, 6]
 */

//#include <boost/program_options.hpp>

bool yes(IPrimalityTest &test) {
    return test.check_primary(2, 0.8);
}

int main() {
    setlocale(LC_ALL, "ru");
    system("chcp 65001");

    Elgamal alg;
    Keys keys = alg.keygen();
    std::cout << keys.x << std::endl;
    std::cout << keys.y << std::endl;
    std::cout << keys.g << std::endl;
    std::cout << keys.p << std::endl;

    SolovayStrassenTest test;

    //std::cout << searchGroupGenerator(cpp_int("19"));
    return 0;
}
