#include "primality_test.h"

// Методы Абстрактного класса PrimalityTest
bool PrimalityTest::checkMinProbRange(const double minProb) {
    return (minProb >= 0.5 && minProb < 1);
}
bool PrimalityTest::checkEvenNumber(const cpp_int &value) {
    return (value > 2 && (value&1)==0);
}
bool PrimalityTest::checkProbRangeAndEvenNumber(const cpp_int &value, double minProb) {
    if (!::PrimalityTest::checkMinProbRange(minProb))
        return false; //TODO придумать действия при ошибках как в контрактах
    if (::PrimalityTest::checkEvenNumber(value))
        return false;
    if (value <= MIN_NUMBER_PRIM_TEST)
        return false;
    return true;
}
//

// Тест Ферма
bool FermatTest::check_primary(cpp_int value, double minProb) {
    if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
        return false;
    return true;
    //TODO реализовать
}
//

// Тест Соловея-Штрассена
bool SolovayStrassenTest::check_primary(cpp_int value, double minProb) {
    if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
        return false;
    //TODO пока ночь и я глупый, буду поступать итеративно, а не высчитаю кол-во шагов k сразу. Исправить

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> dist((unsigned long long)MIN_NUMBER_PRIM_TEST,(unsigned long long)(value - 2));
    // TODO ВАЖНО: выше очень опасный момент с приведением типов, будем охватывать только половину диапазона cpp_int

    cpp_int randA;
    double curProb;
    // TODO пересмотреть?
    int steps = boost::math::lround(log2(1 / (1 - minProb)) + 0.5) + 1;
    for (int i = 0; i < steps; ++i) {
        randA = dist(gen);
        if (gcd_euclid(randA, value) > 1)
            return false;
        if (modPow(randA, (value-1)/2, value, true) != (value + jacobi(randA, value)) % value) {
            return false;
        }
        curProb = 1 - pow(2, -i);
    }

    return true;
}
//

// Тест Миллера-Рабина
bool MillerRabinTest::check_primary(cpp_int value, double minProb) {
    if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
        return false;
    return true;
    //TODO реализовать
}
//
