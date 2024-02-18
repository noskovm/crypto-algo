#ifndef CRYPTO_ALGO_FILE_UTILS_H
#define CRYPTO_ALGO_FILE_UTILS_H
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <vector>
#include <bitset>
#include <limits>

std::vector<std::bitset<128>> block_processing(const boost::dynamic_bitset<>& input_data);

boost::dynamic_bitset<> read_file(std::ifstream& file);

void write_to_file(const std::bitset<128>& bitset, std::ofstream& file);

std::bitset<128> pkcs7_padding(const boost::dynamic_bitset<>& input, size_t block_size);

#endif //CRYPTO_ALGO_FILE_UTILS_H
