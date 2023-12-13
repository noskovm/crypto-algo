#include <iostream>
#include "magenta.h"

int f(int index) {
    return S[index];
}

int A(int x, int y) {
    int tmp = x^(f(y));
    return f(tmp);
}

std::pair<std::bitset<8>, std::bitset<8>> PE(int x, int y) {
    return std::pair(std::bitset<8>(A(x, y)), std::bitset<8>(A(y, x)));
}

std::bitset<128> P(std::bitset<128> open) {
    std::bitset<128> mask(0xff);
    std::vector<int> bytes;


    for (int i = 0; i < 128 / 8; ++i) {
        auto byte = static_cast<uint8_t>(((open >> (8 * i)) & mask).to_ulong());
        bytes.push_back(static_cast<int>(byte));
    }
    std::reverse(bytes.begin(), bytes.end());
    std::vector<std::pair<std::bitset<8>, std::bitset<8>>> tmp;

    tmp.push_back(PE(bytes[0], bytes[8]));
    tmp.push_back(PE(bytes[1], bytes[9]));
    tmp.push_back(PE(bytes[2], bytes[10]));
    tmp.push_back(PE(bytes[3], bytes[11]));
    tmp.push_back(PE(bytes[4], bytes[12]));
    tmp.push_back(PE(bytes[5], bytes[13]));
    tmp.push_back(PE(bytes[6], bytes[14]));
    tmp.push_back(PE(bytes[7], bytes[15]));
    // имеет пары по 8 байт, итого 16 байт

    std::string num;
    for (int i = 0; i < 8; ++i) {
        num += (tmp[i].first).to_string();
        num += (tmp[i].second).to_string();
    }

    std::bitset<128> res(num);
    return res;
}

std::bitset<128> T(std::bitset<128> block) {
    return P(P(P(P(block))));
}

std::bitset<128> Sp(std::bitset<128> open) {
    std::bitset<128> mask1(0xff);
    std::vector<std::bitset<8>> bytes1;


    for (int i = 0; i < 128 / 8; ++i) {
        auto byte = static_cast<uint8_t>(((open >> (8 * i)) & mask1).to_ulong());
        bytes1.push_back(std::bitset<8>(byte));
    }
    std::reverse(bytes1.begin(), bytes1.end());

    std::string num;

    num += bytes1[0].to_string();
    num += bytes1[2].to_string();
    num += bytes1[4].to_string();
    num += bytes1[6].to_string();
    num += bytes1[8].to_string();
    num += bytes1[10].to_string();
    num += bytes1[12].to_string();
    num += bytes1[14].to_string();

    num += bytes1[1].to_string();
    num += bytes1[3].to_string();
    num += bytes1[5].to_string();
    num += bytes1[7].to_string();
    num += bytes1[9].to_string();
    num += bytes1[11].to_string();
    num += bytes1[13].to_string();
    num += bytes1[15].to_string();

    return std::bitset<128>(num);
}

std::bitset<128> C(std::bitset<128> open, int k) {
    if (k == 1) {
        return T(open);
    }
    std::bitset<128> res = T(open^(Sp(C(open, k-1))));
    return res;
}

std::bitset<128> round_fuction(std::bitset<128> x, std::bitset<64> key) {
    std::bitset<128> mask(0b00000000000000000000000000000000000000000000000000000000000000001111111111111111111111111111111111111111111111111111111111111111);
    std::bitset<64> x1 = std::bitset<64>(((x >> 64) & mask).to_ullong());
    std::bitset<64> x2 = std::bitset<64>((x & mask).to_ullong());


    std::bitset<128> input = std::bitset<128>(x2.to_string()+key.to_string());
    std::bitset<128> F_tmp = Sp(C(input, 3));


    std::bitset<128> mask1(0xff);
    std::vector<std::bitset<8>> bytes;
    for (int i = 0; i < 16; ++i) {
        auto byte = static_cast<uint8_t>(((F_tmp >> (8 * i)) & mask1).to_ulong());
        bytes.push_back(std::bitset<8>(byte));
    }
    std::reverse(bytes.begin(), bytes.end());

    std::vector<std::bitset<8>> bytes8(bytes.begin(), bytes.begin() + 8);

    std::string fin;
    for(int i = 0; i < 8; ++i) {
        fin += bytes8[i].to_string();
    }

    std::bitset<64> rignt_side = (x1^std::bitset<64>(fin));

    auto res =  std::bitset<128>(x2.to_string() + rignt_side.to_string());
    return res;
}

std::bitset<128> encrypt(std::bitset<128> block, std::bitset<64> key1, std::bitset<64> key2) {
    std::bitset<128> x = round_fuction(block, key1);

    // 2
    x = round_fuction(x, key1);

    //3
    x = round_fuction(x, key2);

    // 4
    x = round_fuction(x, key2);

    // 5
    x = round_fuction(x, key1);

    // 6
    x = round_fuction(x, key1);

    return x;
}

std::bitset<128> decrypt(std::bitset<128> block) {
    std::bitset<128> decrypt = block;

    std::bitset<128> maskt(0xff);
    std::vector<std::bitset<8>> bytes_d;

    for (int i = 0; i < 128 / 8; ++i) {
        auto byte = static_cast<uint8_t>(((decrypt >> (8 * i)) & maskt).to_ulong());
        bytes_d.push_back(std::bitset<8>(byte));
    }
    std::reverse(bytes_d.begin(), bytes_d.end());
    std::string final;
    final += bytes_d[8].to_string();
    final += bytes_d[9].to_string();
    final += bytes_d[10].to_string();
    final += bytes_d[11].to_string();
    final += bytes_d[12].to_string();
    final += bytes_d[13].to_string();
    final += bytes_d[14].to_string();
    final += bytes_d[15].to_string();

    final += bytes_d[0].to_string();
    final += bytes_d[1].to_string();
    final += bytes_d[2].to_string();
    final += bytes_d[3].to_string();
    final += bytes_d[4].to_string();
    final += bytes_d[5].to_string();
    final += bytes_d[6].to_string();
    final += bytes_d[7].to_string();

    std::bitset<128> decrypt_m(final);
    return decrypt;
}