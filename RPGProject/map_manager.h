#pragma once
#include "pch.h"
#include "enum.h"
#include <vector>
#include <random>

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

	bool is_possible_move(int move_x, int move_y) const;
	bool is_possible_attack(int move_x, int move_y) const;

	PLAYER_STATUS player_status() const;
	void print_user_status() const;

	inline void set_player_position(int x, int y) {
		_player_position = std::make_pair(x, y);
	}
	inline std::pair<int, int> player_position() const {
		return _player_position;
	}
	inline int rows() const {
		return _rows;
	}
private:
	std::pair<int, int> _player_position;
	std::vector<std::vector<int>> _map;
	int _rows;
	int _columns;
};