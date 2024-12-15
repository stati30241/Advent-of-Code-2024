#include <iostream>
#include <fstream>
#include <string>
#include <vector>


// Simple vector structure
struct Vec2d {
	int x, y;
};


// Moves stuff on the map accordingly
bool move(std::vector<std::string>& map, const Vec2d& moveFrom, const Vec2d& moveTo) {
	switch (map.at(moveTo.y).at(moveTo.x)) {
	case '.':
		map.at(moveTo.y).at(moveTo.x) = map.at(moveFrom.y).at(moveFrom.x);
		map.at(moveFrom.y).at(moveFrom.x) = '.';
		return true;
	case '#':
		return false;
	case 'O':
		Vec2d dir = { moveTo.x - moveFrom.x, moveTo.y - moveFrom.y };
		if (!move(map, moveTo, { moveTo.x + dir.x, moveTo.y + dir.y })) return false;
		map.at(moveTo.y).at(moveTo.x) = map.at(moveFrom.y).at(moveFrom.x);
		map.at(moveFrom.y).at(moveFrom.x) = '.';
		return true;
	}
}


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the map and finds the robot's position
	std::vector<std::string> map;
	Vec2d robotPos{ };
	for (std::string line = ""; std::getline(ifs, line) && line != "";) {
		map.push_back(line);
		for (int i = 0; i < line.size(); ++i) {
			if (line.at(i) == '@') robotPos = { i, static_cast<int>(map.size()) - 1 };
		}
	}

	// Moves the robots and boxes according to the sequence
	for (char ch; ifs.get(ch);) {
		Vec2d newPos{ };
		switch (ch) {
		case '^': newPos = { robotPos.x, robotPos.y - 1 }; break;
		case 'v': newPos = { robotPos.x, robotPos.y + 1 }; break;
		case '<': newPos = { robotPos.x - 1, robotPos.y }; break;
		case '>': newPos = { robotPos.x + 1, robotPos.y }; break;
		default: continue;
		}

		if (move(map, robotPos, newPos)) {
			robotPos = newPos;
		}
	}

	// Calculates the gps sum
	int gpsSum = 0;
	for (size_t j = 0; j < map.size(); ++j) {
		for (size_t i = 0; i < map.at(j).size(); ++i) {
			if (map.at(j).at(i) != 'O') continue;
			gpsSum += 100 * j + i;
		}
	}

	std::cout << gpsSum << std::endl;

	return 0;
}
