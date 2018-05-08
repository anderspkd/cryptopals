#ifndef __XOR_CIPHER_HPP__
#define __XOR_CIPHER_HPP__

#include "util.hpp"

namespace xor_cipher {

    // calculates the xor of two equal length byte vectors v1 and v2. Puts the
    // result in dest. Returns 0 on success and -1 if lengths of v1 and v2 does
    // not match.
    int xor_bytes(const byte_v *v1, const byte_v *v2, byte_v *dest);

    // finds the "most likely" single byte that ctxt was xored with. Uses simple
    // frequency analysis according the the english alphabet.
    byte_t most_likely_byte(const byte_v *ctxt);
    byte_t most_likely_byte(const byte_v *ctxt, int *best_score);

    // Viginere cipher (repeated xor).
    int repeated_xor(const byte_v *ptxt, const byte_v *key, byte_v *ctxt);
}

#endif
