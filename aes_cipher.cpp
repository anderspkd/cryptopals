#include "aes_cipher.hpp"


AES::AES(byte_v key) {
  try {
    unsigned char * _key = &key[0];

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

void AES::encrypt(byte_v * in, byte_v * out){

  CryptoPP::ArraySource ss(&(*in)[0], (*in).size(), true,
                  new CryptoPP::StreamTransformationFilter(this->enc,
							   new CryptoPP::ArraySink(&(*out)[0], (*out).size())));
};

void AES::decrypt(byte_v * in, byte_v * out){

  CryptoPP::ArraySource ss(&(*in)[0], (*in).size(), true,
                  new CryptoPP::StreamTransformationFilter(this->dec,
							   new CryptoPP::ArraySink(&(*out)[0], (*out).size())));
};

