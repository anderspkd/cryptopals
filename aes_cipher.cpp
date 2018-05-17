#include "aes.hpp"

AES::AES(byte_v key) {

    try {
	byte * _key = &key[0];

	CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption e;
	e.SetKey(_key, sizeof(key));

	CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption d;
	d.SetKey(_key, sizeof(key));

	enc = e;
	dec = d;

    } catch (const CryptoPP::Exception & exp) {
	std::cerr << exp.what() << std::endl;
	std::exit(1);
    }
}
