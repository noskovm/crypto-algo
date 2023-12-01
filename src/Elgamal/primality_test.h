#ifndef CRYPTO_ALGO_PRIMALITY_TEST_H
#define CRYPTO_ALGO_PRIMALITY_TEST_H

#include <iostream>
#include <random>
#include <cmath>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "spdlog/spdlog.h"
#include "utils.h"

using boost::multiprecision::cpp_int;

const int MIN_NUMBER_PRIM_TEST = 3; // левая граница диапазона поиска чисел 'a' из теста Соловея-Штрассена


// Интерфейс для класса Вероятностной проверки простоты. Контракт - check_primary - проверить на простоту
class IPrimalityTest {
public:
    virtual bool check_primary(cpp_int value, double minProb) = 0;
};

/* Абстрактный класс, реализующий 2 предварительные проверки
 * 1) Четность проверяемого значения(false если да)
 * 2) Проверка на корректность входящего диапазона вероятностей
*/
class PrimalityTest: public IPrimalityTest {
private:
    bool checkMinProbRange(double minProb);
    bool checkEvenNumber(const cpp_int &value);
public:
    bool checkProbRangeAndEvenNumber(const cpp_int &value, double minProb);
};

// Тест Ферма, реализующий абстрактный класс PrimalityTest
class FermatTest: public PrimalityTest {
public:
    bool check_primary(cpp_int value, double minProb) override;
};

// Тест Соловея-Штрассена, реализующий абстрактный класс PrimalityTest
class SolovayStrassenTest: public PrimalityTest {
public:
    bool check_primary(cpp_int value, double minProb) override;
};

// Тест Миллера-Рабина, реализующий абстрактный класс PrimalityTest
class MillerRabinTest: public PrimalityTest {
public:
    bool check_primary(cpp_int value, double minProb) override;
};

#endif // CRYPTO_ALGO_PRIMALITY_TEST_H