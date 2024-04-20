// RPG.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include "pch.h"
#include "map_manager.h"
#include "mob_manager.h"
#include "player_manager.h"
#include "enum.h"
#include <iostream>
#include <fstream>
#include <thread>

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

	// 입력된 크기로 맵 생성
	auto mapManager = std::make_shared<MapManager>(rows, columns);
	mapManager->create_map();
	return mapManager;
}

int main()
{
	// 맵 생성
	auto mapManager = create_map();

	// 플레이어 선택
	auto player = select_job(mapManager);
	player->print_user_info();

	std::system("cls");

	MobManager mobManager(mapManager); // MobManager에 MapManager 전달
	mobManager.add_monster(3);

	// 몬스터 이동을 위한 스레드 시작
	std::thread monster_thread(&MobManager::move_monsters, &mobManager);

	// 메인 스레드에서 다른 작업 처리
	player->move_map();

	// 몬스터 스레드가 종료되기를 대기
	monster_thread.join();
	return 0;
}