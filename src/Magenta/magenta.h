#ifndef CRYPTO_ALGO_MAGENTA_H
#define CRYPTO_ALGO_MAGENTA_H

#include <bitset>
#include <vector>

const std::vector<int> S = {
        1, 2, 4, 8, 16, 32, 64, 128, 101, 202, 241, 135, 107, 214, 201, 247, 139,
        115, 230, 169, 55, 110, 220, 221, 223, 219, 211, 195, 227, 163, 35, 70,
        115, 230, 169, 55, 110, 220, 221, 223, 219, 211, 195, 227, 163, 35, 70,
        140, 125, 250, 145, 71, 142, 121, 242, 129, 103, 206, 249, 151, 75, 150,
        73, 146, 65, 130, 97, 194, 225, 167, 43, 86, 172, 61, 122, 244, 141, 127,
        254, 153, 87, 174, 57, 114, 228, 173, 63, 126, 252, 157, 95, 190, 25, 50,
        100, 200, 245, 143, 123, 246, 137, 119, 238, 185, 23, 46, 92, 184, 21, 42,
        84, 168, 53, 106, 212, 205, 255, 155, 83, 166, 41, 82, 164, 45, 90, 180,
        13, 26, 52, 104, 208, 197, 239, 187, 19, 38, 76, 152, 85, 170, 49, 98, 196,
        237, 191, 27, 54, 108, 216, 213, 207, 251, 147, 67, 134, 105, 210, 193, 231,
        171, 51, 102, 204, 253, 159, 91, 182, 9, 18, 36, 72, 144, 69, 138, 113, 226,
        161, 39, 78, 156, 93, 186, 17, 34, 68, 136, 117, 234, 177, 7, 14, 28, 56,
        112, 224, 165, 47, 94, 188, 29, 58, 116, 232, 181, 15, 30, 60, 120, 240,
        133, 111, 222, 217, 215, 203, 243, 131, 99, 198, 233, 183, 11, 22, 44, 88,
        176, 5, 10, 20, 40, 80, 160, 37, 74, 148, 77, 154, 81, 162, 33, 66, 132,
        109, 218, 209, 199, 235, 179, 3, 6, 12, 24, 48, 96, 192, 229, 175, 59, 118,
        236, 189, 31, 62, 124, 248, 149, 79, 158, 89, 178, 0
};

int f(int index);

int A(int x, int y);

std::bitset<16> PE(int x, int y);

std::bitset<128> P(std::bitset<128> block);

std::bitset<128> T(std::bitset<128> block);

std::bitset<128> Sp(std::bitset<128> block);

std::bitset<128> C(int k, std::bitset<128> block);

std::bitset<128> round_function(std::bitset<128> block, std::bitset<64> key);

std::bitset<128> encrypt(std::bitset<128> block, std::bitset<64> key1, std::bitset<64> key2);

std::bitset<128> decrypt(std::bitset<128> block, std::bitset<64> key1, std::bitset<64> key2);

std::vector<std::bitset<8>> getByteArray8(std::bitset<128> block);

std::bitset<64> getPart(std::bitset<128> block, short index);

std::bitset<64> feistel(std::bitset<128> block, std::bitset<64> key);

#endif //CRYPTO_ALGO_MAGENTA_H
