#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>


// Simple 2d vector sturct
struct Vec2d {
	int x, y;
};


bool operator== (const Vec2d& left, const Vec2d& right) {
	return left.x == right.x && left.y == right.y;
}


// Custom hash function defined for the Vec2d
template <>
struct std::hash<Vec2d> {
	std::size_t operator() (const Vec2d& vec) const {
		return std::hash<int>()(vec.x) ^ std::hash<int>()(vec.y);
	}
};



int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the map along with the position of the guard
	std::vector<std::string> map;
	int j = 0;
	Vec2d guardPos = { }, guardDir = { 0, -1 };
	for (std::string line = ""; std::getline(ifs, line); ++j) {
		for (int i = 0; i < line.size(); ++i) if (line.at(i) == '^') guardPos = { i, j };
		map.push_back(line);
	}

	// Simulates the guards patrol until they exit the map
	std::unordered_set<Vec2d> positionsVisited;
	while (true) {
		positionsVisited.insert(guardPos);

		// If we are going out of bounds, then we are finished
		if (guardPos.x + guardDir.x < 0 || guardPos.x + guardDir.x >= map.at(0).size() ||
			guardPos.y + guardDir.y < 0 || guardPos.y + guardDir.y >= map.size()) {
			break;
		}

		// If there is an obstacle, turn right
		if (map.at(guardPos.y + guardDir.y).at(guardPos.x + guardDir.x) == '#') {
			guardDir = { -guardDir.y, guardDir.x };
			continue;
		}

		// Otherwise walk forward
		guardPos.x += guardDir.x;
		guardPos.y += guardDir.y;
	}

	std::cout << positionsVisited.size() << std::endl;

	return 0;
}
