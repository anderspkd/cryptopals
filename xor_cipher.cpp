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

	int max_keysize      = 40; // maximum keysize to consider
	int max_chunks       = 30; // maximum number of pairs to check
	int min_chunks       = 4;  // minumum number of pairs to check
	int keysize          = 0;  // initial keysize guess (start at 1)
	int smallest_keysize;      // current best keysize guess

	// hamming weight and normalized hamming weight
	int hw;
	float norm_hw;
	float best_hw;

	// hamming weight will never be above this value.
	norm_hw = best_hw = max_keysize * 8;

	// this is just for ease of reference
	byte_v c = (*ctxt);

	// array to hold chunks
	byte_v key_chunks[max_chunks];
	int ccount;

	while ((keysize++) < max_keysize) {

	    ccount = 0; // reset chunk count
	    for (size_t i = 0; i < c.size() / keysize; i += keysize) {

		if (ccount == max_chunks)
		    break;

		byte_v v (keysize);

		for (size_t j = 0; j < keysize; j++) {
		    v[j] = c[j + i];
		}

		key_chunks[ccount++] = v;
	    }

	    if (ccount < min_chunks)
		break;

	    hw = 0;
	    for (size_t i = 0; i < ccount - 1; i++)
		for (size_t j = i; j < ccount; j++)
		    hw += util::hamm_dist(&key_chunks[i], &key_chunks[j]);
	    norm_hw = (float)hw / (ccount*keysize);

	    // save best keysize
	    if (norm_hw < best_hw) {
		smallest_keysize = keysize;
		best_hw = norm_hw;
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
