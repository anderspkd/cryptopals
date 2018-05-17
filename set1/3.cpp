#include "../util.hpp"
#include "../xor_cipher.hpp"

#include <iostream>

using namespace std;

int main() {
    string str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    vector<byte_t> raw;

    if (util::hex_decode(str, &raw) < 0)
	cout << "could not decode hex string" << endl;

    byte_t most_likely = xor_cipher::most_likely_byte(&raw, NULL);

    cout << "mosts likely byte: " << (int)most_likely << endl;
    cout << "decryption with " << (int)most_likely << ":" << endl;
    for (size_t i = 0; i < raw.size(); i++)
	cout << (char)(most_likely ^ raw[i]);
    cout << endl;
}
