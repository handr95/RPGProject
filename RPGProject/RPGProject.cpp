// RPGProject.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.

#include "pch.h"
#include "map_manager.h"
#include "player_manager.h"
#include "enum.h"
#include <iostream>

class AttackManager; // ���� ���� �� ���� üũ����
class EnemyManager; // ���� ����
class Mob;
class Boss;
class Elite;


int display_job_Menu() {
	int selection;

	std::cout << std::endl;
	std::cout << "Choose your job" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "1) NONE" << std::endl;
	std::cout << "2) KNIGHT" << std::endl;
	std::cout << "3) MAGICIAN" << std::endl;
	std::cout << "4) ARCHER" << std::endl;
	std::cout << std::endl;
	std::cout << "---> ";

	std::cin >> selection;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(5, '\n');
	}
	return selection;
}


std::unique_ptr<Player> select_job() {
	int nInputKey{ display_job_Menu() };
	switch (static_cast<E_CLASS>(nInputKey)) {
	case E_CLASS::E_CLASS_NONE:
		return std::make_unique<None>();
	case E_CLASS::E_CLASS_KNIGHT:
		return std::make_unique<Knight>();
	case E_CLASS::E_CLASS_MAGICIAN:
		return std::make_unique<Magician>();
	case E_CLASS::E_CLASS_ARCHER:
		return std::make_unique<Archer>();
	default:
		std::cerr << "Unknown command." << std::endl;
		return nullptr;
	}
}

std::unique_ptr<MapManager> create_map() {
	int rows;
	int columns;
	std::cout << "Enter the number of rows: ";
	std::cin >> rows;
	std::cout << "Enter the number of columns: ";
	std::cin >> columns;

	// �Էµ� ũ��� �� ����
	return std::make_unique<MapManager>(rows, columns);
}

int main()
{
	// �÷��̾� ����
	auto player = select_job();
	player->print_user_info();

	// �� ����
	auto mapManager = create_map();
	mapManager->print_map();
	mapManager->move_map();

	return 0;
}