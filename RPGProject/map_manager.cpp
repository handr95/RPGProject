#include "pch.h"
#include <iostream>
#include "map_manager.h"
#include "util_manager.h"
#include "enum.h"


void MapManager::print_map() const {
	ConsoleManager::clear_console();
	printf("Print my map:\n");
	for (const auto& row : map()) {
		for (int cell : row) {
			switch (cell) {
			case MAP_RAND:
				printf("□");
				break;
			case MAP_WALL:
				printf("■");
				break;
			case MAP_PLAYER:
				ConsoleManager::set_console_color(CONSOLE_COLOR::YELLOW);
				printf("☆");
				ConsoleManager::set_console_color(CONSOLE_COLOR::WHITE);
				break;
			case MAP_MONSTER:
				ConsoleManager::set_console_color(CONSOLE_COLOR::DARK_VOILET);
				printf("◈");
				ConsoleManager::set_console_color(CONSOLE_COLOR::WHITE);
				break;
			}
		}
		printf("\n");
	}
	print_user_status();
}

void MapManager::create_map() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 100); // 균일한 분포의 랜덤 정수 생성기

	// 맵을 랜덤하게 0과 1로 채움
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			_map[i][j] = dist(gen) <= RAND_PERCENT ? 0 : 1; // 랜덤한 값으로 셀을 채움
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
	if (_map[x][y] == MAP_WALL) {
		return;
	}
	_map[x][y] = check;

	for (std::vector<int> direct : MoveManager::get_directs()) {
		int goX = x + direct[0];
		int goY = y + direct[1];
		if (goX < 0 || goY < 0 || goX > _map.size() - 1 || goY > _map[goX].size() - 1) {
			continue;
		}

		if (_map[goX][goY] == MAP_RAND) {
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

		if (_map[row][col] == MAP_RAND) {
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
	_map[x][y] = MAP_MONSTER;
}


bool MapManager::is_possible_move(int move_x, int move_y) const {
	// 지도 밖으로 나갔거나
	if (_columns <= move_x || _rows <= move_y || 0 > move_x || 0 > move_y) {
		return false;
	}
	// 땅이 아닌 경우
	if (_map[move_x][move_y] != MAP_RAND) {
		return false;
	}

	return true;
}

bool MapManager::is_possible_attack(int move_x, int move_y) const {
	// 지도 밖으로 나갔거나
	if (_columns <= move_x || _rows <= move_y || 0 > move_x || 0 > move_y) {
		return false;
	}
	// 몬스터가 아닌 경우
	if (_map[move_x][move_y] != MAP_MONSTER) {
		return false;
	}

	return true;
}

PLAYER_STATUS MapManager::player_status() const {
	auto position = player_position();
	for (std::vector<int> direct : MoveManager::get_directs()) {
		int goX = position.first + direct[0];
		int goY = position.second + direct[1];
		if (is_possible_attack(goX, goY)) {
			return PLAYER_STATUS::MONSTER;
		}
	}
	return PLAYER_STATUS::NONE;
}


void MapManager::print_user_status() const {
	auto position = player_position();
	auto status = player_status() == PLAYER_STATUS::MONSTER ? "가능" : "불가";
	printf("[── 공격 : %s, 현재 위치: (%d,%d) ──]\n", status, position.first, position.second);
}
