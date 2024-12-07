#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <chrono>


/*
* ...Fuck it, we bruteforce.
*/


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


// Custom hash function defined for a pair of Vec2d
template <>
struct std::hash<std::pair<Vec2d, Vec2d>> {
	std::size_t operator() (const std::pair<Vec2d, Vec2d>& p) const {
		return std::hash<int>()(p.first.x) ^ std::hash<int>()(p.first.y) ^
			std::hash<int>()(p.second.x) ^ std::hash<int>()(p.second.y);
	}
};


// Checks if placing an obstacle will result in a loop
bool inLoop(Vec2d guardPos, Vec2d guardDir, Vec2d obstacle, const std::vector<std::string>& map) {
	std::unordered_set<std::pair<Vec2d, Vec2d>> positionsVisited;
	while (true) {
		if (positionsVisited.contains({ guardPos, guardDir })) return true;
		positionsVisited.insert({ guardPos, guardDir });

		// If we are going out of bounds, then we are finished
		if (guardPos.x + guardDir.x < 0 || guardPos.x + guardDir.x >= map.at(0).size() ||
			guardPos.y + guardDir.y < 0 || guardPos.y + guardDir.y >= map.size()) {
			break;
		}

		// If there is an obstacle, turn right
		if (map.at(guardPos.y + guardDir.y).at(guardPos.x + guardDir.x) == '#' ||
			Vec2d{ guardPos.x + guardDir.x, guardPos.y + guardDir.y } == obstacle) {
			guardDir = { -guardDir.y, guardDir.x };
			continue;
		}

		// Otherwise walk forward
		guardPos.x += guardDir.x;
		guardPos.y += guardDir.y;
	}

	return false;
}


int main() {
	auto timeStart = std::chrono::system_clock::now();

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
	Vec2d guardStartPos = guardPos;

	// Simulates the guards patrol until they exit the map
	std::unordered_set<std::pair<Vec2d, Vec2d>> positionsVisited;
	std::unordered_set<Vec2d> newObstaclePositions;
	while (true) {
		positionsVisited.insert({ guardPos, guardDir });

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

		// Check if an obstacle can be added here to make the guard go in a loop
		Vec2d possibleObstacle = Vec2d{ guardPos.x + guardDir.x, guardPos.y + guardDir.y };
		if (inLoop(guardStartPos, Vec2d{ 0, -1 }, possibleObstacle, map) && possibleObstacle != guardStartPos) {
			newObstaclePositions.insert(possibleObstacle);
		}

		// Otherwise walk forward
		guardPos.x += guardDir.x;
		guardPos.y += guardDir.y;
	}

	std::cout << newObstaclePositions.size() << std::endl;

	auto timeEnd = std::chrono::system_clock::now();
	std::cout << timeEnd - timeStart << std::endl;

	return 0;
}
