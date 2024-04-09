#pragma once
#pragma once
#include <vector>
#include <random>

// 맵 생성, 이동관련, 뷰어
class MapManager {
public:
	std::vector<std::vector<int>> map() const {
		return _map;
	}

	MapManager(int rows, int columns) :
		_map(rows, std::vector<int>(columns, 0)), _rows(rows), _columns(columns) {

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, 1); // 균일한 분포의 랜덤 정수 생성기

		// 맵을 랜덤하게 0과 1로 채움
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				_map[i][j] = dist(gen); // 랜덤한 값으로 셀을 채움
			}
		}

		_current_x = 0;
		_current_y = 0;
		_map[_current_x][_current_y] = 2;
	};

	void move(int x, int y);
	void print_map() const;
	void move_map();

private:
	std::vector<std::vector<int>> _map;
	int _rows;
	int _columns;
	int _current_x;
	int _current_y;
};