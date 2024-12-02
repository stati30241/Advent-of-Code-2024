#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the reports and checks if they are safe
	int numSafeReports = 0;
	for (std::string line = ""; std::getline(ifs, line);) {
		std::stringstream lineStream{ line };
		int prevLevel = 0;
		lineStream >> prevLevel;
		int prevDir = 0;

		// Checks if the values are valid
		bool safe = true;
		for (int level = 0; lineStream >> level;) {
			// Checks if the change is between 1 and 3
			if (std::abs(level - prevLevel) < 1 || std::abs(level - prevLevel) > 3) {
				safe = false;
				continue;
			}

			// Makes sure the direction isn't reversed
			int dir = ((level - prevLevel) > 0) - ((level - prevLevel) < 0);
			if (prevDir != 0 && dir != prevDir) {
				safe = false;
				continue;
			}

			prevLevel = level;
			prevDir = dir;
		}

		numSafeReports += safe;
	}

	std::cout << numSafeReports << std::endl;

	return 0;
}
