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

    long steps = size/8 + size%8;

    std::vector<std::pair<unsigned long long, unsigned long long>> openNumbers;

    Elgamal alg;
    Keys keys = alg.keygen();

    std::ofstream encFile("enc204.txt", std::ios::binary);

    for (long i = 0; i < steps; ++i) {
        char* buffer = new char[8]; //64 бита
        char* buffer_other = new char[8];

        inputFile.read (buffer,8);
        unsigned long long current = (*(reinterpret_cast<unsigned long long*>(&buffer)));
        //std::cout << "current = " << current << std::endl;
        cpp_int sessionKey = 13;
        unsigned long long a = (unsigned long long) modPow(keys.g, sessionKey, keys.p, true);
        unsigned long long b = (unsigned long long)((modPow(keys.y, sessionKey, keys.p, true)*current)%keys.p);

        std::cout << "cur = " << current << std::endl;
        std::cout << "a og = " << a << std::endl;
        std::cout << "b og = " << b << std::endl;

        if (i == 0) {
            char* buffer_sign = new char[8];
            buffer_sign = (reinterpret_cast<char*>(&a));
            encFile.write(buffer_sign, 8);
        }
        buffer_other = (reinterpret_cast<char*>(&b));
        encFile.write(buffer_other, 8);
        //openNumbers.push_back(std::pair(a, b));
    }

    std::ifstream IencFile("enc204.txt", std::ios::binary);
    char* buffer_sign = new char[8];
    IencFile.read (buffer_sign,8);
    unsigned long long a_sign = (*(reinterpret_cast<unsigned long long*>(&buffer_sign)));
    std::ofstream outFile("out204.txt", std::ios::binary);

    std::cout << "a sign = " << a_sign << std::endl;

    for (long i = 0; i < steps; ++i) {
        char* buffer_b = new char[8];
        IencFile.read (buffer_b,8);

        unsigned long long b = (*(reinterpret_cast<unsigned long long*>(&buffer_b)));
        if(i == 0) {
            std::cout << "b " << b << std::endl;
        }
        unsigned long long M = (unsigned long long)((modPow(cpp_int(a_sign), keys.p - cpp_int(1) - keys.x, keys.p, true)*cpp_int(b)%keys.p));
        std::cout << "M = " << M << std::endl;
        // заводим другую область памяти
        char* buffer_other = new char[8];
        // интерпретируем unsigned long long* в char*
        buffer_other = reinterpret_cast<char*>(&M);
        outFile.write(buffer_other, 8);
    }

    inputFile.close();

}


