#include "utils.h"

cpp_int modPow(cpp_int base, cpp_int pow, const cpp_int &mod, bool use_boost) {
    spdlog::info("Выполняется операция: modPow; Возведение числа в степень по модулю");

    if (use_boost) {
        return  boost::multiprecision::powm(base, pow, mod);
    }
    base %= mod;
    boost::multiprecision::cpp_int result = 1;
    while (pow > 0) {
        if (pow & 1)
            result = (result*base) % mod;
        base = (base * base) % mod;
        pow >>= 1;
    }
    return result;
}


//TODO чет не-то
cpp_int searchGroupGenerator(cpp_int p) {
    cpp_int x = generateRandomFromRangeCPP_INT(2, p-2);
    cpp_int y = x; // int i = 0; int stage = 2;

    x = (x*x + 1)%p;
    y = (((y*y + 1)%p)*((y*y + 1)%p) + 1)%p;
    // TODO дублирование кода
    //std::cout << "gcd" << boost::math::gcd(p, cpp_abs(x - y));
    while (boost::math::gcd(p, cpp_abs(x - y)) == 1)
    {
        x = (x*x + 1)%p;
        y = (((y*y + 1)%p)*((y*y + 1)%p) + 1)%p;
    }

    if (boost::math::gcd(p, cpp_abs(x-y)) == p)
        return searchGroupGenerator(p);

    return boost::math::gcd(p, cpp_abs(x-y));

}

cpp_int generateRandomFromRangeCPP_INT(cpp_int p_min, cpp_int p_max) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long int> dist((unsigned long long)p_min,(unsigned long long)p_max);
    return dist(gen);
}

cpp_int cpp_abs(cpp_int value) {
    if (value < 0)
        return -value;
    return value;
}