#ifndef SIMPLE_BASE_64_H_
#define SIMPLE_BASE_64_H_
#include <string>
#include <vector>
#include <cstdint>

typedef std::vector<uint8_t> vec8;

class utf8ToBase64 {
public:
	utf8ToBase64(const std::string &utf8);
	utf8ToBase64(const vec8 &utf8);
	utf8ToBase64();
	~utf8ToBase64() = default;

	utf8ToBase64(const utf8ToBase64&) = delete;
	utf8ToBase64& operator=(const utf8ToBase64&) = delete;

	utf8ToBase64& encode(const std::string &utf8);
	utf8ToBase64& encode(const vec8 &utf8);
	utf8ToBase64& encode();
	vec8 getUtf8() const;
	utf8ToBase64& setUtf8(const vec8 &base64);
	utf8ToBase64& setUtf8(const std::string &base64);

	vec8 getBase64() const;
	std::string getBase64String() const;
	utf8ToBase64& setBase64(const vec8 &base64);
	utf8ToBase64& setBase64(const std::string &base64);

	std::string getUtf8String() const;

	utf8ToBase64& decode(const std::string &utf8);
	utf8ToBase64& decode(const vec8& utf8);
	utf8ToBase64& decode();


private:
	vec8 threeTo64(vec8 x);
	vec8 encode_(void);
	vec8 decode_(vec8 &x);
	uint8_t fromBase64Table[256];
	void genFromBase64Table();
	static uint8_t toBase64Table[];
	vec8 utf8, base64;
};


#endif