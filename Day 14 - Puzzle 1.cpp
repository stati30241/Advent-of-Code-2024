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
	int totalSeconds = 100;

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
	for (size_t n = 0; n < totalSeconds; ++n) {
		for (Robot& robot : robots) {
			robot.x = mod(robot.x + robot.vx, mapWidth);
			robot.y = mod(robot.y + robot.vy, mapHeight);
		}
 	}

	// Counts the robots in each quadrant and calculates the safety factor
	int quad1 = 0, quad2 = 0, quad3 = 0, quad4 = 0;
	for (Robot& robot : robots) {
		if (robot.x < mapWidth / 2 && robot.y < mapHeight / 2) quad1++;
		if (robot.x > mapWidth / 2 && robot.y < mapHeight / 2) quad2++;
		if (robot.x > mapWidth / 2 && robot.y > mapHeight / 2) quad3++;
		if (robot.x < mapWidth / 2 && robot.y > mapHeight / 2) quad4++;
	}
	int safetyFactor = quad1 * quad2 * quad3 * quad4;

	std::cout << safetyFactor << std::endl;

	return 0;
}
