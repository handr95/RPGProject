#include "pch.h"
#include <iostream>
#include <queue>
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

	generate_random_map();

	// 0 구역끼리 묶음.
	int target = FLOOD_START_IDX;
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			if (_map[i][j] == MAP_RAND) {
				flood_fill(i, j, target);
				_remain_area_idx.insert(target);
				_area_position_map[target] = { i, j };
				target++;
			}
		}
	}

	// 다른 구역끼리 연결
	std::set<std::vector<int>> changePath;
	start_area_idx = *_remain_area_idx.begin();
	while (!_remain_area_idx.empty()) {
		_remain_area_idx.erase(start_area_idx);
		auto start = _area_position_map[start_area_idx];
		auto bfsPath = connect_area(start[0], start[1]);
		if (bfsPath.empty()) {
			continue;
		}
		for (auto& position : bfsPath) {
			_map[position[0]][position[1]] = MAP_RAND;
		}
	}

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			if (_map[i][j] >= FLOOD_START_IDX) {
				_map[i][j] = MAP_RAND;
			}
		}
	}

	_map[0][0] = 2;
}

// 0,1 랜덤으로 맵 세팅
void MapManager::generate_random_map() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 100); // 균일한 분포의 랜덤 정수 생성기

	// 맵을 랜덤하게 0과 1로 채움
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			_map[i][j] = dist(gen) <= RAND_PERCENT ? 0 : 1; // 랜덤한 값으로 셀을 채움
		}
	}
	// 0부터 시작
	_map[0][0] = 0;
}

// 서로 이어져 있는 0끼리 그룹화
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

std::set<std::vector<int>> MapManager::reconstruct_path(std::vector<std::vector<std::pair<int, int>>>& prev, int endX, int endY) const {
	std::set<std::vector<int>> path;
	int x = endX;
	int y = endY;

	while (prev[x][y] != std::pair<int, int>{-1, -1}) {
		path.insert({ x, y });
		auto previous = prev[x][y];  // 이전 위치 좌표 조회
		x = previous.first;
		y = previous.second;
	}

	// 출발점 정보
	path.insert({ x, y });

	return path;
}

// 근처 지역끼리 연결 처리
std::set<std::vector<int>> MapManager::connect_area(int startX, int startY) {
	std::queue<std::vector<int>> queue;
	std::vector<std::vector<std::pair<int, int>>> prev(_map.size(), std::vector<std::pair<int, int>>(_map[0].size(), { -1, -1 }));
	std::vector<std::vector<bool>> visited(_map.size(), std::vector<bool>(_map[0].size(), false));

	queue.push({ startX, startY });
	visited[startX][startY] = true;

	while (!queue.empty()) {
		auto current = queue.front();
		queue.pop();
		int x = current[0];
		int y = current[1];

		// 연결되지 않은 지역이랑만 연결되도록 처리
		if (_remain_area_idx.find(_map[x][y]) != _remain_area_idx.end()) {
			start_area_idx = _map[x][y];
			return reconstruct_path(prev, x, y);
		}

		for (auto& dir : MoveManager::get_directs()) {
			int nx = x + dir[0];
			int ny = y + dir[1];

			if (nx >= 0 && nx < _map.size() && ny >= 0 && ny < _map[nx].size() && !visited[nx][ny]) {
				visited[nx][ny] = true;
				prev[nx][ny] = { x, y };
				queue.push({ nx, ny });
			}
		}
	}

	return {}; // Empty path if not found
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
	// player, mob 동시에 move가 일어날수 있어 lock 추가
	EnterCriticalSection(&m_cs);
	if (current_x == move_x && current_y == move_y) {
		LeaveCriticalSection(&m_cs);
		return false;
	}
	if (!is_possible_move(move_x, move_y)) {
		LeaveCriticalSection(&m_cs);
		return false;
	}

	auto temp = _map[current_x][current_y];
	_map[current_x][current_y] = _map[move_x][move_y];
	_map[move_x][move_y] = temp;
	LeaveCriticalSection(&m_cs);
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
