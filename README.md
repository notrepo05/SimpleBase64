# SimpleBase64
Simple base64 encoding and decoding without validation. 

*This class has received little testing (need to add unit tests): use with caution. Edit: This code has been extensively tested encoding and decoding large executables and tested for corner cases.*
# Example Uses

```cpp
// example
int main(void) {
    std::string helloWorld("Hello World 你好，世界");
	// instance of sBase64 with default utf-8 to encode
    sBase64 b64{ helloWorld };
	// we encode and return the resultant string
	std::cout << b64.encode().getBase64String() << std::endl;
	// we decode and return the resultant string (equal to the original)
	std::cout << b64.decode().getUtf8String() << std::endl;


	// a few tests

	std::string test1{ "♀ ♁ ♂ ♃ ♄ ♅ ♆ ♇ ♈ ♉ ♊ ♋ ♌ ♍ ♎ ♏ ♐ ♑ ♒ ♓ ♔ ♕ ♖ ♗ ♘ ♙ ♚ ♛ ♜ ♝ ♞ ♟" },
		test2{ "- × ÷ ± ∞ π ∅ ≤ ≥ ≠ ≈ ∧ ∨ ∩ ∪ ∈ ∀ ∃ ∄ ∑ ∏ ← ↑ → ↓ ↔ ↕ ↖ ↗ ↘ ↙ ↺ ↻ ⇒ ⇔" };
	// the setUf8(std::string()) operations are unnecessary
	std::cout << std::boolalpha << (b64.encode(test1).setUtf8(std::string()).decode().getUtf8String() == test1) << std::endl;
	std::cout << std::boolalpha << (b64.encode(test2).setUtf8(std::string()).decode().getUtf8String() == test2) << std::endl;

	return EXIT_SUCCESS;
}
```
example stdout: 
```
SGVsbG8gV29ybGQg5L2g5aW977yM5LiW55WM
Hello World 你好，世界
true
true

```
