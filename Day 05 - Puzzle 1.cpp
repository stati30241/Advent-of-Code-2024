#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the ordering rules and makes a map of which numbers
	// cannot come after a number
	std::unordered_map<int, std::unordered_set<int>> invalidOrderingMap;
	for (std::string line = ""; std::getline(ifs, line) && !line.empty();) {
		// Reads in the numbers and their order
		int pred = std::atoi(line.substr(0, line.find_first_of('|')).c_str());
		int succ = std::atoi(line.substr(line.find_first_of('|') + 1, line.size()).c_str());
		
		// Adds the info to our map
		if (invalidOrderingMap.contains(succ)) invalidOrderingMap.at(succ).insert(pred);
		else invalidOrderingMap.insert(std::make_pair(succ, std::unordered_set{ pred }));
	}

	// Now reads in the pages to be produced and checks if they are in order
	int sumOfMiddleNumbers = 0;
	for (std::string line = ""; std::getline(ifs, line);) {
		std::replace(line.begin(), line.end(), ',', ' ');
		std::stringstream lineStream{ line };
		std::vector<int> pages;
		for (int page = 0; lineStream >> page;) pages.push_back(page);

		// Now checks if the pages are in order
		float inOrder = true;
		for (size_t i = 0; i < pages.size() - 1; ++i) {
			for (size_t j = i + 1; j < pages.size(); ++j) {
				if (!invalidOrderingMap.contains(pages.at(i))) continue;
				if (invalidOrderingMap.at(pages.at(i)).contains(pages.at(j))) inOrder = false;
			}
		}

		// If the line is in order, we can add the middle number
		if (inOrder) sumOfMiddleNumbers += pages.at((pages.size() - 1) / 2);
	}

	std::cout << sumOfMiddleNumbers << std::endl;

	return 0;
}
