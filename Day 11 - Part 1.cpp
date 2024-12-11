#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the stones
	using ull = unsigned long long;
	std::vector<ull> stones, stonesCopy;
	for (ull stone = 0; ifs >> stone;) stones.push_back(stone);

	// Simulates blinking
	size_t numBlinks = 25;
	for (size_t n = 0; n < numBlinks; ++n) {
		stonesCopy.clear();
		for (ull stone : stones) {
			if (stone == 0) {
				stonesCopy.push_back(1);
				continue;
			}

			std::string stoneString = std::to_string(stone);
			if (stoneString.size() % 2 == 0) {
				stonesCopy.push_back(std::atoll(stoneString.substr(0, stoneString.size() / 2).c_str()));
				stonesCopy.push_back(std::atoll(stoneString.substr(stoneString.size() / 2).c_str()));
			}

			else {
				stonesCopy.push_back(stone * 2024ull);
			}
		}
		stones = stonesCopy;
	}

	std::cout << stones.size() << std::endl;

	return 0;
}
