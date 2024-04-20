#include "pch.h"
#include "mob_manager.h"
#include "util_manager.h"
#include <thread>

void MobManager::add_monster(int count) {
	EnterCriticalSection(&m_cs);
	int create_mob = 0;
	int add_count = _mapManager->rows();
	while (create_mob < count) {
		auto gps = _mapManager->random_rand_path();
		_monster_list.push_back({ gps.first, gps.second }); // 몬스터 추가
		_mapManager->set_monster(gps.first, gps.second);
		create_mob++;
	}
	LeaveCriticalSection(&m_cs);
}

void MobManager::move_monsters() {
	while (true) {
		EnterCriticalSection(&m_cs);
		for (auto& monster : _monster_list) {
			// 몬스터를 랜덤하게 이동시킴
			auto direct = MoveManager::random_direct();

			// 새로운 위치 계산
			int new_x = monster.current_x + direct.first;
			int new_y = monster.current_y + direct.second;

			// 맵 범위 내에서만 이동. 이동 위치가 벽으로 막혀 있다면 움직이지 않음.
			if (_mapManager->is_possible_move(new_x, new_y) && _mapManager->move(monster.current_x, monster.current_y, new_x, new_y)) {
				monster.current_x = new_x;
				monster.current_y = new_y;
			}
		}
		LeaveCriticalSection(&m_cs);

		_mapManager->print_map();

		// 3초 대기
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}
