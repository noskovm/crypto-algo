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

    std::uintmax_t size = std::filesystem::file_size(filePath);

    long steps = size/16 + size%16;

    std::vector<std::pair<unsigned long long, unsigned long long>> openNumbers;

    Elgamal alg;
    Keys keys = alg.keygen();


    for (long i = 0; i < steps; ++i) {
        char* buffer = new char[16]; //64 бита
        inputFile.read (buffer,16);
        unsigned long long current = (*(reinterpret_cast<unsigned long long*>(&buffer)));
        cpp_int sessionKey = 13;
        unsigned long long a = (unsigned long long)modPow(keys.g, sessionKey, keys.p, true);
        unsigned long long b = (unsigned long long)((modPow(keys.y, sessionKey, keys.p, true)*current)%keys.p);

        openNumbers.push_back(std::pair(a, b));

    }


    std::ofstream outFile("out2.jpg", std::ios::binary);
    for (long i = 0; i < steps; ++i) {
        unsigned long long M = (unsigned long long)((modPow(cpp_int(openNumbers[i].first), keys.p - cpp_int(1) - keys.x, keys.p, true)*cpp_int(openNumbers[i].second)%keys.p));
        // заводим другую область памяти
        char* buffer_other = new char[16];
        // интерпретируем unsigned long long* в char*
        buffer_other = reinterpret_cast<char*>(M);
        outFile.write(buffer_other, 16);
    }

    inputFile.close();

}


