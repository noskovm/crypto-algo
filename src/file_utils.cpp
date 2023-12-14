#include "file_utils.h"

boost::dynamic_bitset<> read_file(std::ifstream& file) {
    file.seekg(0, std::ios::end);
    const size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);

    boost::dynamic_bitset<> input_data;
    for (const char c : buffer)
    {
        for (int i = 7; i >= 0; --i)
        {
            input_data.push_back((c >> i) & 1);
        }
    }

    return input_data;
}

std::bitset<128> convert(const boost::dynamic_bitset<>& dynamicBitset) {
    std::bitset<128> bitset;
    for (int i = 0; i < dynamicBitset.size(); ++i) {
        bitset[i] = dynamicBitset[i];
    }
    return bitset;
}

void write_to_file(const std::bitset<128>& bitset, std::ofstream& file) {
    for (int i = 0; i < bitset.size(); i += CHAR_BIT) {
        char byte = 0;
        for (int j = 0; j < CHAR_BIT; ++j) {
            byte |= (bitset[i + (CHAR_BIT - 1 - j)] << j);
        }
        file.write(&byte, sizeof(byte));
    }
}

std::bitset<128> pkcs7_padding(const boost::dynamic_bitset<>& input, size_t block_size) {
    size_t input_size = input.size() / 8;
    size_t padding_size = block_size - (input_size % block_size);
    boost::dynamic_bitset<> output = input;
    std::bitset<8> padding_bits(padding_size);
    for (int i = 0; i < padding_size; ++i) {
        for (int j = 7; j >= 0; --j) {
            output.push_back(padding_bits[j]);
        }
    }
    return convert(output);
}

std::vector<std::bitset<128>> block_processing(const boost::dynamic_bitset<>& input_data) {
    size_t padding_block_size = 16;
    std::vector<std::bitset<128>> blocks;

    for (size_t i = 0; i < input_data.size(); i += 128)
    {
        size_t block_size = std::min<size_t>(128, input_data.size() - i);
        boost::dynamic_bitset<> current_block(block_size);

        for (size_t j = 0; j < block_size; ++j)
        {
            current_block[j] = input_data[i + j];
        }

        std::bitset<128> current_block_128 = convert(current_block);

        if (block_size < 128)
        {
            current_block_128 = pkcs7_padding(current_block, padding_block_size);
        }

        blocks.push_back(current_block_128);
    }

    return blocks;
}
