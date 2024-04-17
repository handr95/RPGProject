#include "pch.h"
#include "mob_manager.h"

void MobManager::add_monster(int count) {
	EnterCriticalSection(&m_cs);
	int create_mob = 0;
	while (create_mob < count) {
		auto gps = _mapManager->random_rand_path();
		_monster_list.push_back({ gps.first, gps.second }); // ���� �߰�
		_mapManager->set_monster(gps.first, gps.second);
		create_mob++;
	}
	LeaveCriticalSection(&m_cs);
}

void MobManager::move_monsters() {
	while (true) {
		EnterCriticalSection(&m_cs);
		for (auto& monster : _monster_list) {
			// ���͸� �����ϰ� �̵���Ŵ (���÷� ������ �������� �̵�)
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dis(-1, 1);

			int dx = dis(gen);
			int dy = dis(gen);

			// ���ο� ��ġ ���
			int new_x = monster.current_x + dx;
			int new_y = monster.current_y + dy;

			// �� ���� �������� �̵�
			if (_mapManager->is_possible_move(new_x, new_y) && _mapManager->move(monster.current_x, monster.current_y, new_x, new_y)) {
				monster.current_x = new_x;
				monster.current_y = new_y;
			}
		}
		LeaveCriticalSection(&m_cs);

		_mapManager->print_map();

		// 10�� ���
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
}
