#include "SimpleBase64.h"

uint8_t utf8ToBase64::toBase64Table[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
	'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'
};

void utf8ToBase64::genFromBase64Table() {
	for (int i = 0; i < 256; i++)
		fromBase64Table[i] = 0;
	for (int i = 0; i < 64; i++)
		fromBase64Table[toBase64Table[i]] = i;
}

vec8 utf8ToBase64::getUtf8() const {
	return utf8;
}

std::string utf8ToBase64::getUtf8String() const {
	return std::string(utf8.begin(), utf8.end());
}

std::string utf8ToBase64::getBase64String() const {
	return std::string(base64.begin(), base64.end());
}

vec8 utf8ToBase64::getBase64() const {
	return base64;
}
utf8ToBase64& utf8ToBase64::setBase64(const vec8 &base64) {
	this->base64 = base64;
	return *this;

}
utf8ToBase64& utf8ToBase64::setBase64(const std::string &base64) {
	return setBase64(vec8(base64.begin(), base64.end()));
}

utf8ToBase64& utf8ToBase64::setUtf8(const std::string& utf8) {
	return setUtf8(std::vector<uint8_t>(utf8.begin(), utf8.end()));
}

utf8ToBase64& utf8ToBase64::setUtf8(const vec8 &utf8) {
	this->utf8 = utf8;
	return *this;
}


utf8ToBase64::utf8ToBase64(const std::string &utf8) : utf8{}, base64{} {
	setUtf8(utf8);
	genFromBase64Table();
}


utf8ToBase64::utf8ToBase64() : utf8{}, base64{} {
	// build table for translating from base64 to utf8
	genFromBase64Table();
}


utf8ToBase64::utf8ToBase64(const vec8 &utf8) : utf8{}, base64{} {
	setUtf8(utf8);
	genFromBase64Table();
}

utf8ToBase64& utf8ToBase64::encode(const std::string &utf8) {
	setUtf8(utf8);
	return encode();
}

utf8ToBase64& utf8ToBase64::encode(const vec8 &utf8) {
	setUtf8(utf8);
	return encode();
}

utf8ToBase64& utf8ToBase64::encode() {
	setBase64(encode_());
	return *this;
}
// build the base64 vector
vec8 utf8ToBase64::encode_(void) {
	vec8 result;

	auto part = utf8.begin();
	auto end = utf8.end();
	while (std::distance(part, end) > 2) {
		auto res = std::move(threeTo64(vec8(part, part + 3)));
		result.insert(result.end(), res.begin(), res.end());
		part += 3;
	}
	if (part != end) {
		auto res = std::move(threeTo64(std::vector<uint8_t>(part, end)));
		result.insert(result.end(), res.begin(), res.end());
	}
	return result;
}
utf8ToBase64&  utf8ToBase64::decode(const std::string& base64) {
	auto res = vec8(base64.begin(), base64.end());
	return decode(res);

}
utf8ToBase64&  utf8ToBase64::decode() {
	return decode(this->base64);
}

utf8ToBase64&  utf8ToBase64::decode(const vec8 &base64) {
	if ((base64.size() % 4) != 0)
		throw new std::invalid_argument("base64 must be a multiple of 4 length");
	vec8 result;
	auto part = base64.begin();
	auto end = base64.end();
	while (std::distance(part, end) > 3) {
		auto v8 = vec8(part, part + 4);
		auto res = std::move(decode_(v8));
		result.insert(result.end(), res.begin(), res.end());
		part += 4;
	}
	this->utf8 = result;
	return *this;
}


vec8 utf8ToBase64::decode_(vec8 &x) {
	if (x.size() != 4) 
		throw new std::invalid_argument("x must be of size 4");
	
	int padding = 0;
	uint8_t res[4];
	for (int i = 0; i < 4; ++i) {
		uint8_t cur = x[i];
		if (cur == '=') {
			padding++;
			cur = 0;
		}
		res[i] = fromBase64Table[x[i]] << 2;
	}
	uint8_t af6 = res[0];
	uint8_t bf2 = (res[1] & 0xc0) >> 6;
	uint8_t first = af6 | bf2;

	uint8_t bm4 = (res[1] & 0x3c) << 2;
	uint8_t cf4 = (res[2] & 0xf0) >> 4;

	uint8_t second = bm4 | cf4;

	uint8_t cm2 = (res[2] & 0xc) << 4;
	uint8_t df6 = (res[3] & 0xfc) >> 2;
	uint8_t third = cm2 | df6;

	if (padding == 1) {
		return vec8{ first, second };
	}
	else if (padding == 2) {
		return vec8{ first };
	}
	return vec8{ first, second, third };
}



vec8 utf8ToBase64::threeTo64(vec8 x) {
	if (x.empty()) return vec8();
	// we calculate the amount of padding necessary
	int padding = (x.size() % 3) != 0 ? 3 - x.size() : 0;
	// and provide the actual 0 for non-three width vectors padding
	for (int i = 0; i < padding; i++) {
		x.push_back(0);
	}

	// we create the four 6-bit bytes

	// I prefer to just shift bits of consecutive ones generated by 0xf* rather than using
	// values such as 3 for 0b11 to reduce chance of mistakes
	uint8_t first = (x[0] & (0xff << 2)) >> 2;

	uint8_t al2s = (x[0] & (0xf >> 2)) << 6;
	uint8_t bf4 = (x[1] & (0xf << 4)) >> 2;
	uint8_t second = (bf4 | al2s) >> 2;

	uint8_t bl4 = (x[1] & 0xf) << 4;
	uint8_t cf2 = (x[2] & (0xf << 6)) >> 4;
	uint8_t third = (bl4 | cf2) >> 2;

	uint8_t fourth = x[2] & (0xff >> 2);

	// we now translate the bytes according to the toBase64Table table
	vec8 res = { toBase64Table[first], toBase64Table[second], toBase64Table[third], toBase64Table[fourth] };

	// add padding
	while (padding > 0) {
		res[4 - padding] = '=';
		padding--;
	}
	return res;
}