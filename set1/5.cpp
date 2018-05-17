#include "../xor_cipher.hpp"
#include "../util.hpp"

#include <iostream>

using namespace std;

int main() {

    string _ptxt =
	"Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    string _key = "ICE";

    byte_v ptxt (_ptxt.begin(), _ptxt.end());
    byte_v key (_key.begin(), _key.end());
    byte_v ctxt;

    xor_cipher::repeated_xor(&ptxt, &key, &ctxt);

    cout << "result:   " << util::hex_encode(&ctxt) << endl;
    cout << "expected: " << "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f" << endl;
}
