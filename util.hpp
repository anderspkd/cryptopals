#ifndef __UTIL_HPP__
#define __UTIL_HPP__

/* Utility functions.
*/

#include <cstdint>
#include <vector>
#include <iostream>

// Typedefs ftso. clarity.
typedef uint8_t byte_t;
typedef std::vector<byte_t> byte_v;

#define DEBUG_V(vec, size)			\
    do {					\
	for (size_t i = 0; i < (size); i++)	\
	    std::cout << (vec)[i];		\
	std::cout << std::endl;			\
    } while (0)					\

#define DEBUG_A(atom)				\
    do {					\
	std::cout << (atom) << std::endl;	\
    } while (0)					\

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

    // hex alphabet. Used for encoding.
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

    int hamm_dist(const byte_v *a, const byte_v *b);

}

#endif
