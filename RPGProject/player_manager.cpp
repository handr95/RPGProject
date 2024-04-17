#include "pch.h"
#include "enum.h"
#include "player_manager.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>

void PlayerManager::move_map() {
	int nInputKey = 0;

	while (true)
	{
		if (::_kbhit() > 0)
		{
			nInputKey = ::_getch();
		}
		else nInputKey = 0;
		switch (static_cast<E_INPUT_KEY>(nInputKey))
		{
		case E_INPUT_KEY::E_INPUT_KEY_NONE: {
			break;
		}
		case E_INPUT_KEY::E_INPUT_KEY_UP: {
			move_player(-1, 0);
			break;
		}
		case E_INPUT_KEY::E_INPUT_KEY_DOWN: {
			move_player(1, 0);
			break;
		}
		case E_INPUT_KEY::E_INPUT_KEY_LEFT: {
			move_player(0, -1);
			break;
		}
		case E_INPUT_KEY::E_INPUT_KEY_RIGHT: {
			move_player(0, 1);
			break;
		}
		default: break;
		}

		int a = 1;
		int b = 2;
		if (a != 1) {

		}
		::Sleep(100);
	}
}

void PlayerManager::move_player(int move_x, int move_y) {
	int new_x = m_current_x + move_x;
	int new_y = m_current_y + move_y;

	// 맵 범위 내에서만 이동
	if (_mapManager->is_possible_move(new_x, new_y)
		&& _mapManager->move(m_current_x, m_current_y, new_x, new_y)) {
		m_current_x = new_x;
		m_current_y = new_y;
	}

	_mapManager->print_map();
}