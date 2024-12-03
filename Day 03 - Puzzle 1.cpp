#include <iostream>
#include <fstream>
#include <string>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	std::string correctSyntax = "mul(,)";
	std::string token = "";
	std::string a = "", b = "";

	// Goes character by character to interpret the input
	int sum = 0;
	for (char ch = 0; ifs.get(ch);) {
		// This is how we keep track of what numbers are to be multiplied
		if (isdigit(ch)) {
			if (token.empty()) continue;
			if (token.back() == ',') b += ch; else a += ch;
		} else token += ch;

		// If it isn't resembling our syntax, we can discard it
		if (token != correctSyntax.substr(0, token.size())) {
			token = "";
			a = "", b = "";
			continue;
		}

		// Once we do get a fully correct mul block, we add to our sum
		if (token == correctSyntax) {
			sum += std::atoi(a.c_str()) * std::atoi(b.c_str());
			token = "";
			a = "", b = "";
		}
	}

	std::cout << sum << std::endl;

	return 0;
}
