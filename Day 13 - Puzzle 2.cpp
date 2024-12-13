#include <algorithm>
#include <iostream>
#include <numeric>
#include <fstream>
#include <string>
#include <sstream>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Converts the file into a stringstream for easier parsing
	std::string fileBuffer{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
	std::replace_if(fileBuffer.begin(), fileBuffer.end(), [](char ch) { return !isdigit(ch); }, ' ');
	std::stringstream fileStream{ fileBuffer };

	// Solves for the values of A and B using elimination
	long long sumTokens = 0;
	for (long long x1, y1, x2, y2, X, Y; fileStream >> x1 >> y1 >> x2 >> y2 >> X >> Y;) {
		X += 10000000000000, Y += 10000000000000;
		
		long long f = std::lcm(x1, y1) / x1, g = std::lcm(x1, y1) / y1; // What we need to multiply the two eqs by
		long long b = (X * f - Y * g) / (x2 * f - y2 * g);
		long long a = (X - b * x2) / x1;

		long long c = a * x1 + b * x2;
		long long d = a * y1 + b * y2;
		if (a * x1 + b * x2 == X && a * y1 + b * y2 == Y) {
			sumTokens += a * 3 + b;
		}
	}

	std::cout << sumTokens << std::endl;

	return 0;
}
