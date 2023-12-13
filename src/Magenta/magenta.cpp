#include <iostream>
#include "magenta.h"

int f(int index) {
    return S[index];
}

int A(int x, int y) {
    int tmp = x^(f(y));
    return f(tmp);
}

std::bitset<16> PE(int x, int y) {
    return std::bitset<16>(std::bitset<8>(A(x, y)).to_string() + std::bitset<8>(A(y, x)).to_string());
}

std::bitset<128> P(std::bitset<128> block) {
    std::vector<std::bitset<8>> batch = getByteArray8(block);

    std::vector<std::bitset<16>> pairs;

    for (int i = 0; i < 8; ++ i) {
        pairs.push_back(PE(batch[i].to_ulong(), batch[i+8].to_ulong()));
    }

    std::string num;
    for (int i = 0; i < 8; ++i) {
        num += pairs[i].to_string();
    }

    return std::bitset<128>(num);
}

std::bitset<128> T(std::bitset<128> block) {
    return P(P(P(P(block))));
}

std::bitset<128> Sp(std::bitset<128> block) {
    std::vector<std::bitset<8>> batch = getByteArray8(block);

    std::string num;

    for(int i = 0; i < 15; i += 2) {
        num += batch[i].to_string();
    }

    for(int i = 1; i < 16; i += 2) {
        num += batch[i].to_string();
    }

    return std::bitset<128>(num);
}

std::bitset<128> C(int k, std::bitset<128> block) {
    if (k == 1) {
        return T(block);
    }
    std::bitset<128> res = T(block^(Sp(C(k-1, block))));
    return res;
}

std::bitset<128> round_function(std::bitset<128> block, std::bitset<64> key) {

    std::bitset<128> currentX = block;

    std::bitset<64> x1 = getPart(currentX, 0);
    std::bitset<64> x2 = getPart(currentX, 1);

    std::bitset<64> rightSide = (x1^feistel(block, key));

    return std::bitset<128>(x2.to_string() + rightSide.to_string());
}

std::bitset<128> encrypt(std::bitset<128> block, std::bitset<64> key1, std::bitset<64> key2) {

    std::bitset<128> x = round_function(block, key1); // 1
    x = round_function(x, key1);    // 2
    x = round_function(x, key2);    // 3
    x = round_function(x, key2);    // 4
    x = round_function(x, key1);    // 5
    x = round_function(x, key1);    // 6

    return x;
}

std::bitset<128> decrypt(std::bitset<128> block) {
    std::vector<std::bitset<8>> batch = getByteArray8(block);

    std::string open;

    for(int i = 8; i < 16; ++i) {
        open += batch[i].to_string();
    }

    for(int i = 0; i < 8; ++i) {
        open += batch[i].to_string();
    }

    return std::bitset<128>(open);
}

std::vector<std::bitset<8>> getByteArray8(std::bitset<128> block) {
    std::bitset<128> mask(0xff);
    std::vector<std::bitset<8>> bytes;


    for (int i = 0; i < 16; ++i) {
        auto byte = static_cast<uint8_t>(((block >> (8 * i)) & mask).to_ulong());
        bytes.push_back(std::bitset<8>(byte));
    }
    std::reverse(bytes.begin(), bytes.end());
    return bytes;
}

std::bitset<64> getPart(std::bitset<128> block, short index) {
    std::bitset<128> mask(0b00000000000000000000000000000000000000000000000000000000000000001111111111111111111111111111111111111111111111111111111111111111);
    if(index==0){
        return std::bitset<64>(((block >> 64) & mask).to_ullong());
    }
    else {
        return std::bitset<64>((block & mask).to_ullong());
    }
}

std::bitset<64> feistel(std::bitset<128> block, std::bitset<64> key) {
    std::bitset<64> rightPart = getPart(block, 1);
    std::bitset<128> concatBlock(rightPart.to_string() + key.to_string());
    std::bitset<128> result = Sp(C(3, concatBlock));

    std::vector<std::bitset<8>> batch = getByteArray8(result);

    std::vector<std::bitset<8>> BatchFirst8(batch.begin(), batch.begin() + 8);

    std::string first8Bytes;
    for(int i = 0; i < 8; ++i) {
        first8Bytes += BatchFirst8[i].to_string();
    }

    return std::bitset<64>(first8Bytes);
}