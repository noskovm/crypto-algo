#include "mag_file_processing.h"
#include "magenta.h"

void magenta_encrypt_file(std::string filePath, std::bitset<64> key1, std::bitset<64> key2) {
    std::ifstream f(filePath, std::ios::binary);
    if(!f.is_open()) {
        std::cout << "error open file";
        return;
    }

    //считываем весь файл в bitset
    boost::dynamic_bitset<> whole_file = read_file(f);
    f.close();

    std::ofstream out("out", std::ios::binary);

    // записываем шифрованный bitset
    std::vector<std::bitset<128>> setBits = block_processing(whole_file);
    for (int i = 0;i < setBits.size(); ++i) {
        std::bitset<128>cipher = encrypt(setBits[i], key1, key2);
        write_to_file(cipher, out);
    }
    out.close();
}

void magenta_decrypt_file(std::string filePath,  std::bitset<64> key1, std::bitset<64> key2, std::string ext) {
    std::ifstream f1(filePath, std::ios::binary);
    if(!f1.is_open()) {
        std::cout << "error open file";
        return;
    }
    boost::dynamic_bitset<> whole_file = read_file(f1);
    f1.close();
    std::ofstream out(filePath + "_decrypt" + ext, std::ios::binary);

    std::vector<std::bitset<128>> set = block_processing(whole_file);
    for (int i = 0;i < set.size(); ++i) {
        std::bitset<128>open = decrypt(set[i], key1, key2);
        write_to_file(open, out);
    }
    out.close();
}