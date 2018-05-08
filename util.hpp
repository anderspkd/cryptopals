#ifndef __UTIL_HPP__
#define __UTIL_HPP__

/*
  Encoding and decoding functions.

  Decoding functions take 2 arguments: source (a std::string const) and
  destination (a pointer to a byte vector). Returns -1 if decoding fails
  otherwise returns the number of bytes decoded.

  Encoding functions take 1 argument: source (a const pointer to a byte
  vector). Returns a std::string with the result. Always succeeds.
*/

#include <cstdint>
#include <vector>
#include <iostream>

typedef uint8_t byte_t;
typedef std::vector<byte_t> byte_v;

namespace util {

    static const byte_t hex_table[127] = {
    /*  0    1    2    3    4    5    6    7    8    9   */
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 0,   1,
	2,   3,   4,   5,   6,   7,   8,   9,   255, 255,
	255, 255, 255, 255, 255, 10,  11,  12,  13,  14,
	15,  255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 10,  11,  12,
	13,  14,  15,  255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255
    };

    // translate hex character to a decimal
    static inline byte_t hexc(char c) {
	return c > 127 ? 255 : hex_table[(int)c];
    }

    static const std::string hexa = "0123456789abcdef";

#define PAD 64

    static const byte_t b64_table[127] = {
    /*	0    1    2    3    4    5    6    7    8    9   */
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 62 , 255, 255, 255, 63,  52,  53,
	54,  55,  56,  57,  58,  59,  60,  61,  255, 255,
	255, PAD, 255, 255, 255, 0,   1,   2,   3,   4,
	5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
	15,  16,  17,  18,  19,  20,  21,  22,  23,  24,
	25,  255, 255, 255, 255, 255, 255, 26,  27,  28,
	29,  30,  31,  32,  33,  34,  35,  36,  37,  38,
	39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
	49,  50,  51, 255, 255, 255, 255
    };

    // translate a base64 character to a decimal
    static inline byte_t b64c(char c) {
	return c > 127 ? 255 : b64_table[(int)c];
    }

    static const std::string b64a =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // decoding functions
    int hex_decode(const std::string hex, byte_v *dest);
    int base64_decode(const std::string b64, byte_v *dest);

    // encoding functions
    std::string hex_encode(const byte_v *src);
    std::string base64_encode(const byte_v *srt);

} // end util namespace

#endif
