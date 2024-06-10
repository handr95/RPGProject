#pragma once
#include "pch.h"
#include "enum.h"
#include "map_manager.h"

class PlayerManager {
public:
	explicit PlayerManager(std::shared_ptr<MapManager> mapManager, E_CLASS job)
		: _mapManager(mapManager), _job(job) {};
	virtual ~PlayerManager() = default;
	virtual void print_user_info() = 0;

	void move_map();
	void move_player(int move_x, int move_y);
private:
	std::shared_ptr<MapManager> _mapManager; // MapManager에 대한 참조

	E_CLASS _job;

	int m_current_x;
	int m_current_y;

	int m_nMaxHP;
	int m_nCurrentHP;
	int m_nAtk;
	int m_nDefense;
};


class None : public PlayerManager {
public:
	explicit None(std::shared_ptr<MapManager> mapManager) : PlayerManager(mapManager, E_CLASS::E_CLASS_NONE) {}
	inline void print_user_info() override {
		std::cout << "None player" << std::endl;
	}
};

class Knight : public PlayerManager {
public:
	explicit Knight(std::shared_ptr<MapManager> mapManager) : PlayerManager(mapManager, E_CLASS::E_CLASS_KNIGHT) {}
	inline void print_user_info() override {
		std::cout << "Knight player" << std::endl;
	}
};

class Magician : public PlayerManager {
public:
	explicit Magician(std::shared_ptr<MapManager> mapManager) : PlayerManager(mapManager, E_CLASS::E_CLASS_MAGICIAN) {}
	inline void print_user_info() override {
		std::cout << "Magician player" << std::endl;
	}
};

class Archer : public PlayerManager {
public:
	explicit Archer(std::shared_ptr<MapManager> mapManager) : PlayerManager(mapManager, E_CLASS::E_CLASS_ARCHER) {}
	inline void print_user_info() override {
		std::cout << "Archer player" << std::endl;
	}
};