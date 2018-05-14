#include "util.hpp"
#include "xor_cipher.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string filename = "data/4.txt";
    string curr_line, best_line;
    float best_score, curr_score;
    int linum, best_linum;
    byte_t b, best_byte;

    ifstream file (filename);

    if (file.is_open())
	cout << "Good. Now I can open files" << endl;

    linum = best_linum = 0;
    best_score = curr_score = 10000.0;

    while (getline(file, curr_line)) {

	vector<byte_t> *r = new vector<byte_t>;

	if (util::hex_decode(curr_line, r) < 0) {
	    cout << "could not decode line " << linum << endl;
	    return 1;
	}
	b = xor_cipher::most_likely_byte(r, &curr_score);

	if (curr_score < best_score) {
	    best_score = curr_score;
	    best_line = curr_line;
	    best_byte = b;
	    best_linum = linum;
	}

	linum++;

	delete r; // is this really necessary?
    }

    cout << "best line at " << best_linum
	 << ", score=" << best_score << endl
	 << "byte: " << (int)best_byte << endl << endl;

    cout << "decoded:" << endl;
    vector<byte_t> ctxt;
    int end = util::hex_decode(best_line, &ctxt);
    for (size_t i = 0; i < end; i++) {
	cout << (char)(ctxt[i] ^ best_byte);
    }
}
