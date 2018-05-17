#include "../util.hpp"
#include "../xor_cipher.hpp"

#include <iostream>

using namespace std;

int main() {
    string str1 = "1c0111001f010100061a024b53535009181c";
    string str2 = "686974207468652062756c6c277320657965";

    // str1 xor str2 == targ
    string targ = "746865206b696420646f6e277420706c6179";

    vector<byte_t> v1;
    vector<byte_t> v2;

    int v1_size = util::hex_decode(str1, &v1);
    int v2_size = util::hex_decode(str2, &v2);

    if (v1_size < 0)
	cout << "could not decode string 1" << endl;
    if (v2_size < 0)
	cout << "could not decode string 2" << endl;

    if (v1_size != v2_size)
	cout << "hmmm" << endl;

    vector<byte_t> r;

    if (xor_cipher::xor_bytes(&v1, &v2, &r))
	cout << "xor didn't work" << endl;

    if (!targ.compare(util::hex_encode(&r)))
    	cout << "yay! it's a match!" << endl;

}
