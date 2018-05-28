#ifndef __AES_CIPHER_HPP__
#define __AES_CIPHER_HPP__

#include "util.hpp"

#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
//#include <cryptopp/hex.h>
#include <cryptopp/base64.h>

/* This object simply holds an aes context and shorthands for encryption and
 * decryption of blocks*/
class AES {
public:

  AES (byte_v key);

  virtual void encrypt(byte_v * in, byte_v * out);
  virtual void decrypt(byte_v * in, byte_v * out);

protected:

  void _encrypt_block(byte_v * in, byte_v * out);
  void _decrypt_block(byte_v * in, byte_v * out);

private:

  CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption enc;
  CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption dec;
};

// class ECB_AES : AES {
//     public:

//     void encrypt(byte_v * in, byte_v * out);
//     void decrypt(byte_v * in, byte_v * out);
// }


#endif
