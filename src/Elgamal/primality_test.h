#pragma once

#include <iostream>
#include <random>
#include <cmath>
#include <numeric>

const int MIN_NUMBER_PRIM_TEST = 3; // левая граница дипазона поиска чисел 'a' из теста Соловея-Штрассена

// modPow выполняет операцию возведения в степень по модулю
int modPow(int base, int exp, int modulus);

// Интерфейс для класса Вероятностной проверки простоты. Контракт - check_primary - проверить на простоту
class IPrimalityTest {
public:
    virtual bool check_primary(int value, double minProb) = 0;
};

/* Абстрактный класс, реализующий 2 предварительные проверки
 * 1) Четность проверяемого значения(false если да)
 * 2) Проверка на корректость входящего диапазона вероятностей
*/
class PrimalityTest: public IPrimalityTest {
private:
    bool checkMinProbRange(double minProb);
    bool checkEvenNumber(int value);
public:
    bool checkProbRangeAndEvenNumber(int value, double minProb);
};

// Тест Ферма, реализующий абстрактный класс PrimalityTest
class FermatTest: public PrimalityTest {
    bool check_primary(int value, double minProb) override;
};

// Тест Соловея-Штрассена, реализующий абстрактный класс PrimalityTest
class SolovayStrassenTest: public PrimalityTest {
    bool check_primary(int value, double minProb) override;
};

// Тест Миллера-Рабина, реализующий абстрактный класс PrimalityTest
class MillerRabinTest: public PrimalityTest {
    bool check_primary(int value, double minProb) override;
};

