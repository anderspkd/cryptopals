#include <iostream>

#include "../util.hpp"

using namespace std;

int main() {
    string hex =
	"49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    vector<byte_t> *raw = new vector<byte_t>;

    int count = util::hex_decode(hex, raw);

    if (count < 0)
	cout << "could not unhex string" << endl;

    string b64 = util::base64_encode(raw);
    string target =
	"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

    if (! target.compare(b64)) {
	cout << "yay! it's a match" << endl;
    }

}
