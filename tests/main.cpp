#include <iostream>
#include <random>
#include <cmath>
#include <numeric>
#include "primality_test.h"
#include <boost/math/common_factor.hpp>
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

    SolovayStrassenTest test;

    std::cout << yes(test);

    std::cout << boost::math::gcd(6, 15);
    return 0;
}
