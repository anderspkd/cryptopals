#include "xor_cipher.hpp"

namespace xor_cipher {

    int xor_bytes(const byte_v *v1, const byte_v *v2, byte_v *dest) {

	if (v1->size() != v2->size())
	    return -1;

	for (size_t i = 0; i < v1->size(); i++)
	    dest->push_back( (*v1)[i] ^ (*v2)[i] );

	return 0;
    }

    byte_t most_likely_byte(const byte_v *ctxt) {
	return most_likely_byte(ctxt, NULL);
    }

    byte_t most_likely_byte(const byte_v *ctxt, int *final_score) {

	byte_t curr_cand, best_cand;
	int curr_score, best_score;
	size_t i;

	curr_score = best_score = 0;
	curr_cand = best_cand = 0;

	while(curr_cand < 255) {
	    for (i = 0; i < ctxt->size(); i++) {

		switch ((*ctxt)[i] ^ curr_cand) {

		case (byte_t)'e':
		case (byte_t)'t':
		case (byte_t)'a':
		case (byte_t)'o':
		case (byte_t)'i':
		case (byte_t)'n':
		    curr_score++;
		    break;

		default:
		    break;
		}
	    }

	    if (curr_score > best_score) {
		best_cand = curr_cand;
		best_score = curr_score;
	    }

	    curr_cand++;
	    curr_score = 0;
	}

	// Save final score?
	if (final_score)
	    *final_score = best_score;

	return best_cand;
    }

    int repeated_xor(const byte_v *ptxt, const byte_v *key, byte_v *ctxt) {

	size_t key_size = key->size();
	size_t i = 0;

	for (; i < ptxt->size(); i++) {
	    ctxt->push_back( ((*ptxt)[i] ^ (*key)[i % key_size]) );
	}

	return i;
    }

}
