#include "../aes_cipher.hpp"
#include "../util.hpp"
using namespace std;

int main() {

  string keystr = "YELLOW SUBMARINE";
  byte_v key (keystr.begin(), keystr.end());

  AES * cipher = new AES(key);
  string cipherstr;
  try{
    CryptoPP::FileSource file("data/7.txt", true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(cipherstr)));}
			      //new CryptoPP::ArraySink(&plaintext[0], plaintext.size()));}
  catch (const CryptoPP::FileStore::OpenErr & err) { cerr << err.what() << endl;}
  //cout << plainstr;

  byte_v ciphertext (cipherstr.begin(), cipherstr.end());
  
  byte_v plaintext(ciphertext.size());
  
  cipher->decrypt(&ciphertext, &plaintext);
  
  
 
}
