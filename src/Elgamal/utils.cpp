#include "utils.h"

cpp_int modPow(cpp_int base, cpp_int pow, const cpp_int &mod, bool use_boost) {
    if (use_boost) {
        return boost::multiprecision::powm(base, pow, mod);
    }
    cpp_int result = 1;
    while (pow > 0) {
        cpp_int last_bit = (pow & 1);
        if (last_bit)
            result = (result * base) % mod;
        base = (base * base) % mod;
        pow = pow >> 1;
    }
    return result;
}


cpp_int searchGroupGenerator(cpp_int p) {
    p = p-1;
    cpp_int x = 2; //generateRandomFromRangeCPP_INT(2, p-2);
    cpp_int y = x;

    cpp_int gcd = 1;
    while (gcd == 1 || gcd == p)
    {
        x = simple_f(x)%p;
        y = simple_f(simple_f(y)%p)%p;

        gcd = boost::math::gcd(p, cpp_abs(x-y));
    }
    return gcd;
    //return 2;
}



cpp_int generateRandomFromRangeCPP_INT(cpp_int p_min, cpp_int p_max) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long int> dist((unsigned long long)p_min,(unsigned long long)p_max);
    return dist(gen);
}

cpp_int cpp_abs(cpp_int value) {
    if (value < 0)
        return -value;
    return value;
}

cpp_int gcd_euclid(cpp_int u, cpp_int v) {
    while (true) {
        if (!v) return u;
        u %= v;
        if (!u) return v;
        v %= u;
    }
}

cpp_int simple_f(cpp_int x) {
    return (x+1)*(x+1);
}

// TODO заменить на свою реализацию
// a/n is represented as (a,n)
cpp_int jacobi(cpp_int a, cpp_int n) {
    //step 1
    a = a % n;
    cpp_int t = 1;
    cpp_int r;
    //step 3
    while (a != 0) {
        //step 2
        while (a % 2 == 0) {
            a /= 2;
            r = n % 8;
            if (r == 3 || r == 5) {
                t = -t;
            }
        }
        //step 4
        r = n;
        n = a;
        a = r;
        if (a % 4 == 3 && n % 4 == 3) {
            t = -t;
        }
        a = a % n;
    }
    if (n == 1) {
        return t;
    }
    else {
        return 0;
    }
}

////////////////////////
