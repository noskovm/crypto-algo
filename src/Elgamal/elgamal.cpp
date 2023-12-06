#include "primality_test.h"
#include "elgamal.h"
#include "keys.h"
#include <iostream>

//TODO опять дублирование
Keys Elgamal::keygen() {
    Keys keys_set;
    cpp_int value = generateRandomFromRangeCPP_INT( (unsigned long long)(LLONG_MAX) + 1, ULLONG_MAX);

    SolovayStrassenTest test;
    while(!test.check_primary(value, 0.9)) {
        value = generateRandomFromRangeCPP_INT((unsigned long long)LLONG_MAX+1, ULLONG_MAX);
    }

    keys_set.p = value;
    keys_set.g = searchGroupGenerator(keys_set.p);

    keys_set.x = generateRandomFromRangeCPP_INT( (unsigned long long)1, (unsigned long long)keys_set.g);
    // маловероятная ситуация, но все же
    while((keys_set.x == keys_set.y) || (keys_set.x == keys_set.g))
        keys_set.x = generateRandomFromRangeCPP_INT( (unsigned long long)1, (unsigned long long)keys_set.g);

    keys_set.y = modPow(keys_set.g, keys_set.x, keys_set.p, true);

    return keys_set;
}

void Elgamal::encrypt(std::string filePath) {
    std::ifstream inputFile;
    inputFile.open(filePath, std::ios::binary);

    if (!inputFile.is_open())
        return;


    std::cout << "open" << std::endl;

    // заводим область памати на 64 бита
    char* buffer = new char[16]; //64 бита

    //считываем символы в буфер
    inputFile.read (buffer,16);

    // переводим кусок памяти, указывающий на char* в указатель unsigned long long*
    unsigned long long openNumber = *(reinterpret_cast<unsigned long long*>(&buffer));
    std::cout << openNumber << std::endl;

    //__________________________________

    Elgamal alg;
    Keys keys = alg.keygen();

    cpp_int sessionKey = 13;
    unsigned long long a = (unsigned long long)modPow(keys.g, sessionKey, keys.p, true);
    unsigned long long b = (unsigned long long)((modPow(keys.y, sessionKey, keys.p, true)*openNumber)%keys.p);

    //std::cout << "Pair chifrtext" << a << "," << b << std::endl;

    std::cout << "Decrypt " << std::endl;

    unsigned long long M = (unsigned long long)((modPow(cpp_int(a), keys.p - cpp_int(1) - keys.x, keys.p, true)*cpp_int(b)%keys.p));

    std::cout << keys.p << std::endl << keys.x << std::endl;
    std::cout << keys.p - cpp_int(1) - keys.x << std::endl;
    std::cout << M << std::endl;

    // заводим другую область памяти
    char* buffer_other = new char[16];
    // интерпретируем unsigned long long* в char*
    buffer_other = reinterpret_cast<char*>(M);
    std::cout << *(buffer_other + 15);

    //____________--

    inputFile.close();

}


