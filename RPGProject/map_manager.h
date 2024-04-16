#pragma once
#include <vector>
#include <random>

// 맵은 공유 자원. 각각의 행동은 쓰레드
// 맵 생성 -> thread // 만든 객체를 main에서 어떻게 가져올지.
// 이동관련, 뷰어
// 몬스터 생성 -> 쓰레드
// 몬스터 이동 -> 쓰레드
// 메인 -> 선택 / 플레이어 이동을 ..?
class MapManager {
public:
	std::vector<std::vector<int>> map() const {
		return _map;
	}

	MapManager(int rows, int columns) :
		_map(rows, std::vector<int>(columns, 0)), _rows(rows), _columns(columns) { };

	bool move(int current_x, int current_y, int move_x, int move_y);
	void print_map() const;
	void create_map();
	void flood_fill(int x, int y, int check);
	void connect_zones();
	void set_monster(int x, int y);
	std::pair<int, int> random_rand_path();

	bool is_possible_move(int move_x, int move_y) const {
		// 지도 밖으로 나갔거나
		if (_columns <= move_x || _rows <= move_y || 0 > move_x || 0 > move_y) {
			return false;
		}
		// 벽인 경우
		if (_map[move_x][move_y] != 0) {
			return false;
		}

		return true;
	}
private:
	std::vector<std::vector<int>> _map;
	int _rows;
	int _columns;
};