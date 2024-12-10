#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>


/*
* Easiest part 2 ever, all you had to was comment out one line.
*/


// Simple struct to keep track of each position for pathfinding
struct Node {
	int x, y;
	int height;
	bool visited;
};


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the map and the position of the trailheads
	std::vector<std::vector<Node*>> map;
	std::vector<Node*> trailHeads;
	for (std::string line = ""; std::getline(ifs, line);) {
		std::vector<Node*> row;
		for (char ch : line) {
			int i = row.size(), j = map.size();
			Node* node = new Node{ i, j, ch - 48, false };
			row.push_back(node);

			if (ch - 48 == 0) {
				trailHeads.push_back(node);
			}
		}
		map.push_back(row);
	}

	// Calculates the score for each trailhead and adds them up
	int sum = 0;
	for (Node* startPos : trailHeads) {
		int trailHeadRating = 0;

		// Resets the map so no position has been visited
		for (size_t j = 0; j < map.size(); ++j) {
			for (size_t i = 0; i < map.at(j).size(); ++i) {
				map.at(j).at(i)->visited = false;
			}
		}

		// Does the actual pathfinding using bfs
		std::queue<Node*> queue;
		queue.push(startPos);
		while (!queue.empty()) {
			Node* currentPos = queue.front();
			queue.pop();

			// If the current position is a 9, we can add to our score
			if (currentPos->height == 9) trailHeadRating++;

			// Adds the neighbors based
			for (const auto& [dx, dy] : std::vector<std::pair<int, int>>{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }) {
				// if neighbor is outside the bounds
				if (currentPos->x + dx < 0 || currentPos->x + dx >= map.at(0).size() ||
					currentPos->y + dy < 0 || currentPos->y + dy >= map.size()) continue;

				// If we can't climb it or its been visited
				Node* neighbor = map.at(currentPos->y + dy).at(currentPos->x + dx);
				if (neighbor->height - currentPos->height != 1) continue;
				if (neighbor->visited) continue;

				queue.push(neighbor);
			}
		}

		// Adds the trailhead score to the total sum
		sum += trailHeadRating;
	}

	std::cout << sum << std::endl;

	return 0;
}
