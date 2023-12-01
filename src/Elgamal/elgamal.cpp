#include "primality_test.h"
#include "keys.h"

class Elgamal {
public:
    Elgamal() {

    }
    class KeyGen {
    public:
        KeyGen() = default;
        enum PrimeTest {
            FERMAT,
            SOLOVAYSTRASSEN,
            MILLERRABIN
        };
    private:
        PrimeTest primeTest;
        double minProb;
        int keyBitLength;
    };

//    void encrypt();
//    void decrypt();
//    std::pair<PublicKey, PrivateKey> keygen();
};
//
//std::pair<PublicKey, PrivateKey> Elgamal::keygen() {
//
//}
