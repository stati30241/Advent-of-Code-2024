#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


/*
* Almost ran out of time today, just almost...
*/


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the disk map
	std::string diskMap = "";
	std::getline(ifs, diskMap);

	// Generates the block map of the disk
	std::vector<std::vector<size_t>> blockMap;
	for (size_t index = 0, i = 0; i < diskMap.size(); ++i) {
		if (i % 2 == 0) {
			blockMap.push_back(std::vector<size_t>(diskMap.at(i) - 48, index + 48));
			index++;
		} else blockMap.push_back(std::vector<size_t>(diskMap.at(i) - 48, 1));
	}

	// Now moves all the files from the back to the front
	for (int i = blockMap.size() - 1; i >= 0; i -= 2) {
		for (int j = 1; j < i; j += 2) {
			size_t numFreeSpaces = std::count(blockMap.at(j).begin(), blockMap.at(j).end(), 1);
			if (blockMap.at(i).size() > numFreeSpaces) continue;
			size_t difference = numFreeSpaces - blockMap.at(i).size();

			blockMap.at(j).erase(std::remove(blockMap.at(j).begin(), blockMap.at(j).end(), 1), blockMap.at(j).end());
			blockMap.at(j).insert(blockMap.at(j).end(), blockMap.at(i).begin(), blockMap.at(i).end());
			blockMap.at(j).insert(blockMap.at(j).end(), difference, 1);

			blockMap.at(i) = std::vector<size_t>(blockMap.at(i).size(), 1);
			break;
		}
	}

	// Calculates the checksum
	unsigned long long checksum = 0;
	size_t index = 0;
	for (size_t i = 0; i < blockMap.size(); ++i) {
		for (size_t j = 0; j < blockMap.at(i).size(); ++j) {
			if (blockMap.at(i).at(j) == 1) {
				index++;
				continue;
			};
			checksum += index * (blockMap.at(i).at(j) - 48);
			index++;
		}
	}

	std::cout << checksum << std::endl;

	return 0;
}
