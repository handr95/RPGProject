#pragma once
#pragma once
#include <vector>
#include <random>

// �� ����, �̵�����, ���
class MapManager {
public:
	std::vector<std::vector<int>> map() const {
		return _map;
	}

	MapManager(int rows, int columns) :
		_map(rows, std::vector<int>(columns, 0)), _rows(rows), _columns(columns) {

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, 1); // ������ ������ ���� ���� ������

		// ���� �����ϰ� 0�� 1�� ä��
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				_map[i][j] = dist(gen); // ������ ������ ���� ä��
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