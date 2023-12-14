#include "elg_file_processing.h"
#include "elgamal.h"

void e_encrypt_file(std::string inputFilePath,
                     std::string outputFilePath,
                     cpp_int y,
                     cpp_int g,
                     cpp_int p) {
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    std::ofstream outputFile(outputFilePath, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Error while opening file" << std::endl;
        return;
    }

    Elgamal alg;
    char* buffer = new char[4]; // 32 бита
    while (inputFile.read(buffer, 4)) {
        unsigned long current = *(reinterpret_cast<unsigned long*>(buffer));
        std::pair<cpp_int, cpp_int> encrypted_data = alg.encrypt(cpp_int(current), y, g, p);
        unsigned long long cur1 = (unsigned long long)encrypted_data.first;
        unsigned long long cur2 = (unsigned long long)encrypted_data.second;
        outputFile.write(reinterpret_cast<char*>(&cur1), 8);
        outputFile.write(reinterpret_cast<char*>(&cur2), 8);
    }
    inputFile.close();
    outputFile.close();
}

void e_decrypt_file(std::string inputFilename,
                     std::string outputFilename,
                     cpp_int x,
                     cpp_int p) {
    std::ifstream inputFile(inputFilename, std::ios::binary);
    std::ofstream outputFile(outputFilename, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "error when opening file";
    }

    Elgamal alg;

    char* buffer1 = new char[8]; // 32 бита
    char* buffer2 = new char[8]; // 32 бита

    while(inputFile.read(buffer1, 8) && inputFile.read(buffer2, 8)){
        unsigned long long a = *(reinterpret_cast<unsigned long long*>(buffer1));
        unsigned long long b = *(reinterpret_cast<unsigned long long*>(buffer2));
        cpp_int decrypted_data = alg.decrypt(a, b, x, p);
        unsigned long current = (unsigned long)(decrypted_data);
        outputFile.write(reinterpret_cast<char*>(&current), 4);
    }
    inputFile.close();
    outputFile.close();
}
