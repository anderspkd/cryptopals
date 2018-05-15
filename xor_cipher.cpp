#include "xor_cipher.hpp"
#include <math.h>

namespace xor_cipher {

    int xor_bytes(const byte_v *v1, const byte_v *v2, byte_v *dest) {

	if (v1->size() != v2->size())
	    return -1;

	for (size_t i = 0; i < v1->size(); i++)
	    dest->push_back( (*v1)[i] ^ (*v2)[i] );

	return 0;
    }

    /* Better version. Curtsy of Daniel :-) */
    float score_plaintext(const byte_v *text) {

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
	    // if (b < 30)
	    // 	for (size_t i = 0; i < DICT_S; i++)
	    // 	    counts[i] = counts[i] > 0 ? counts[i] - 1 : 0;
	}

	for (size_t i = 0; i < DICT_S; i++)
	    dist += std::fabs((counts[i] / text_len) - real_freqs[i]);

	return dist;
    }

    byte_t most_likely_byte(const byte_v *ctxt) {
	return most_likely_byte(ctxt, NULL);
    }

    byte_t most_likely_byte(const byte_v *ctxt, float *min_dist) {

	byte_t curr_cand, best_cand;
	float curr_score, best_score;
	byte_v *ptxt = new byte_v(ctxt->size());

	curr_cand = best_cand = 0;
	curr_score = best_score = (float)ctxt->size();

	while(curr_cand < 255) {

	    for (size_t i = 0; i < ctxt->size(); i++)
		(*ptxt)[i] = (*ctxt)[i] ^ curr_cand;

	    curr_score = score_plaintext(ptxt);

	    if (curr_score < best_score) {
		best_score = curr_score;
		best_cand = curr_cand;
	    }

	    curr_cand++;
	}

	if (min_dist)
	    *min_dist = best_score;

	return best_cand;

    }

    int repeated_xor(const byte_v *src, const byte_v *key, byte_v *dest) {

	size_t key_size = key->size();
	size_t i = 0;

	for (; i < src->size(); i++) {
	    dest->push_back( ((*src)[i] ^ (*key)[i % key_size]) );
	}

	return i;
    }

    /* Attempts to find the key size based on the approach given in the
     */
    int find_key_size(const byte_v *ctxt) {

	// int max_ks = 50;
	// int ks, best_ks;

	// ks = best_ks = 0;

	// float hd, best_hd;

	// hd = best_hd = max_ks * 8;

	// byte_v c = (*ctxt);

	// while ((ks++) < max_ks) {

	//     // keysize is too large to split ctxt
	//     if (c.size() < 2 * ks)
	// 	break;

	//     byte_v v1 (ks);
	//     byte_v v2 (ks);

	//     for (size_t i = 0; i < ks; i++) {
	//     	v1[i] = c[i];
	//     	v2[i] = c[i + ks];
	//     }

	//     hd = (float)util::hamm_dist(&v1, &v2) / ks;

	//     // for (size_t i = 0; i < ks; i++) v1[i] = c[i];
	//     // for (size_t i = ks; i < (c.size() - ks) / ks; i += ks) {
	//     // 	for (size_t j = 0; j < ks; j++) v2[j] = c[j + i];
	//     // 	hd += (float)util::hamm_dist(&v1, &v2) / ks;
	//     // }

	//     if (hd < best_hd) {
	// 	best_hd = hd;
	// 	best_ks = ks;
	//     }

	//     std::cout << "keysize = " << ks
	// 	      << ", score = " << hd << std::endl;
	// }

	// return best_ks;

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

	    // if (curr_hd < best_hd) {
	    // 	smallest_keysize = keysize;
	    // 	best_hd = curr_hd;
	    // }

	    if (norm_ks < best_ks) {
		smallest_keysize = keysize;
		best_ks = norm_ks;
	    }

	    std::cout << "keysize = " << keysize
	    	      << ", hamm_dist = " << (float)norm_ks << std::endl;
	}

	return smallest_keysize;
    }

    byte_v find_repeated_xor_key(const byte_v *ctxt) {
	int keysize = find_key_size(ctxt);
	return find_repeated_xor_key(ctxt, keysize);
    }

    byte_v find_repeated_xor_key(const byte_v *ctxt, int keysize) {

	// return (byte_v)0;
	byte_v key (keysize);
	byte_t kb;

	byte_v _ctxt = (*ctxt);

	for (size_t i = 0; i < keysize; i++) {

	    byte_v tctxt;

	    for (size_t j = 0; j < (size_t)(_ctxt.size() / keysize); j++)
		tctxt.push_back(_ctxt[i + j*keysize]);

	    float s;
	    key[i] = most_likely_byte(&tctxt, &s);

	    std::cout << (int)key[i] << ", " << s << std::endl;
	}

	return key;

    }

}
