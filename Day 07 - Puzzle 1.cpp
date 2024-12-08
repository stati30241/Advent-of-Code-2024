#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


/*
* When will the brute forcing stop??
*/


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Goes line by line to check if they are valid
	unsigned long long totalCalibrationResult = 0;
	for (std::string line = ""; std::getline(ifs, line);) {
		std::replace(line.begin(), line.end(), ':', ' ');

		// Reads in the line
		std::stringstream lineStream{ line };
		unsigned long long desiredResult = 0;
		std::vector<unsigned long long> numbers;
		lineStream >> desiredResult;
		for (int n = 0; lineStream >> n;) numbers.push_back(n);

		// Now check all 2^n possibilites for the operators
		// This is so stupid but im too lazy to figure out a
		// better way
		for (size_t i = 0; i < std::pow(2, numbers.size() - 1); ++i) {
			unsigned long long result = numbers.front();
			int bin = i; // Because we will be chaning it
			for (size_t j = 1; j < numbers.size(); ++j) {
				result = (bin % 2 == 0) ? result + numbers.at(j) : result * numbers.at(j);
				bin = bin >> 1;
			}

			if (result == desiredResult) {
				totalCalibrationResult += desiredResult;
				break;
			}
		}
	}

	std::cout << totalCalibrationResult << std::endl;

	return 0;
}
