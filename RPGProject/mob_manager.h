#include <iostream>
#include <vector>
#include <windows.h>
#include "map_manager.h"

class MobManager {
public:
	struct MobInfo
	{
		int current_x;
		int current_y;

		int m_nMaxHP;
		int m_nCurrentHP;
		int m_nAtk;
		int m_nDefense;

	};
	MobManager(std::shared_ptr<MapManager> mapManager) : _mapManager(mapManager) {
		InitializeCriticalSection(&m_cs);
	}
	~MobManager() {
		DeleteCriticalSection(&m_cs);
	}
	void add_monster(int count); // ���� �߰�
	void move_monsters(); // ���� �̵�

private:
	std::shared_ptr<MapManager> _mapManager; // MapManager�� ���� ����
	std::vector<MobInfo> _monster_list; // ���� ����
	CRITICAL_SECTION m_cs;
};