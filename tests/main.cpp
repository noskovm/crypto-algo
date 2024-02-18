#include <iostream>
#include <bitset>
#include "mag_file_processing.h"
#include "elgamal.h"
#include "elg_file_processing.h"
#include "magenta.h"

int main() {
    setlocale(LC_ALL, "ru");
    //system("chcp 65001");

    Elgamal alg;
    Keys kset = alg.keygen();

//    elgamal_encrypt_file("/home/learn/Desktop/crypto-algo/test_files/image.jpg",
//                     "/home/learn/Desktop/crypto-algo/image_encryped",
//                          kset.y, kset.g, kset.p);

//    elgamal_decrypt_file("/home/learn/Desktop/crypto-algo/image_encryped",
//                     "/home/learn/Desktop/crypto-algo/test_files/image_res.jpg",
//                     kset.x, kset.p);

    std::bitset<64> key1("1010100111011100010000000010000000");

    std::bitset<64> key2("1110100111111100010011100010000000");

    magenta_encrypt_file("/home/learn/Desktop/crypto-algo/test_files/image.jpg", 
                         "/home/learn/Desktop/crypto-algo/encrypted", key1, key2);


    magenta_decrypt_file("/home/learn/Desktop/crypto-algo/encrypted", 
                        "/home/learn/Desktop/crypto-algo/test_files/img_res.jpg", key1, key2);


    return 0;
}