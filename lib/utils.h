#ifndef CRYPTO_ALGO_UTILS_H
#define CRYPTO_ALGO_UTILS_H

#include <iostream>
#include <random>
#include <cmath>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <climits>

using boost::multiprecision::cpp_int;

    void hello();
    // modPow выполняет операцию возведения в степень по модулю
    cpp_int modPow(cpp_int base, cpp_int pow, const cpp_int &mod, bool use_boost);

    /* возвращает первообразный корень группы по модулю p
     * работает на алгоритме Полларда
     */
    cpp_int searchGroupGenerator(cpp_int p);

    // возвращает случайное число из диапазона
    cpp_int generateRandomFromRangeCPP_INT(cpp_int p_min, cpp_int p_max);

    // модуль для cpp_int
    cpp_int cpp_abs(cpp_int value);

    // алгоритм нахождения НОД для больших чисел
    cpp_int gcd_euclid(cpp_int u, cpp_int v);

    // функция нелинейного преобразования, необходимая в функции searchGroupGenerator
    cpp_int simple_f(cpp_int x);

    // jacobi находит символ Яккоби
    cpp_int jacobi(cpp_int a, cpp_int n);


#endif //CRYPTO_ALGO_UTILS_H
