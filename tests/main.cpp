#include <iostream>
#include <random>
#include <cmath>
#include <numeric>
#include "primality_test.h"
#include <boost/math/common_factor.hpp>
#include "elgamal.h"
#include "utils.h"


bool yes(IPrimalityTest &test) {
    return test.check_primary(2, 0.8);
}

int main() {
    setlocale(LC_ALL, "ru");
    system("chcp 65001");

    Elgamal alg;

    alg.encrypt("C:\\Users\\noskovm\\CLionProjects\\crypto-algo\\file.txt");

    return 0;
}
