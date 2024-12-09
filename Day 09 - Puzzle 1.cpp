#include <iostream>
#include <fstream>
#include <string>


/*
* This algorithm is too convoluted for smth 
* that was supposed to be simpler.
*/


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the disk map
	std::string diskMap = "";
	std::getline(ifs, diskMap);

	// Calculates the checksum through this very conovoluted algorithm
	unsigned long long checksum = 0;
	for (size_t index = diskMap.front() - 48, id = 1; id < (diskMap.size() + 1) / 2; ++id) { // We start off by ignoring the first file
		// Now we calculate the free space before the file and its checksum which we get by moving the files
		size_t freeSize = diskMap.at(id * 2 - 1) - 48;
		for (size_t i = 0; i < freeSize; ++i, ++index) {
			if (diskMap.back() == '0') diskMap.erase(diskMap.size() - 2, diskMap.size());

			if (id >= (diskMap.size() + 1) / 2) break;

			checksum += index * (diskMap.size() - 1) / 2;
			diskMap.back()--;
		}

		if (id >= (diskMap.size() + 1) / 2) break;

		// Now we can add on the checksum of the regular files
		size_t fileSize = diskMap.at(id * 2) - 48;
		for (size_t i = 0; i < fileSize; ++i, ++index) {
			checksum += id * index;
		}
	}

	std::cout << checksum << std::endl;

	return 0;
}
