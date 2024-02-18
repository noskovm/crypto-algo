#ifndef CRYPTO_ALGO_ELG_FILE_PROCESSING_H
#define CRYPTO_ALGO_ELG_FILE_PROCESSING_H

#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;


void e_encrypt_file(std::string inputFilePath,
                    std::string outputFilePath,
                    cpp_int y,
                    cpp_int g,
                    cpp_int p);

void e_decrypt_file(std::string inputFilename,
                    std::string outputFilename,
                    cpp_int x,
                    cpp_int p);

#endif //CRYPTO_ALGO_ELG_FILE_PROCESSING_H
