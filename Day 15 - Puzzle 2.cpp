#include <iostream>
#include <fstream>
#include <string>
#include <vector>


// Simple vector structure
struct Vec2d {
	int x, y;
};

bool operator== (const Vec2d& left, const Vec2d& right) {
	return left.x == right.x && left.y == right.y;
}


// Only inserts the item into the vector if it doesn't exist already
// We are using a vector and not a set because we need to maintain the order in
// which the elements are inserted
void insertIntoVector(std::vector<Vec2d>& toMove, const Vec2d& vec) {
	if (std::find(toMove.begin(), toMove.end(), vec) == toMove.end()) {
		toMove.push_back(vec);
	}
}


// Moves stuff on the map accordingly
bool canMove(std::vector<std::string>& map, const Vec2d& moveFrom, const Vec2d& moveTo, std::vector<Vec2d>& toMove) {
	switch (map.at(moveTo.y).at(moveTo.x)) {
	case '#':
		return false;
	case '.':
		insertIntoVector(toMove, moveFrom);
		return true;
	case '[':
	case ']':
		Vec2d dir = { moveTo.x - moveFrom.x, moveTo.y - moveFrom.y };
		if (dir.y == 0) {
			if (!canMove(map, moveTo, { moveTo.x + dir.x, moveTo.y }, toMove)) return false;
			insertIntoVector(toMove, moveFrom);
			return true;
		}

		int side = map.at(moveTo.y).at(moveTo.x) == '[' ? moveTo.x + 1 : moveTo.x - 1;
		if (!canMove(map, moveTo, { moveTo.x, moveTo.y + dir.y }, toMove)) return false;
		if (!canMove(map, { side, moveTo.y }, { side, moveTo.y + dir.y }, toMove)) return false;
		insertIntoVector(toMove, moveFrom);
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
		std::string modifiedLine = "";
		for (int i = 0; i < line.size(); ++i) {
			switch (line.at(i)) {
			case '@':
				robotPos = { i * 2, static_cast<int>(map.size()) };
				modifiedLine += "@.";
				break;
			case '.': modifiedLine += ".."; break;
			case '#': modifiedLine += "##"; break;
			case 'O': modifiedLine += "[]"; break;
			}
		}
		map.push_back(modifiedLine);
	}

	// Moves the robots and boxes according to the sequence
	for (char ch; ifs.get(ch);) {
		// Gets the direction to move in
		Vec2d dir{ };
		switch (ch) {
		case '^': dir = { 0, -1 }; break;
		case 'v': dir = { 0, +1 }; break;
		case '<': dir = { -1, 0 }; break;
		case '>': dir = { +1, 0 }; break;
		default: continue;
		}
		const Vec2d newPos = { robotPos.x + dir.x, robotPos.y + dir.y };

		// Gets all the indecies to move
		std::vector<Vec2d> toMove;
		if (!canMove(map, robotPos, newPos, toMove)) continue;

		// Moves them
		for (const auto& moveFrom : toMove) {
			map.at(moveFrom.y + dir.y).at(moveFrom.x + dir.x) = map.at(moveFrom.y).at(moveFrom.x);
			map.at(moveFrom.y).at(moveFrom.x) = '.';
		}
		robotPos = newPos;
	}

	// Calculates the gps sum
	int gpsSum = 0;
	for (size_t j = 0; j < map.size(); ++j) {
		for (size_t i = 0; i < map.at(j).size(); ++i) {
			if (map.at(j).at(i) != '[') continue;
			gpsSum += 100 * j + i;
		}
	}

	std::cout << gpsSum << std::endl;

	return 0;
}
