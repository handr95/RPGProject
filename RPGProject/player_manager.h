#pragma once
#include "pch.h"
#include "enum.h"
#include <iostream>

class Player {
public:
	Player(E_CLASS job) : _job(job) {};
	virtual ~Player() = default;
	virtual void print_user_info() = 0;
private:
	E_CLASS _job;
	int m_nMaxHP;
	int m_nCurrentHP;
	int m_nAtk;
	int m_nDefense;
};


class None : public Player {
public:
	None() : Player(E_CLASS::E_CLASS_NONE) {}
	inline void print_user_info() override {
		std::cout << "None player" << std::endl;
	}
};

class Knight : public Player {
public:
	Knight() : Player(E_CLASS::E_CLASS_KNIGHT) {}
	inline void print_user_info() override {
		std::cout << "Knight player" << std::endl;
	}
};

class Magician : public Player {
public:
	Magician() : Player(E_CLASS::E_CLASS_MAGICIAN) {}
	inline void print_user_info() override {
		std::cout << "Magician player" << std::endl;
	}
};

class Archer : public Player {
public:
	Archer() : Player(E_CLASS::E_CLASS_ARCHER) {}
	inline void print_user_info() override {
		std::cout << "Archer player" << std::endl;
	}
};