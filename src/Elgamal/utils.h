#ifndef CRYPTO_ALGO_UTILS_H
#define CRYPTO_ALGO_UTILS_H

#include <iostream>
#include <random>
#include <cmath>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "spdlog/spdlog.h"

using boost::multiprecision::cpp_int;



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


#endif //CRYPTO_ALGO_UTILS_H
