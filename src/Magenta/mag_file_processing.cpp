#include "mag_file_processing.h"
#include "magenta.h"
namespace fs = std::filesystem;

void magenta_encrypt_file(std::string inputFilePath, std::string outputFilePath, std::bitset<64> key1, std::bitset<64> key2) {
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    std::ofstream outputFile(outputFilePath, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cout << "Error while opening file" << std::endl;
        return;
    }


    //считываем весь файл в bitset
    boost::dynamic_bitset<> whole_file = read_file(inputFile);
    inputFile.close();

    //std::ofstream out("out", std::ios::binary);

    // записываем шифрованный bitset
    std::vector<std::bitset<128>> setBits = block_processing(whole_file);
    for (int i = 0;i < setBits.size(); ++i) {
        std::bitset<128>cipher = encrypt(setBits[i], key1, key2);
        write_to_file(cipher, outputFile);
    }
    outputFile.close();
}

void magenta_decrypt_file(std::string inputFilePath, std::string outputFilePath,  std::bitset<64> key1, std::bitset<64> key2) {
    std::ifstream inputFile(inputFilePath, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cout << "Error while opening file" << std::endl;
        return;
    }

    
    std::string newOutputName = remove_extension(outputFilePath);
    std::string fileExstension = fs::path(outputFilePath).extension();
    std::ofstream outputFile(newOutputName + fileExstension, std::ios::binary);

    boost::dynamic_bitset<> whole_file = read_file(inputFile);
    inputFile.close();

    std::vector<std::bitset<128>> set = block_processing(whole_file);
    for (int i = 0;i < set.size(); ++i) {
        std::bitset<128>open = decrypt(set[i], key1, key2);
        write_to_file(open, outputFile);
    }
    outputFile.close();
}

std::string remove_extension(const std::string& filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename;
    return filename.substr(0, lastdot); 
}