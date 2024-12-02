#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the reports and checks if they are safe
	int numSafeReports = 0;
	for (std::string line = ""; std::getline(ifs, line);) {
		// Reads in the report
		std::stringstream lineStream{ line };
		std::vector<int> report;
		for (int level = 0; lineStream >> level;) report.push_back(level);

		// Now checks if it can be made safe by removing each element one by one
		// Fun fact: we don't need to check if its already safe,
		// because if it is then it can also be made safe
		for (size_t i = 0; i < report.size(); ++i) {
			int prevLevel = i == 0 ? report.at(1) : report.at(0);
			int prevDir = 0;
			bool safe = true;
			for (size_t j = i == 0 ? 2 : 1; j < report.size(); ++j) {
				if (j == i) continue;

				int dir = ((report.at(j) - prevLevel) > 0) - ((report.at(j) - prevLevel) < 0);

				// Checks if our new report is safe
				if (std::abs(report.at(j) - prevLevel) < 1 || std::abs(report.at(j) - prevLevel) > 3) {
					safe = false;
					continue;
				}
				if (prevDir != 0 && dir != prevDir) {
					safe = false;
					continue;
				}

				prevLevel = report.at(j);
				prevDir = dir;
			}

			// If it can be made safe one way, we don't need to check again
			if (safe) {
				numSafeReports++;
				break;
			}
		}
	}

	std::cout << numSafeReports << std::endl;

	return 0;
}
