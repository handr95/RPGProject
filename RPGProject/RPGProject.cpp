// RPGProject.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include "pch.h"
#include "map_manager.h"
#include "player_manager.h"
#include "enum.h"
#include <iostream>

class AttackManager; // 전투 공식 및 전투 체크사항
class EnemyManager; // 적군 관리
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

	// 입력된 크기로 맵 생성
	return std::make_unique<MapManager>(rows, columns);
}

int main()
{
	// 플레이어 선택
	auto player = select_job();
	player->print_user_info();

	// 맵 생성
	auto mapManager = create_map();
	mapManager->print_map();
	mapManager->move_map();

	return 0;
}