#include "primality_test.h"

// Методы Абстрактного класса PrimalityTest
bool PrimalityTest::checkMinProbRange(const double minProb) {
    return (minProb >= 0.5 && minProb < 1);
}
bool PrimalityTest::checkEvenNumber(const cpp_int &value) {
    return (value > 2 && (value&1)==0);
}
bool PrimalityTest::checkProbRangeAndEvenNumber(const cpp_int &value, double minProb) {
    spdlog::info("Выполняется операция: checkProbRangeAndEvenNumber; проверка допустимости диапазона вероятностей и числа на четность");
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
    spdlog::info("Выполнется операция: SolovayStrassen check_primary; Проверка числа на простоту");
    if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
        return false;
    //TODO пока ночь и я глупый, буду поступать итеративно, а не высчитаю кол-во шагов k сразу. Исправить

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long int> dist(MIN_NUMBER_PRIM_TEST,(unsigned long long)(value - 2));
    // TODO ВАЖНО: выше очень опасный момент с приведением типов, будем охватывать только половину диапазона cpp_int

    unsigned long long randA;
    int k = 0;
    double curProb = 1 - pow(2, k); // 0

    while (curProb < minProb) {
        randA = dist(gen);
        if (boost::math::gcd(randA, value) > 1)
            return false;
        if (modPow(randA, (value - 1)/2, value, true) == modPow(randA/value, 1, value, true))
            return false;
        k += 1;
        curProb = 1 - pow(2, -k);
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
