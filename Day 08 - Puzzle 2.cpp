#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>


// Simple struct for storing a 2d vector
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
	
	std::unordered_map<char, std::vector<Vec2d>> antennaPositions;
	std::unordered_set<Vec2d> antinodePositions;
	size_t mapWidth = 0, mapHeight = 0;

	// Reads in the positions of the antennas
	int j = 0;
	for (std::string line = ""; std::getline(ifs, line); ++j) {
		mapWidth = line.size();
		for (int i = 0; i < line.size(); ++i) {
			if (line.at(i) == '.') continue;
			if (antennaPositions.contains(line.at(i))) antennaPositions.at(line.at(i)).push_back(Vec2d{ i, j });
			antennaPositions.insert(std::make_pair(line.at(i), std::vector<Vec2d>{ Vec2d{ i, j } }));
		}
	}
	mapHeight = j;

	// Calculates the positions of the antinodes for each pair of identical antennas
	for (const auto& [ch, position] : antennaPositions) {
		for (const Vec2d& a : position) {
			for (const Vec2d& b : position) {
				// We need to include every antenna as well
				if (a == b) {
					antinodePositions.insert(a);
					continue;
				}

				// Adds all the antennas in the line
				Vec2d difference = { b.x - a.x, b.y - a.y };
				for (Vec2d newAntinodePos = { b.x + difference.x, b.y + difference.y };
					newAntinodePos.x >= 0 && newAntinodePos.x < mapWidth && newAntinodePos.y >= 0 && newAntinodePos.y < mapHeight;
					newAntinodePos = { newAntinodePos.x + difference.x, newAntinodePos.y + difference.y }) {
					antinodePositions.insert(newAntinodePos);
				}
			}
		}
	}

	std::cout << antinodePositions.size() << std::endl;

	return 0;
}
