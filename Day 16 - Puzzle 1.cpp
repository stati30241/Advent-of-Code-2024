#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <set>


/*
* So we meet again, Dijkstra...
* 
* I have learned much since our last encounter.
*/


struct Node {
	int x, y;
	bool obstacle;
	bool visited = false;
	Node* parent = nullptr;
	int score = std::numeric_limits<int>::max();
	int dx = 1, dy = 0;
};


int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads in the map
	std::vector<std::vector<Node*>> map;
	Node* startNode = nullptr;
	Node* endNode = nullptr;
	for (std::string line = ""; std::getline(ifs, line);) {
		std::vector<Node*> row;
		for (int i = 0; i < line.size(); ++i) {
			Node* node = new Node{ i, static_cast<int>(map.size()), line.at(i) == '#' };
			if (line.at(i) == 'S') startNode = node;
			if (line.at(i) == 'E') endNode = node;
			row.push_back(node);
		}
		map.push_back(row);
	}
	startNode->score = 0;

	// Needed for priority queue
	auto compareNodes = [](const Node* left, const Node* right) {
		return left->score > right->score;
	};

	// Finds the shortest path from S to E using bfs
	std::priority_queue<Node*, std::vector<Node*>, decltype(compareNodes)> queue;
	queue.push(startNode);
	while (!queue.empty()) {
		// Gets the current node
		Node* currentNode = queue.top();
		queue.pop();
		currentNode->visited = true;

		// Otherwise we keep searching
		for (auto& [dx, dy] : std::vector<std::pair<int, int>>{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }) {
			if (currentNode->x + dx < 0 || currentNode->x + dx >= map.at(0).size() ||
				currentNode->y + dy < 0 || currentNode->y + dy >= map.size()) continue;
			
			Node* nextNode = map.at(currentNode->y + dy).at(currentNode->x + dx);
			if (nextNode->obstacle) continue;
			if (nextNode->visited) continue;

			int newScore = currentNode->score + ((dx == currentNode->dx && dy == currentNode->dy) ? 1 : 1001);
			if (nextNode->score < newScore) continue;

			nextNode->parent = currentNode;
			nextNode->score = newScore;
			nextNode->dx = dx, nextNode->dy = dy;
			queue.push(nextNode);
		}
	}

	std::cout << endNode->score << std::endl;

	return 0;
}
