#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the stones
	using ull = unsigned long long;
	std::unordered_map<ull, ull> stones, stonesCopy;
	for (ull stone = 0; ifs >> stone;) {
		if (stones.contains(stone)) stones.at(stone)++;
		else stones.insert(std::make_pair(stone, 1));
	}

	// Simulates blinking
	size_t numBlinks = 75;
	for (size_t n = 0; n < numBlinks; ++n) {
		stonesCopy = stones;
		for (const auto& [stone, freq] : stones) {
			std::string stoneString = std::to_string(stone);

			if (freq == 0) continue;

			if (stone == 0) {
				if (stonesCopy.contains(1)) stonesCopy.at(1) += freq;
				else stonesCopy.insert(std::make_pair(1, freq));
			} else if (stoneString.size() % 2 == 0) {
				ull a = std::atoll(stoneString.substr(0, stoneString.size() / 2).c_str());
				ull b = std::atoll(stoneString.substr(stoneString.size() / 2).c_str());

				if (stonesCopy.contains(a)) stonesCopy.at(a) += freq; else stonesCopy.insert(std::make_pair(a, freq));
				if (stonesCopy.contains(b)) stonesCopy.at(b) += freq; else stonesCopy.insert(std::make_pair(b, freq));
			} else {
				if (stonesCopy.contains(stone * 2024ull)) stonesCopy.at(stone * 2024ull) += freq;
				else stonesCopy.insert(std::make_pair(stone * 2024ull, freq));
			}

			stonesCopy.at(stone) -= freq;
		}
		stones = stonesCopy;
	}

	// Counts the total number of stones
	ull totalStones = 0;
	for (const auto& [stone, freq] : stones) {
		totalStones += freq;
	}

	std::cout << totalStones << std::endl;;

	return 0;
}
