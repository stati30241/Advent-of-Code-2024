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
	
	// Calculates the similarity score
	int totalSimilarityScore = 0;
	for (int num : leftList) {
		totalSimilarityScore += num * std::count(rightList.begin(), rightList.end(), num);
	}

	std::cout << totalSimilarityScore << std::endl;

	return 0;
}
