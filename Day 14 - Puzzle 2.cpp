#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


// Simple struct to keep track of a robot
struct Robot {
	int x, y, vx, vy;
};


// Better mod function that takes care of negative values
int mod(int a, int b) {
	return ((a % b) + b) % b;
}


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// World info
	int mapWidth = 101, mapHeight = 103;

	// Converts the file into a stringstream for easier parsing
	std::string fileBuffer{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
	std::replace_if(fileBuffer.begin(), fileBuffer.end(), [](char ch) { return !isdigit(ch) && ch != '-'; }, ' ');
	std::stringstream fileStream{ fileBuffer };

	// Reads in the robot information
	std::vector<Robot> robots;
	for (int x, y, vx, vy; fileStream >> x >> y >> vx >> vy;) {
		robots.push_back(Robot{ x, y, vx, vy });
	}

	// Simulates the behavior of the robots
	size_t secondsElapsed = 1; // Start at 1
	for (;; ++secondsElapsed) {
		for (Robot& robot : robots) {
			robot.x = mod(robot.x + robot.vx, mapWidth);
			robot.y = mod(robot.y + robot.vy, mapHeight);
		}

		// The tree can only be formed if the robots aren't on top of each other (hopefully)
		bool overlapping = false;
		for (const Robot& robot1 : robots) {
			for (const Robot& robot2 : robots) {
				if (&robot1 == &robot2) continue;
				if (robot1.x == robot2.x && robot1.y == robot2.y) overlapping = true;
			}
		}
		if (!overlapping) break;
 	}

	std::cout << secondsElapsed << std::endl;

	return 0;
}
