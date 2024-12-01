#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the two lists
	std::vector<int> leftList, rightList;
	for (int m = 0, n = 0; ifs >> m >> n;) {
		leftList.push_back(m);
		rightList.push_back(n);
	}

	// Sorts the two lists
	std::sort(leftList.begin(), leftList.end());
	std::sort(rightList.begin(), rightList.end());
	
	// Calculates the total distance
	int totalDistance = 0;
	for (size_t i = 0; i < leftList.size(); ++i) {
		totalDistance += std::abs(leftList.at(i) - rightList.at(i));
	}

	std::cout << totalDistance << std::endl;

	return 0;
}
