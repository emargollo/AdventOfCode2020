#include "pch.h"
#include "reader.h"
#include "days.h"

class Node {
	public:
		Node(char point) {
			value = point;
			tree = point == '#';
		}

		bool isTree() {
			return tree;
		}

		char chr() {
			return value;
		}

		Node* right = NULL;
		Node* down = NULL;
	private:
		bool tree;
		char value;
};

Node* initMap(std::vector<std::string> charMap) {
	Node* head = NULL;
	Node* currentLineHead = NULL;
	Node* previousLineHead = NULL;
	Node* current = NULL;

	for (unsigned int i = 0; i < charMap.size(); i++) {
		Node* previousNode = NULL;

		for (unsigned int j = 0; j < charMap[i].size(); j++) {
			current = new Node(charMap[i][j]);

			if (i == 0 && j == 0) {
				head = current;
			}

			if (j == 0) {
				currentLineHead = current;
			}

			if (previousNode != NULL) {
				previousNode->right = current;
			}

			if (previousLineHead != NULL) {
				previousLineHead->down = current;
				previousLineHead = previousLineHead->right;
			}

			previousNode = current;
		}

		if (current != NULL) {
			current->right = currentLineHead;
			previousLineHead = currentLineHead;
		}
	}
	return head;
}

void printMap(Node* head, int lineSize) {
	Node* walk = head;
	while (walk != NULL) {
		for (int i = 1; i < lineSize; i++) {
			std::cout << walk->chr();
			walk = walk->right;
		}
		std::cout << std::endl;
		walk = walk->down;
	}
}

class Toboggan {
	public:
		Toboggan(Node* head) {
			this->head = head;
		};

		std::int64_t ride(Node* path(Node*)) {
			Node* pos = head;
			std::int64_t trees = 0;
			while (pos != NULL) {
				if (pos->isTree()) { trees++; }
				pos = path(pos);
			}

			return trees;
		}
	private:
		Node* head;
};

int day3() {
	std::vector<std::string> test{
		"..##.......",
		"#...#...#..",
		".#....#..#.",
		"..#.#...#.#",
		".#...##..#.",
		"..#.##.....",
		".#.#.#....#",
		".#........#",
		"#.##...#...",
		"#...##....#",
		".#..#...#.#",
	};
	std::ifstream ifs("Day3Input.txt", std::ifstream::in);
	std::vector<std::string> input = read_input(ifs);

	Node* head = initMap(input);

	Toboggan t(head);

	std::int64_t trees1 = t.ride([](Node* pos) { return pos->right->down; });
	std::int64_t trees2 = t.ride([](Node* pos) { return pos->right->right->right->down; });
	std::int64_t trees3 = t.ride([](Node* pos) { return pos->right->right->right->right->right->down; });
	std::int64_t trees4 = t.ride([](Node* pos) { return pos->right->right->right->right->right->right->right->down; });
	std::int64_t trees5 = t.ride([](Node* pos) {
		Node* down = pos->right->down;
		if (down == NULL) { return down; }
		else { return down->down; }
	});

	std::cout << "Trees encountered(Right 1, down 1): " << trees1 << std::endl;
	std::cout << "Trees encountered(Right 3, down 1): " << trees2 << std::endl;
	std::cout << "Trees encountered(Right 5, down 1): " << trees3 << std::endl;
	std::cout << "Trees encountered(Right 7, down 1): " << trees4 << std::endl;
	std::cout << "Trees encountered(Right 1, down 2): " << trees5 << std::endl;

	std::int64_t mult = trees1 * trees2 * trees3 * trees4 * trees5;

	std::cout << "Multiplied: " << mult << std::endl;

	return 0;
}

/*
* Output:
* Trees encountered(Right 1, down 1): 82
* Trees encountered(Right 3, down 1): 242
* Trees encountered(Right 5, down 1): 71
* Trees encountered(Right 7, down 1): 67
* Trees encountered(Right 1, down 2): 24
* Multiplied: 2265549792
*/