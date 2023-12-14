#include <iostream>
#include <bitset>
#include "mag_file_processing.h"
#include "elgamal.h"
#include "elg_file_processing.h"
#include <xstring>

int main() {
    setlocale(LC_ALL, "ru");
    system("chcp 65001");

    Elgamal alg;
    Keys kset = alg.keygen();

    e_encrypt_file(R"(C:\Users\noskovm\CLionProjects\crypto-algo\lesnik.mp3)",
                     R"(C:\Users\noskovm\CLionProjects\crypto-algo\tmp)",
                          kset.y, kset.g, kset.p);

    e_decrypt_file(R"(C:\Users\noskovm\CLionProjects\crypto-algo\tmp)",
                     R"(C:\Users\noskovm\CLionProjects\crypto-algo\lesnikout.mp3)",
                     kset.x, kset.p);

    return 0;
}