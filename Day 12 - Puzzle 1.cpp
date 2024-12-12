#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>


// Uses the flood fill algorithm to get area and perimeter
std::pair<int, int> floodFill(const std::vector<std::string>& map,
	std::vector<std::vector<bool>>& hasBeenVisited, size_t i, size_t j) {
	int area = 0, perimeter = 0;
	
	std::queue<std::pair<int, int>> queue;
	queue.push({ i, j });
	hasBeenVisited.at(j).at(i) = true;
	while (!queue.empty()) {
		auto [x, y] = queue.front();
		queue.pop();
		area++;

		for (auto [dx, dy] : std::vector<std::pair<int, int>>{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }) {
			if (x + dx < 0 || x + dx >= map.at(0).size() || y + dy < 0 || y + dy >= map.size() ||
				map.at(y).at(x) != map.at(y + dy).at(x + dx)) {
				perimeter++;
				continue;
			}

			if (hasBeenVisited.at(y + dy).at(x + dx)) continue;

			queue.push({ x + dx, y + dy });
			hasBeenVisited.at(y + dy).at(x + dx) = true;
		}
	}

	return std::make_pair(area, perimeter);
}


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the map
	std::vector<std::string> map;
	for (std::string line = ""; std::getline(ifs, line);) map.push_back(line);
	std::vector<std::vector<bool>> hasBeenVisisted;
	for (size_t j = 0; j < map.size(); ++j) {
		hasBeenVisisted.push_back(std::vector<bool>(map.at(j).size(), false));
	}

	// Calculates the total cost
	int totalCost = 0;
	for (size_t j = 0; j < map.size(); ++j) {
		for (size_t i = 0; i < map.at(j).size(); ++i) {
			if (hasBeenVisisted.at(j).at(i)) continue;
			auto [area, perimeter] = floodFill(map, hasBeenVisisted, i, j);
			totalCost += area * perimeter;
		}
	}

	std::cout << totalCost << std::endl;

	return 0;
}
