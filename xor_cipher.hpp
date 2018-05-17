#ifndef __XOR_CIPHER_HPP__
#define __XOR_CIPHER_HPP__

#include "util.hpp"
#include <cmath>

namespace xor_cipher {

    /* Helper function that obtains a vector with all the bytes encrypted by the
     * same keybyte. I.e., if in = [k_1 | ... | k_n] where k_i is the i'th
     * column, encrypted with keybyte #i, then this function returns k_idx.
     */
    static inline void chunk_by_ks(byte_v * in, byte_v * out, int ks, int idx) {
	for (size_t i = 0; i < (size_t)(in->size() / ks); i++)
	    (*out)[i] = ((*in)[idx + i * ks]);
    }

#define DICT_S 26

    /* Frequencies of letters in the english alphabet. I.e., real_freqs[0],
     * which corresponds to 'a' has a frequency of around 8.1 percent.
     */
    static const float real_freqs[DICT_S] = {
	0.8167, 0.1492, 0.2782, 0.4253, 1.2702, 0.2228, 0.2015,
	0.6094, 0.6966, 0.0153, 0.0772, 0.4025, 0.2406, 0.6749,
	0.7507, 0.1929, 0.0095, 0.5987, 0.6327, 0.9056, 0.2758,
	0.0978, 0.2360, 0.0150, 0.1974, 0.0074
    };

    /* Calculate the xor of two equal length bit strings. Stores the result in
     * dest.
     */
    int xor_bytes(const byte_v * v1, const byte_v * v2, byte_v * dest);

    /* Finds the most likely byte via. frequency analysis. if min_dist is not
     * NULL, then the score of the returned byte is saved there.
     */
    byte_t most_likely_byte(const byte_v * ctxt, float * min_dist);

    /* Viginére cipher.
     */
    int repeated_xor(const byte_v * ptxt, const byte_v * key, byte_v * ctxt);

    /* Find the key size of used to compute the Viginére ciphertext ctxt.
     */
    int find_key_size(const byte_v * ctxt);

    /* Find Viginére key, resp. n most plausible Viginére keys.
     */
    byte_v find_key(const byte_v * ctxt, int keysize);
}

#endif
