#pragma once
#include <vector>
#include <random>

// ���� ���� �ڿ�. ������ �ൿ�� ������
// �� ���� -> thread // ���� ��ü�� main���� ��� ��������.
// �̵�����, ���
// ���� ���� -> ������
// ���� �̵� -> ������
// ���� -> ���� / �÷��̾� �̵��� ..?
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
		// ���� ������ �����ų�
		if (_columns <= move_x || _rows <= move_y || 0 > move_x || 0 > move_y) {
			return false;
		}
		// ���� ���
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