#include "util.hpp"

namespace util {

    int hex_decode(const std::string hex, byte_v *dest) {

	// check if input is a multiple of 2
	if (hex.length() % 2)
	    return -1;

	byte_t b1, b2;

	for (size_t i = 0; i < hex.length();) {
	    b1 = hexc(hex[i++]);
	    b2 = hexc(hex[i++]);
	    // invalid hex characters found
	    if (b1 == 255 || b2 == 255)
		return -1;
	    dest->push_back((b1 << 4) | b2);
	}

	return dest->size();
    }

    std::string hex_encode(const byte_v *src) {

	std::string res;
	byte_t b;
	size_t i;

	for (i = 0; i < src->size();) {
	    b = (*src)[i++];
	    res += hexa[b >> 4];
	    res += hexa[b & 0xF];
	}

	return res;
    }


    int base64_decode(const std::string b64, byte_v *dest) {

	byte_t x, y, z;

	for (size_t i = 0; i < b64.size();) {
	    x = b64c(b64[i++]);
	    y = b64c(b64[i++]);
	    // do not allow padding on the first two characters of a
	    // 4-tuple.
	    if (x == PAD || y == PAD || x == 255 || y == 255)
		return -1;

	    // first byte
	    dest->push_back( (x << 2) | ((y & 0x30) >> 4) );

	    z = b64c(b64[i++]);
	    if (z == PAD)
		return dest->size();
	    if (z == 255)
		return -1;

	    // second byte
	    dest->push_back( ((y & 0xF) << 4) | ((z & 0x3C) >> 2) );

	    x = b64c(b64[i++]);
	    if (x == PAD)
		return dest->size();
	    if (x == 255)
		return -1;

	    // third byte
	    dest->push_back( ((z & 0x3) << 6) | x );
	}

	return dest->size();
    }

    std::string base64_encode(const byte_v *src) {

	byte_t x, y;
	std::string res;
	size_t i;

	// calculate padding length
	int padding = (src->size() % 3) ? 3 - (src->size() % 3) : 0;

	for (i = 0; i < src->size() - (padding + 1);) {
	    // first character
	    x = (*src)[i++];
	    res += b64a[(x >> 2)];

	    // second character
	    y = (*src)[i++];
	    res += b64a[((x & 0x3) << 4) | (y >> 4)];

	    // third and fourth charater
	    x = (*src)[i++];
	    res += b64a[((y & 0xF) << 2) | (x >> 6)];
	    res += b64a[(x & 0x3F)];
	}

	// adding padding, if necessary
	if (padding) {
	    x = (*src)[i++];
	    res += b64a[(x >> 2)];
	    padding--;

	    if (!padding) {
		y = (*src)[i++];
		res += b64a[((x & 0x3) << 4) | (y >> 4)];
		res += b64a[(y & 0xF) << 2];
		res += "=";
	    } else {
		res += b64a[(x & 0x3) << 4];
		res += "==";
	    }
	}

	return res;
    }
}
