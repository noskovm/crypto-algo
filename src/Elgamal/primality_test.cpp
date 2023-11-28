#include "primality_test.h"

//TODO реализовать возведение в степень по модулю и вынести в отдельный файл
int modPow(int base, int exp, int modulus) {
    base %= modulus;
    int result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

// Методы Абстрактного класса PrimalityTest
bool PrimalityTest::checkMinProbRange(double minProb) {
    return (minProb >= 0.5 && minProb < 1);
}
bool PrimalityTest::checkEvenNumber(int value) {
    return (value > 2 && (value % 2)==0); //TODO подумать об эффективной проверке на четность(последний бит)
}
bool PrimalityTest::checkProbRangeAndEvenNumber(int value, double minProb) {
    if (!::PrimalityTest::checkMinProbRange(minProb))
        return false; //TODO придумать действия при ошибках как в контрактах
    if (::PrimalityTest::checkEvenNumber(value))
        return false;
    return true;
}
//

// Тест Ферма
bool FermatTest::check_primary(int value, double minProb) {
    if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
        return false;
    return true;
    //TODO реализовать
}
//

// Тест Соловея-Штрассена
bool SolovayStrassenTest::check_primary(int value, double minProb) {
    if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
        return false;
    //TODO пока ночь и я глупый, буду поступать итеративно, а не высчитаю кол-во шагов k сразу. Исправить
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()

    std::uniform_int_distribution<> distrib(MIN_NUMBER_PRIM_TEST, value - 2);
    int randA;
    int k = 0;
    double curProb = 1 - pow(2, k); // 0

    while (curProb < minProb) {
        randA = distrib(gen);
        if (std::gcd(randA, value) > 1)
            return false;
        if (modPow(randA, (value - 1)/2, value) == modPow(randA/value, 1, value))
            return false;
        k += 1;
        curProb = 1 - pow(2, -k);
    }
    return true;
}
//

// Тест Миллера-Рабина
bool MillerRabinTest::check_primary(int value, double minProb) {
    if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
        return false;
    return true;
    //TODO реализовать
}
//
