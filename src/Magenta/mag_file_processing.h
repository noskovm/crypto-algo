#ifndef CRYPTO_ALGO_MAG_FILE_PROCESSING_H
#define CRYPTO_ALGO_MAG_FILE_PROCESSING_H

#include <bitset>
#include <fstream>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <filesystem>

#include "file_utils.h"

std::string remove_extension(const std::string& filename);

void magenta_encrypt_file(std::string inputFilePath, std::string outputFilePath, std::bitset<64> key1, std::bitset<64> key2);

void magenta_decrypt_file(std::string inputFilePath, std::string outputFilePath,  std::bitset<64> key1, std::bitset<64> key2);

#endif //CRYPTO_ALGO_MAG_FILE_PROCESSING_H
