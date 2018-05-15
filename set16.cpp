#include "xor_cipher.hpp"
#include "util.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string filename = "data/6.txt";
    string line;
    string _ctxt;
    byte_v ctxt;

    ifstream file (filename);

    if (!file.is_open()) {
	cout << "could not open file :-(" << endl;
	return 1;
    }

    while (getline(file, line))
	_ctxt += line;

    if(util::base64_decode(_ctxt, &ctxt) < 0) {
    	cout << "could not decode ctxt" << endl;
    	return 1;
    }

    byte_v key = xor_cipher::find_repeated_xor_key(&ctxt);

    cout << "key: \"";
    for (size_t i = 0; i < key.size(); i++) {
	cout << (char)key[i];
    }
    cout << "\"" << endl;

    byte_v ptxt;

    xor_cipher::repeated_xor(&ctxt, &key, &ptxt);

    for (size_t i = 0; i < ptxt.size(); i++) {
    	cout << (char)ptxt[i];
    }
}
