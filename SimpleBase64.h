#ifndef SIMPLE_BASE_64_H_
#define SIMPLE_BASE_64_H_
#include <string>
#include <vector>
#include <cstdint>

typedef std::vector<uint8_t> vec8;

class sBase64 {
public:
	sBase64(const std::string &utf8);
	sBase64(const vec8 &utf8);
	sBase64();
	~sBase64() = default;

	sBase64(const sBase64&) = delete;
	sBase64& operator=(const sBase64&) = delete;

	sBase64& encode(const std::string &utf8);
	sBase64& encode(const vec8 &utf8);
	sBase64& encode();
	vec8 getUtf8() const;
	sBase64& setUtf8(const vec8 &base64);
	sBase64& setUtf8(const std::string &base64);

	vec8 getBase64() const;
	std::string getBase64String() const;
	sBase64& setBase64(const vec8 &base64);
	sBase64& setBase64(const std::string &base64);

	std::string getUtf8String() const;

	sBase64& decode(const std::string &utf8);
	sBase64& decode(const vec8& utf8);
	sBase64& decode();


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