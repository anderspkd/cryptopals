#ifndef __XOR_CIPHER_HPP__
#define __XOR_CIPHER_HPP__

#include "util.hpp"
#include <math.h>

namespace xor_cipher {

#define DICT_S 26
#define ETAOINS_S 7

    static const float etaoins[ETAOINS_S] = {
	0.12702, 0.09056, 0.08167, 0.07507, 0.06966, 0.06749, 0.06327
    };

    static const float real_freqs[DICT_S] = {
	0.8167, 0.1492, 0.2782, 0.4253, 0.1270, 0.2228, 0.2015,
	0.6094, 0.6966, 0.0153, 0.0772, 0.4025, 0.2406, 0.6749,
	0.7507, 0.1929, 0.0095, 0.5987, 0.6327, 0.9056, 0.2758,
	0.0978, 0.2360, 0.0150, 0.1974, 0.0074
    };

    // calculates the xor of two equal length byte vectors v1 and v2. Puts the
    // result in dest. Returns 0 on success and -1 if lengths of v1 and v2 does
    // not match.
    int xor_bytes(const byte_v *v1, const byte_v *v2, byte_v *dest);

    // finds the "most likely" single byte that ctxt was xored with. Uses simple
    // frequency analysis according the the english alphabet.
    byte_t most_likely_byte(const byte_v *ctxt);
    byte_t most_likely_byte(const byte_v *ctxt, float *min_dist);

    // float score_plaintext(const byte_v *text);

    // Viginere cipher (repeated xor).
    int repeated_xor(const byte_v *ptxt, const byte_v *key, byte_v *ctxt);

    int find_key_size(const byte_v *ctxt);

    byte_v find_repeated_xor_key(const byte_v *ctxt);
    byte_v find_repeated_xor_key(const byte_v *ctxt, int keysize);
}

#endif
