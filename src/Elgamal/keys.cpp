#include "keys.h"

PublicKey::PublicKey(cpp_int p_y, cpp_int p_g, cpp_int p_p) : y(p_y), g(p_g), p(p_p) {}

PrivateKey::PrivateKey(cpp_int p_x, cpp_int p_g, cpp_int p_p) : x(p_x), g(p_g), p(p_p) {}
