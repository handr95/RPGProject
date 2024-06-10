#pragma once
#include "pch.h"
#include "enum.h"

class CriticalSection {
public:
	CriticalSection() {
		InitializeCriticalSection(&m_cs);  // CRITICAL_SECTION 초기화
	}

	~CriticalSection() {
		DeleteCriticalSection(&m_cs);      // 자원 해제
	}

	void lock() {
		EnterCriticalSection(&m_cs);       // 임계 영역 진입
	}

	void unlock() {
		LeaveCriticalSection(&m_cs);       // 임계 영역 해제
	}

	// 복사 생성자와 할당 연산자 삭제하여 복사 방지
	CriticalSection(const CriticalSection&) = delete;
	CriticalSection& operator=(const CriticalSection&) = delete;

private:
	CRITICAL_SECTION m_cs;                // 내부 CRITICAL_SECTION 객체
};


class MapManager {
public:
	std::vector<std::vector<int>> map() const {
		return _map;
	}

	explicit MapManager(int rows, int columns) :
		_map(rows, std::vector<int>(columns, 0)), _rows(rows), _columns(columns) {
	};

	bool move(int current_x, int current_y, int move_x, int move_y);
	void print_map();

	void create_map();
	void generate_random_map();
	void flood_fill(int x, int y, int check);
	std::set<std::vector<int>> connect_area(int startX, int startY);
	std::set<std::vector<int>> reconstruct_path(std::vector<std::vector<std::pair<int, int>>>& prev, int endX, int endY) const;

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

	std::set<int> _remain_area_idx;
	std::map<int, std::vector<int>> _area_position_map;
	int start_area_idx;
	CriticalSection critical_section;
};