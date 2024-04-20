// RPG.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.

#include "pch.h"
#include "map_manager.h"
#include "mob_manager.h"
#include "player_manager.h"
#include "enum.h"
#include <iostream>
#include <fstream>
#include <thread>

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


std::unique_ptr<PlayerManager> select_job(std::shared_ptr<MapManager> mapManager) {
	int nInputKey{ display_job_Menu() };
	switch (static_cast<E_CLASS>(nInputKey)) {
	case E_CLASS::E_CLASS_NONE:
		return std::make_unique<None>(mapManager);
	case E_CLASS::E_CLASS_KNIGHT:
		return std::make_unique<Knight>(mapManager);
	case E_CLASS::E_CLASS_MAGICIAN:
		return std::make_unique<Magician>(mapManager);
	case E_CLASS::E_CLASS_ARCHER:
		return std::make_unique<Archer>(mapManager);
	default:
		std::cerr << "Unknown command." << std::endl;
		return nullptr;
	}
}

std::shared_ptr<MapManager> create_map() {
	int rows;
	int columns;
	std::cout << "Enter the number of rows: ";
	std::cin >> rows;
	std::cout << "Enter the number of columns: ";
	std::cin >> columns;

	// �Էµ� ũ��� �� ����
	auto mapManager = std::make_shared<MapManager>(rows, columns);
	mapManager->create_map();
	return mapManager;
}

int main()
{
	// �� ����
	auto mapManager = create_map();

	// �÷��̾� ����
	auto player = select_job(mapManager);
	player->print_user_info();

	std::system("cls");

	MobManager mobManager(mapManager); // MobManager�� MapManager ����
	mobManager.add_monster(3);

	// ���� �̵��� ���� ������ ����
	std::thread monster_thread(&MobManager::move_monsters, &mobManager);

	// ���� �����忡�� �ٸ� �۾� ó��
	player->move_map();

	// ���� �����尡 ����Ǳ⸦ ���
	monster_thread.join();
	return 0;
}