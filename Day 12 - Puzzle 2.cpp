#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <set>


// Uses the flood fill algorithm to get area and number of sides
std::pair<int, int> floodFill(const std::vector<std::string>& map,
	std::vector<std::vector<bool>>& hasBeenVisited, size_t i, size_t j) {
	int area = 0;
	
	// Uses the floodfill algorithm to make a map of all the normals
	// The map needs to have a set of normals as the normals need to be ordered
	std::map<std::pair<int, int>, std::set<std::pair<int, int>>> normals;
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
				if (normals.contains({ dx, dy })) normals.at({ dx, dy }).insert({ x, y });
				else normals.insert({ { dx, dy }, std::set<std::pair<int, int>>{ { x, y } } });
				continue;
			}

			if (hasBeenVisited.at(y + dy).at(x + dx)) continue;

			queue.push({ x + dx, y + dy });
			hasBeenVisited.at(y + dy).at(x + dx) = true;
		}
	}

	// Collapses adjacent normals into one side
	std::map<std::pair<int, int>, std::set<std::pair<int, int>>> sides;
	for (const auto& [normal, positions] : normals) {
		for (const auto& position : positions) {
			if (!sides.contains(normal)) sides.insert({ normal, {position } });
			else {
				bool unique = true;
				for (auto [nx, ny] : normals.at(normal)) {
					// We will use the fact that normals are ordered to only check for the normals behind us
					if (normal.first == 0 && position.second == ny && (position.first - nx) == 1) unique = false;
					if (normal.second == 0 && position.first == nx && (position.second - ny) == 1) unique = false;
				}
				if (unique) sides.at(normal).insert(position);
			}
		}
	}

	// Counts the number of sides
	int numSides = 0;
	for (const auto& [normal, positions] : sides) {
		numSides += positions.size();
	}

	return std::make_pair(area, numSides);
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
			auto [area, numSides] = floodFill(map, hasBeenVisisted, i, j);
			totalCost += area * numSides;
		}
	}

	std::cout << totalCost << std::endl;

	return 0;
}
