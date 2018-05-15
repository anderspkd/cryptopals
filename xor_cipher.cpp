#include "xor_cipher.hpp"
#include <math.h>
#include <algorithm>

namespace xor_cipher {

    int xor_bytes(const byte_v * v1, const byte_v * v2, byte_v * dest) {

	if (v1->size() != v2->size())
	    return -1;

	for (size_t i = 0; i < v1->size(); i++)
	    dest->push_back( (*v1)[i] ^ (*v2)[i] );

	return 0;
    }

    /* Better version. Curtsy of Daniel :-) */
    float score_plaintext(const byte_v * text) {

	byte_t b;
	float dist;

	size_t text_len = text->size();
	float counts[DICT_S] = {0};

	for (size_t i = 0; i < text_len; i++) {
	    b = (*text)[i];
	    if (b > 64 && b < 91)
		counts[b - 65]++;
	    if (b > 96 && b < 123)
		counts[b - 97] += 2;
	}

	for (size_t i = 0; i < DICT_S; i++)
	    dist += std::fabs((counts[i] / text_len) - real_freqs[i]);

	return dist;
    }

    byte_t most_likely_byte(const byte_v * ctxt, float * min_dist) {

	byte_t cand, bcand;
	float dist, mdist;

	byte_v * ptxt = new byte_v(ctxt->size());

	cand = bcand = 0;
	dist = mdist = (float)ctxt->size();

	while(cand < 255) {

	    for (size_t i = 0; i < ctxt->size(); i++)
		(*ptxt)[i] = (*ctxt)[i] ^ cand;

	    dist = score_plaintext(ptxt);

	    if (dist < mdist) {
		mdist = dist;
		bcand = cand;
	    }

	    cand++;
	}

	if (min_dist)
	    *min_dist = mdist;

	return bcand;

    }

    int repeated_xor(const byte_v * src, const byte_v * key, byte_v * dest) {

	size_t key_size = key->size();
	size_t i = 0;

	for (; i < src->size(); i++) {
	    dest->push_back( ((*src)[i] ^ (*key)[i % key_size]) );
	}

	return i;
    }

    /* Attempts to find the key size based on the approach given in the
     */
    int find_key_size(const byte_v * ctxt) {

	int max_keysize = 30;
	int keysize = 0; // first guess at keysize is 4

	int curr_hd, best_hd;
	int smallest_keysize = -1;

	float norm_ks, best_ks;

	norm_ks = best_ks = max_keysize * 8;

	// this is (I think) the max edit dist possible.
	best_hd = max_keysize * 8;

	byte_v _ctxt = (*ctxt);

	while ((keysize++) < max_keysize) {

	    if (_ctxt.size() < 2 * keysize) {
		// not enough ciphertext bytes to split ctxt.
		return -1;
	    }

	    byte_v v1 (keysize);
	    byte_v v2 (keysize);
	    byte_v v3 (keysize);
	    byte_v v4 (keysize);

	    for (size_t i = 0; i < keysize; i++) {
		v1[i] = _ctxt[i];
		v2[i] = _ctxt[i + keysize];
		v3[i] = _ctxt[i + keysize + keysize];
		v4[i] = _ctxt[i + keysize + keysize + keysize];
	    }

	    curr_hd = util::hamm_dist(&v1, &v2)
		+ util::hamm_dist(&v1, &v3)
		+ util::hamm_dist(&v1, &v4)
		+ util::hamm_dist(&v2, &v3)
		+ util::hamm_dist(&v3, &v4);

	    norm_ks = (float)curr_hd / (5*keysize);

	    if (norm_ks < best_ks) {
		smallest_keysize = keysize;
		best_ks = norm_ks;
	    }
	}

	return smallest_keysize;
    }

    byte_v find_key(const byte_v * ctxt, int keysize) {

	byte_v key (keysize);
	byte_v c = *ctxt;
	byte_v tc (c.size() / keysize);

	for (size_t i = 0; i < keysize; i++) {
	    chunk_by_ks(&c, &tc, keysize, i);
	    key[i] = most_likely_byte(&tc, NULL);
	}

	return key;
    }

}
