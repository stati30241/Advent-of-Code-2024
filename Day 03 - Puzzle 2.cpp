#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	std::vector<std::string> correctSyntax = { "mul(,)", "do()", "don't()" };
	std::string token = "";
	std::string a = "", b = "";
	bool enabled = true;

	// Goes character by character to interpret the input
	int sum = 0;
	for (char ch = 0; ifs.get(ch);) {
		// This is how we keep track of what numbers are to be multiplied
		if (isdigit(ch)) {
			if (token.empty()) continue;
			if (token.back() == ',') b += ch; else a += ch;
		} else token += ch;

		// We need to check if it resembles any of our valid syntaxes
		bool valid = false;
		for (const std::string& syntax : correctSyntax) {
			if (token.size() > syntax.size()) continue;
			if (token == syntax.substr(0, token.size())) {
				valid = true;
			}
		}
		
		// If it doesn't, we can discard it
		if (!valid) {
			token = "";
			a = "", b = "";
			continue;
		}

		// Now that we have a full block, we can do stuff based on what it is
		if (token == correctSyntax.at(1)) {
			enabled = true;
			token = "";
			a = "", b = "";
		} else if (token == correctSyntax.at(2)) {
			enabled = false;
			token = "";
			a = "", b = "";
		} else if (token == correctSyntax.at(0)) {
			if (enabled) sum += std::atoi(a.c_str()) * std::atoi(b.c_str());
			token = "";
			a = "", b = "";
		}
	}

	std::cout << sum << std::endl;

	return 0;
}
