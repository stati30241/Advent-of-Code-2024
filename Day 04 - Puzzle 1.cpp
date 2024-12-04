#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the crossword puzzle
	std::string word = "XMAS", wordReversed{ word.rbegin(), word.rend() };
	std::vector<std::string> crossword;
	for (std::string line = ""; std::getline(ifs, line);) {
		crossword.push_back(line);
	}

	int numAppearances = 0;
	size_t crosswordWidth = crossword.at(0).size();
	size_t crosswordHeight = crossword.size();

	// Searches for the word horizontally
	for (size_t j = 0; j < crosswordHeight; ++j) {
		for (size_t i = 0; i < crosswordWidth - 3; ++i) {
			if (crossword.at(j).substr(i, 4) == word ||
				crossword.at(j).substr(i, 4) == wordReversed)
				numAppearances++;
		}
	}

	// Searches for the word vertically
	for (size_t i = 0; i < crosswordWidth; ++i) {
		for (size_t j = 0; j < crosswordHeight - 3; ++j) {
			std::string concatenation{ {crossword.at(j).at(i), crossword.at(j + 1).at(i),
				crossword.at(j + 2).at(i), crossword.at(j + 3).at(i) } };
			if (concatenation == word || concatenation == wordReversed) 
				numAppearances++;
		}
	}

	// Search for the word in one diagonal
	for (size_t k = 3; k <= crosswordHeight * 2 - 2; ++k) {
		size_t i = k < crosswordHeight ? 0 : (k + 1) - crosswordHeight;
		size_t j = k < crosswordHeight ? k : crosswordHeight - 1;
		for (; j >= 3 && i < crosswordWidth - 3; ++i, --j) {
			std::string concatenation{ {crossword.at(j).at(i), crossword.at(j - 1).at(i + 1),
				crossword.at(j - 2).at(i + 2), crossword.at(j - 3).at(i + 3) } };
			if (concatenation == word || concatenation == wordReversed) numAppearances++;
		}
	}

	
	// Search for the word in the other diagonal
	for (size_t k = 3; k <= crosswordWidth * 2 - 2; ++k) {
		size_t i = k < crosswordWidth ? k : crosswordWidth - 1;
		size_t j = k < crosswordWidth ? crosswordHeight - 1 : crosswordHeight - ((k + 1) - crosswordWidth) - 1;
		for (; i >= 3 && j >= 3; --i, --j) {
			std::string concatenation{ {crossword.at(j).at(i), crossword.at(j - 1).at(i - 1),
				crossword.at(j - 2).at(i - 2), crossword.at(j - 3).at(i - 3) } };
			if (concatenation == word || concatenation == wordReversed) numAppearances++;
		}
	}
	

	std::cout << numAppearances << std::endl;

	return 0;
}
