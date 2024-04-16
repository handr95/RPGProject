#include "pch.h"
#include "map_manager.h"
#include <iostream>
#include "enum.h"

void MapManager::print_map() const {
	std::cout << "Print my map:" << std::endl;
	for (const auto& row : _map) {
		for (int cell : row) {
			switch (cell) {
			case 0:
				std::cout << "□" << " ";
				break;
			case 1:
				std::cout << "■" << " ";
				break;
			case 2:
				std::cout << "★" << " ";
				break;
			case 3:
				std::cout << "◈" << " ";
				break;
			}
		}
		std::cout << std::endl;
	}
}

void MapManager::create_map() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 100); // 균일한 분포의 랜덤 정수 생성기
	int percent = 40;

	// 맵을 랜덤하게 0과 1로 채움
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			_map[i][j] = dist(gen) <= percent ? 0 : 1; // 랜덤한 값으로 셀을 채움
		}
	}

	//_map[0][0] = 0;
	//// 0 구역끼리 묶음.
	//int check = 10;
	//for (int i = 0; i < _rows; i++) {
	//	for (int j = 0; j < _columns; j++) {
	//		if (_map[i][j] == 0) {
	//			flood_fill(i, j, check);
	//			check++;
	//		}
	//	}
	//}

	//// 다른 구역끼리 연결
	//connect_zones();


	_map[0][0] = 2;
}

void MapManager::flood_fill(int x, int y, int check) {
	if (_map[x][y] == 1) {
		return;
	}
	_map[x][y] = check;

	std::vector<std::vector<int>> directs = { {1,0},{0,1},{-1,0},{0,-1} };
	for (std::vector<int> direct : directs) {
		int goX = x + direct[0];
		int goY = y + direct[1];
		if (goX < 0 || goY < 0 || goX > _map.size() - 1 || goY > _map[goX].size() - 1) {
			continue;
		}

		if (_map[goX][goY] == 0) {
			flood_fill(goX, goY, check);
		}
	}
}

void MapManager::connect_zones() {
}

std::pair<int, int> MapManager::random_rand_path() {
	std::random_device rd;
	std::mt19937 gen(rd());

	int rows = _rows;
	int cols = _columns;

	std::uniform_int_distribution<int> rowDist(0, rows - 1);
	std::uniform_int_distribution<int> colDist(0, cols - 1);

	while (true) {
		int row = rowDist(gen);
		int col = colDist(gen);

		if (_map[row][col] == 0) {
			return std::make_pair(row, col);
		}
	}
}

bool MapManager::move(int current_x, int current_y, int move_x, int move_y) {
	if (current_x == move_x && current_y == move_y) {
		return false;
	}
	if (!is_possible_move(move_x, move_y)) {
		return false;
	}

	auto temp = _map[current_x][current_y];
	_map[current_x][current_y] = _map[move_x][move_y];
	_map[move_x][move_y] = temp;
	return true;
}

void MapManager::set_monster(int x, int y) {
	_map[x][y] = 3;
}
